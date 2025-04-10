#include "minia.h"

#include <iostream>

#include "builtin.h"
#include "toml.hpp"

namespace minia {

Minia::Minia(const std::string &config_file) {
  toml::table table;
  try {
    table = toml::parse_file(config_file);
  } catch (const toml::parse_error &err) {
    throw std::runtime_error("Error parsing file '" + *err.source().path +
                             "': " + std::string(err.description()) + " (" +
                             std::to_string(err.source().begin.line) + ")");
  }

  std::vector<std::string> exprs;
  if (auto *arr = table.at_path("transform.expressions").as_array()) {
    for (const auto &item : *arr) {
      if (auto expr = item.value<std::string>()) {
        exprs.emplace_back(*expr);
      }
    }
  } else {
    throw std::runtime_error("Missing or invalid 'transform.expressions' "
                             "array in configuration.");
  }

  parse(exprs);
}

Minia::Minia(const toml::table &table) {
  std::vector<std::string> exprs;
  if (auto *arr = table.at_path("transform.expressions").as_array()) {
    for (const auto &item : *arr) {
      if (auto expr = item.value<std::string>()) {
        exprs.emplace_back(*expr);
      }
    }
  } else {
    throw std::runtime_error("Missing or invalid 'transform.expressions' "
                             "array in configuration.");
  }

  parse(exprs);
}

void Minia::call(Features &features) {
  // copy literals
  for (const auto &[key, value] : literals_) {
    auto ptr = features.get(key);
    if (ptr == nullptr) {
      features.insert(key, value);
    }
  }

  for (const auto &op : ops_) {
    op(features);
  }

  for (const auto &k : features_) {
    features.insert(k, features.get(name_mappings_[k]));
  }
}

void Minia::parse(const std::vector<std::string> &exprs) {
  // Combine expressions into a single string with ';' as a delimiter
  std::string total;
  for (size_t i = 0; i < exprs.size(); ++i) {
    if (i > 0) {
      total += ";";
    }
    total += exprs[i];
  }

  // Initialize ANTLR components for parsing
  antlr4::ANTLRInputStream input(total);
  miniaLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  miniaParser parser(&tokens);

  // Parse the input and build the parse tree
  antlr4::tree::ParseTree *tree = parser.prog();

  // Walk the parse tree with a custom listener
  minia::MiniaListener listener;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  // Retrieve nodes from the listener
  auto nodes = listener.nodes_;

  features_ = listener.features_;

  for (const auto &k : features_) {
    name_mappings_[k] = k;
  }

  // Simplify nodes
  simplify(nodes);

  // Deduplicate nodes
  deduplicate(nodes);
}

void Minia::simplify(std::vector<std::shared_ptr<Expr>> &all_nodes) {
  std::unordered_map<std::string, std::shared_ptr<Expr>> dict;

  for (auto &node : all_nodes) {
    if (node->type == ExprType::kExprTypeVariable) {
      bool literal = true;
      auto ptr = std::dynamic_pointer_cast<Variable>(node);
      // Check if all arguments are literals
      for (auto &arg : ptr->args) {
        arg = dict[arg->name];
        if (arg->type != ExprType::kExprTypeLiteral) {
          literal = false;
          break;
        }
      }

      if (!literal) {
        dict[node->name] = node;
        continue;
      }

      std::string func =
          ptr->func + ":" + std::to_string(ptr->args.size()) + "=[";
      std::vector<FeaturePtr> args;

      for (size_t j = 0; j < ptr->args.size(); ++j) {
        auto tmp = std::dynamic_pointer_cast<Literal>(ptr->args[j]);
        func += (j > 0 ? "," : "") +
                std::to_string(static_cast<int>(tmp->value->type));
        args.push_back(tmp->value);
      }
      func += "]";

      auto it = builtins.find(func);
      if (it != builtins.end()) {
        node = std::make_shared<Literal>(ptr->name, it->second(args));
      } else {
        throw std::runtime_error("Error: Built-in function not found for " +
                                 func);
      }
    }

    dict[node->name] = node;
  }
}

void Minia::deduplicate(std::vector<std::shared_ptr<Expr>> &all_nodes) {
  // Simplify expressions before deduplication
  simplify(all_nodes);

  // Maps expression names to their unique expression pointers
  std::unordered_map<std::string, std::shared_ptr<Expr>> name_mappings;
  // Stores unique expression nodes
  std::vector<std::shared_ptr<Expr>> unique_nodes;

  // Lambda function to check equality of two expressions
  std::function<bool(const std::shared_ptr<Expr> &,
                     const std::shared_ptr<Expr> &)>
      are_expressions_equal = [&](const std::shared_ptr<Expr> &expr_a,
                                  const std::shared_ptr<Expr> &expr_b) -> bool {
    if (!expr_a || !expr_b || expr_a->type != expr_b->type) {
      return false;
    }

    const ExprType &type = expr_a->type;
    if (type == ExprType::kExprTypeVariable) {
      auto var_a = std::dynamic_pointer_cast<Variable>(expr_a);
      auto var_b = std::dynamic_pointer_cast<Variable>(expr_b);

      if (var_a->func != var_b->func ||
          var_a->args.size() != var_b->args.size()) {
        return false;
      }

      // Recursively check equality of arguments
      for (size_t i = 0; i < var_a->args.size(); ++i) {
        if (!are_expressions_equal(var_a->args[i], var_b->args[i])) {
          return false;
        }
      }
      return true;
    } else if (type == ExprType::kExprTypeColumn) {
      return expr_a->name == expr_b->name;
    } else if (type == ExprType::kExprTypeLiteral) {
      auto lit_a = std::dynamic_pointer_cast<Literal>(expr_a);
      auto lit_b = std::dynamic_pointer_cast<Literal>(expr_b);
      return *(lit_a->value) == *(lit_b->value);
    }
    return false;
  };

  // Deduplicate expressions
  for (const auto &node : all_nodes) {
    bool is_duplicate = false;
    for (const auto &existing_node : unique_nodes) {
      if (are_expressions_equal(node, existing_node)) {
        name_mappings[node->name] = existing_node;
        is_duplicate = true;
        break;
      }
    }
    if (!is_duplicate) {
      unique_nodes.push_back(node);
      name_mappings[node->name] = node;
    }
  }

  // Update name mappings for deduplicated expressions
  for (const auto &kv : name_mappings) {
    name_mappings_[kv.first] = kv.second->name;
  }

  // Process unique variable expressions into operations
  for (const auto &node : unique_nodes) {
    if (node->type != ExprType::kExprTypeVariable) {
      // record all literal values
      if (node->type == ExprType::kExprTypeLiteral) {
        bool status = false;
        for (const std::string &fea : features_) {
          if (node->name == fea) {
            status = true;
            break;
          }
        }
        if (status) {
          auto var = std::dynamic_pointer_cast<Literal>(node);
          literals_[var->name] = var->value;
        }
      }
      continue;
    }
    auto var = std::dynamic_pointer_cast<Variable>(node);

    std::vector<IndexedVar> vars;
    std::vector<FeaturePtr> args(var->args.size(), nullptr);

    for (size_t i = 0; i < var->args.size(); ++i) {
      if (var->args[i]->type == ExprType::kExprTypeColumn) {
        vars.emplace_back(i, var->args[i]->name);
      } else if (var->args[i]->type == ExprType::kExprTypeLiteral) {
        auto tmp = std::dynamic_pointer_cast<Literal>(var->args[i]);
        args[i] = tmp->value;
      } else if (var->args[i]->type == ExprType::kExprTypeVariable) {
        auto tmp = std::dynamic_pointer_cast<Variable>(var->args[i]);
        vars.emplace_back(i, name_mappings_[tmp->name]);
      }
    }
    ops_.emplace_back(Op{var->name, var->func, vars, args});
  }
}

const std::string
Minia::Op::get_func(const std::vector<FeaturePtr> &my_args) const {
  std::string name = func + ":" + std::to_string(my_args.size()) + "=[";
  for (size_t j = 0; j < my_args.size(); ++j) {
    name +=
        (j > 0 ? "," : "") + std::to_string(static_cast<int>(my_args[j]->type));
  }
  name += "]";
  return name;
}

void Minia::Op::operator()(Features &features) const {
  std::vector<FeaturePtr> copy_args = args;

  for (const auto &var : vars) {
    copy_args[std::get<0>(var)] = features.get(std::get<1>(var));
  }

  const std::string name = get_func(copy_args);

  auto it = builtins.find(name);
  if (it != builtins.end()) {
    features.insert(out, it->second(copy_args));
  } else {
    throw std::runtime_error("Error: Built-in function not found for " + name);
  }
}
} // namespace minia