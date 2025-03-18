#include "grammar/minia.h"
#include <assert.h>

namespace minia {
/**
 * @brief Exit function for start rule.
 * @param ctx Context of the start rule.
 */
void MiniaListener::exitStart(miniaParser::StartContext *ctx) {
  if (exprs_.empty()) {
    throw std::runtime_error("Operation stack is empty at exitStart.");
  }
  std::string str = ctx->IDENTIFIER()->getText();
  auto expr = exprs_.top();
  expr->name = str;
  exprs_.pop();
}

/**
 * @brief Exit function for multiplication expression rule.
 * @param ctx Context of the multiplication expression rule.
 */
void MiniaListener::exitMulExpr(miniaParser::MulExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for multiplication.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "mul",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for string expression rule.
 * @param ctx Context of the string expression rule.
 */
void MiniaListener::exitStringExpr(miniaParser::StringExprContext *ctx) {
  std::string str = ctx->STRING()->getText();
  FeaturePtr f = std::shared_ptr<Feature>(
      new Feature{str.substr(1, str.size() - 2)}, FeatureDeleter{true});
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
  exprs_.push(ptr);
  g_node_count++;

  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for decimal list expression rule.
 * @param ctx Context of the decimal list expression rule.
 */
void MiniaListener::exitDecimalLISTExpr(
    miniaParser::DecimalLISTExprContext *ctx) {
  std::string str = ctx->getText();
  std::vector<float> result;

  if (!str.empty() && str.front() == '(' && str.back() == ')') {
    std::string numbers = str.substr(1, str.size() - 2);
    std::string currentNumber;

    for (char ch : numbers) {
      if (ch == ',') {
        // Trim whitespace from current number
        auto start = currentNumber.begin();
        while (start != currentNumber.end() && std::isspace(*start)) {
          ++start;
        }
        auto end = currentNumber.end();
        while (end != start && std::isspace(*(end - 1))) {
          --end;
        }
        currentNumber = std::string(start, end);

        try {
          float value = std::stof(currentNumber);
          result.push_back(value);
        } catch (const std::invalid_argument &e) {
          throw std::runtime_error("Invalid number format: " + currentNumber);
        } catch (const std::out_of_range &e) {
          throw std::runtime_error("Number out of range: " + currentNumber);
        }
        currentNumber.clear();
      } else {
        currentNumber += ch;
      }
    }

    // Handle the last number
    if (!currentNumber.empty()) {
      auto start = currentNumber.begin();
      while (start != currentNumber.end() && std::isspace(*start)) {
        ++start;
      }
      auto end = currentNumber.end();
      while (end != start && std::isspace(*(end - 1))) {
        --end;
      }
      currentNumber = std::string(start, end);

      try {
        float value = std::stof(currentNumber);
        result.push_back(value);
      } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Invalid number format: " + currentNumber);
      } catch (const std::out_of_range &e) {
        throw std::runtime_error("Number out of range: " + currentNumber);
      }
    }
  } else {
    throw std::runtime_error("Invalid format: " + str);
  }

  FeaturePtr f =
      std::shared_ptr<Feature>(new Feature{result}, FeatureDeleter{true});
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
  exprs_.push(ptr);
  g_node_count++;
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for column expression rule.
 * @param ctx Context of the column expression rule.
 */
void MiniaListener::exitColumnExpr(miniaParser::ColumnExprContext *ctx) {
  std::string str = ctx->IDENTIFIER()->getText();
  std::shared_ptr<Expr> ptr = std::make_shared<Column>(str);
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for subtraction expression rule.
 * @param ctx Context of the subtraction expression rule.
 */
void MiniaListener::exitSubExpr(miniaParser::SubExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for subtraction.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "sub",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for addition expression rule.
 * @param ctx Context of the addition expression rule.
 */
void MiniaListener::exitAddExpr(miniaParser::AddExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for addition.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "add",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for function expression rule.
 * @param ctx Context of the function expression rule.
 */
void MiniaListener::exitFuncExpr(miniaParser::FuncExprContext *ctx) {
  std::string str = ctx->IDENTIFIER()->getText();
  std::vector<std::shared_ptr<Expr>> args;

  for (size_t i = 0; i < ctx->expr().size(); i++) {
    auto arg = exprs_.top();
    args.push_back(arg);
    exprs_.pop();
  }

  std::reverse(args.begin(), args.end());

  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), str, args);

  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for decimal expression rule.
 * @param ctx Context of the decimal expression rule.
 */
void MiniaListener::exitDecimalExpr(miniaParser::DecimalExprContext *ctx) {
  std::string str = ctx->getText();
  try {
    float value = std::stof(str);
    FeaturePtr f =
        std::shared_ptr<Feature>(new Feature{value}, FeatureDeleter{true});
    std::shared_ptr<Expr> ptr =
        std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
    exprs_.push(ptr);
    nodes_.push_back(ptr);
    g_node_count++;
  } catch (const std::invalid_argument &e) {
    throw std::runtime_error("Invalid number format: " + str);
  } catch (const std::out_of_range &e) {
    throw std::runtime_error("Number out of range: " + str);
  }
}

/**
 * @brief Exit function for string list expression rule.
 * @param ctx Context of the string list expression rule.
 */
void MiniaListener::exitStringLISTExpr(
    miniaParser::StringLISTExprContext *ctx) {
  std::string str = ctx->getText();
  std::vector<std::string> result;

  if (!str.empty() && str.front() == '(' && str.back() == ')') {
    std::string values = str.substr(1, str.size() - 2);
    std::string current;

    for (char ch : values) {
      if (ch == ',') {
        // Trim whitespace from current string
        auto start = current.begin();
        while (start != current.end() && std::isspace(*start)) {
          ++start;
        }
        auto end = current.end();
        while (end != start && std::isspace(*(end - 1))) {
          --end;
        }
        current = std::string(start, end);

        result.push_back(current.substr(1, current.size() - 2));
        current.clear();
      } else {
        current += ch;
      }
    }

    if (!current.empty()) {
      auto start = current.begin();
      while (start != current.end() && std::isspace(*start)) {
        ++start;
      }
      auto end = current.end();
      while (end != start && std::isspace(*(end - 1))) {
        --end;
      }
      current = std::string(start, end);

      result.push_back(current.substr(1, current.size() - 2));
    }
  } else {
    throw std::runtime_error("Invalid format: " + str);
  }

  FeaturePtr f =
      std::shared_ptr<Feature>(new Feature{result}, FeatureDeleter{true});
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
  exprs_.push(ptr);
  nodes_.push_back(ptr);
  g_node_count++;
}

/**
 * @brief Exit function for runtime function expression rule.
 * @param ctx Context of the runtime function expression rule.
 */
void MiniaListener::exitRuntTimeFuncExpr(
    miniaParser::RuntTimeFuncExprContext *ctx) {
  std::string str = ctx->IDENTIFIER()->getText();
  std::shared_ptr<Expr> ptr =
      std::make_shared<Variable>("node:" + std::to_string(g_node_count), str,
                                 std::vector<std::shared_ptr<Expr>>{});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for integer expression rule.
 * @param ctx Context of the integer expression rule.
 */
void MiniaListener::exitIntegerExpr(miniaParser::IntegerExprContext *ctx) {
  std::string str = ctx->INTEGER()->getText();
  try {
    int64_t value = std::stoll(str);
    FeaturePtr f =
        std::shared_ptr<Feature>(new Feature{value}, FeatureDeleter{true});
    std::shared_ptr<Expr> ptr =
        std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
    exprs_.push(ptr);
    nodes_.push_back(ptr);
    g_node_count++;
  } catch (const std::invalid_argument &e) {
    throw std::runtime_error("Invalid number format: " + str);
  } catch (const std::out_of_range &e) {
    throw std::runtime_error("Number out of range: " + str);
  }
}

/**
 * @brief Exit function for division expression rule.
 * @param ctx Context of the division expression rule.
 */
void MiniaListener::exitDivExpr(miniaParser::DivExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for division.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "div",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for modulo expression rule.
 * @param ctx Context of the modulo expression rule.
 */
void MiniaListener::exitModExpr(miniaParser::ModExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for modulo operation.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "mod",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for integer list expression rule.
 * @param ctx Context of the integer list expression rule.
 */
void MiniaListener::exitIntegerLISTExpr(
    miniaParser::IntegerLISTExprContext *ctx) {
  std::string str = ctx->getText();
  std::vector<int64_t> result;

  if (!str.empty() && str.front() == '(' && str.back() == ')') {
    std::string numbers = str.substr(1, str.size() - 2);
    std::string currentNumber;

    for (char ch : numbers) {
      if (ch == ',') {
        // Trim whitespace from current number
        auto start = currentNumber.begin();
        while (start != currentNumber.end() && std::isspace(*start)) {
          ++start;
        }
        auto end = currentNumber.end();
        while (end != start && std::isspace(*(end - 1))) {
          --end;
        }
        currentNumber = std::string(start, end);

        try {
          int64_t value = std::stoll(currentNumber);
          result.push_back(value);
        } catch (const std::invalid_argument &) {
          throw std::runtime_error("Invalid number format: " + currentNumber);
        } catch (const std::out_of_range &) {
          throw std::runtime_error("Number out of range: " + currentNumber);
        }
        currentNumber.clear();
      } else {
        currentNumber += ch;
      }
    }

    if (!currentNumber.empty()) {
      auto start = currentNumber.begin();
      while (start != currentNumber.end() && std::isspace(*start)) {
        ++start;
      }
      auto end = currentNumber.end();
      while (end != start && std::isspace(*(end - 1))) {
        --end;
      }
      currentNumber = std::string(start, end);

      try {
        int64_t value = std::stoll(currentNumber);
        result.push_back(value);
      } catch (const std::invalid_argument &) {
        throw std::runtime_error("Invalid number format: " + currentNumber);
      } catch (const std::out_of_range &) {
        throw std::runtime_error("Number out of range: " + currentNumber);
      }
    }
  } else {
    throw std::runtime_error("Invalid format: " + str);
  }

  FeaturePtr f =
      std::shared_ptr<Feature>(new Feature{result}, FeatureDeleter{true});
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
  exprs_.push(ptr);
  nodes_.push_back(ptr);
  g_node_count++;
}
} // namespace minia