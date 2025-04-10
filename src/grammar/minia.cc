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
  features_.push_back(str);
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
void MiniaListener::exitDecimalListExpr(
    miniaParser::DecimalListExprContext *ctx) {
  std::string str = ctx->getText();
  std::vector<float> result;

  if (!str.empty() && str.front() == '[' && str.back() == ']') {
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
void MiniaListener::exitStringListExpr(
    miniaParser::StringListExprContext *ctx) {
  std::string str = ctx->getText();
  std::vector<std::string> result;

  if (!str.empty() && str.front() == '[' && str.back() == ']') {
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
void MiniaListener::exitIntegerListExpr(
    miniaParser::IntegerListExprContext *ctx) {
  std::string str = ctx->getText();
  std::vector<int64_t> result;

  if (!str.empty() && str.front() == '[' && str.back() == ']') {
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

/**
 * @brief Exit function for "and" expression rule.
 * @param ctx Context of the "and" expression rule.
 */
void MiniaListener::exitAndExpr(miniaParser::AndExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for and.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "and",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "true" expression rule.
 * @param ctx Context of the "true" expression rule.
 */
void MiniaListener::exitTrueExpr(miniaParser::TrueExprContext *ctx) {
  int64_t value = 1;
  FeaturePtr f =
      std::shared_ptr<Feature>(new Feature{value}, FeatureDeleter{true});
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
  exprs_.push(ptr);
  nodes_.push_back(ptr);
  g_node_count++;
}

/**
 * @brief Exit function for "or" expression rule.
 * @param ctx Context of the "or" expression rule.
 */
void MiniaListener::exitOrExpr(miniaParser::OrExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for or.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "or",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "false" expression rule.
 * @param ctx Context of the "false" expression rule.
 */
void MiniaListener::exitFalseExpr(miniaParser::FalseExprContext *ctx) {
  int64_t value = 0;
  FeaturePtr f =
      std::shared_ptr<Feature>(new Feature{value}, FeatureDeleter{true});
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(g_node_count), f);
  exprs_.push(ptr);
  nodes_.push_back(ptr);
  g_node_count++;
}

/**
 * @brief Exit function for "not" expression rule.
 * @param ctx Context of the "not" expression rule.
 */
void MiniaListener::exitNotExpr(miniaParser::NotExprContext *ctx) {
  if (exprs_.size() < 1) {
    throw std::runtime_error("Insufficient operands for not.");
  }
  auto expr = exprs_.top();
  exprs_.pop();

  std::shared_ptr<Expr> ptr =
      std::make_shared<Variable>("node:" + std::to_string(g_node_count), "not",
                                 std::vector<std::shared_ptr<Expr>>{expr});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "greater than or equal" expression rule.
 *
 * This function processes the "greater than or equal" (`>=`) expression
 * by creating a node in the expression tree and pushing it onto the stack.
 *
 * @param ctx Context of the "greater than or equal" expression rule.
 * @throws std::runtime_error if there are fewer than two operands on the stack.
 */
void MiniaListener::exitGreaterThanEqualExpr(
    miniaParser::GreaterThanEqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for gte.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "gte",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "less than or equal" expression rule.
 *
 * This function processes the "less than or equal" (`<=`) expression
 * by creating a node in the expression tree and pushing it onto the stack.
 *
 * @param ctx Context of the "less than or equal" expression rule.
 * @throws std::runtime_error if there are fewer than two operands on the stack.
 */
void MiniaListener::exitLessThanEqualExpr(
    miniaParser::LessThanEqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for lte.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "lte",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "less than" expression rule.
 *
 * This function processes the "less than" (`<`) expression
 * by creating a node in the expression tree and pushing it onto the stack.
 *
 * @param ctx Context of the "less than" expression rule.
 * @throws std::runtime_error if there are fewer than two operands on the stack.
 */
void MiniaListener::exitLessThanExpr(miniaParser::LessThanExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for lt.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "lt",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "greater than" expression rule.
 *
 * This function processes the "greater than" (`>`) expression
 * by creating a node in the expression tree and pushing it onto the stack.
 *
 * @param ctx Context of the "greater than" expression rule.
 * @throws std::runtime_error if there are fewer than two operands on the stack.
 */
void MiniaListener::exitGreaterThanExpr(
    miniaParser::GreaterThanExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for gt.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "gt",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "not equal" expression rule.
 *
 * This function processes the "not equal" (`!=`) expression
 * by creating a node in the expression tree and pushing it onto the stack.
 *
 * @param ctx Context of the "not equal" expression rule.
 * @throws std::runtime_error if there are fewer than two operands on the stack.
 */
void MiniaListener::exitNotEqualExpr(miniaParser::NotEqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for neq.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "neq",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for "equal" expression rule.
 *
 * This function processes the "equal" (`==`) expression
 * by creating a node in the expression tree and pushing it onto the stack.
 *
 * @param ctx Context of the "equal" expression rule.
 * @throws std::runtime_error if there are fewer than two operands on the stack.
 */
void MiniaListener::exitEqualExpr(miniaParser::EqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    throw std::runtime_error("Insufficient operands for eq.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(g_node_count), "eq",
      std::vector<std::shared_ptr<Expr>>{left, right});
  g_node_count++;
  exprs_.push(ptr);
  nodes_.push_back(ptr);
}

/**
 * @brief Exit function for function expression rule.
 * @param ctx Context of the function expression rule.
 */
void MiniaListener::exitFuncCall(miniaParser::FuncCallContext *ctx) {
  std::string str = ctx->IDENTIFIER()->getText();
  std::vector<std::shared_ptr<Expr>> args;

  miniaParser::ExprListContext *list = ctx->exprList();
  size_t size = 0;
  if (list) {
    std::vector<miniaParser::ExprContext *> exprs = list->expr();
    size = exprs.size();
    if (exprs_.size() < size) {
      throw std::runtime_error("Insufficient args for func call.");
    }
  }

  for (size_t i = 0; i < size; i++) {
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

} // namespace minia