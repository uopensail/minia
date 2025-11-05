#include "grammar/minia.h"

#include <assert.h>

#include "builtin.h"

namespace minia {
/**
 * @brief Exit function for start rule.
 * @param ctx Context of the start rule.
 */
void MiniaListener::exitStart(miniaParser::StartContext *ctx) {
  if (exprs_.empty()) {
    LOG(ERROR) << "Operation stack is empty at exitStart.\n";
    throw std::runtime_error("Operation stack is empty at exitStart.");
  }
  std::string str = ctx->IDENTIFIER()->getText();
  auto expr = exprs_.top();
  expr->name = str;
  exprs_.pop();
  nodes_.push_back(expr);
  features_.push_back(str);
}

/**
 * @brief Exit function for multiplication expression rule.
 * @param ctx Context of the multiplication expression rule.
 */
void MiniaListener::exitMulExpr([
    [maybe_unused]] miniaParser::MulExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for multiplication.\n";
    throw std::runtime_error("Insufficient operands for multiplication.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "mul",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for string expression rule.
 * @param ctx Context of the string expression rule.
 */
void MiniaListener::exitStringExpr(miniaParser::StringExprContext *ctx) {
  std::string str = ctx->STRING()->getText();
  FeaturePtr f = std::make_shared<Feature>(str.substr(1, str.size() - 2));
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
  exprs_.push(ptr);
  node_count_++;

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
          LOG(ERROR) << "Invalid number format: " << currentNumber << "\n";
          throw std::runtime_error("Invalid number format: " + currentNumber);
        } catch (const std::out_of_range &e) {
          LOG(ERROR) << "Number out of range:" << currentNumber << "\n";
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
        LOG(ERROR) << "Invalid number format: " << currentNumber << "\n";
        throw std::runtime_error("Invalid number format: " + currentNumber);
      } catch (const std::out_of_range &e) {
        LOG(ERROR) << "Number out of range:" << currentNumber << "\n";
        throw std::runtime_error("Number out of range: " + currentNumber);
      }
    }
  } else {
    LOG(ERROR) << "Invalid format: " << str << "\n";
    throw std::runtime_error("Invalid format: " + str);
  }

  FeaturePtr f = std::make_shared<Feature>(std::move(result));
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
  exprs_.push(ptr);
  node_count_++;
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
void MiniaListener::exitSubExpr([
    [maybe_unused]] miniaParser::SubExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for subtraction.\n";
    throw std::runtime_error("Insufficient operands for subtraction.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "sub",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for addition expression rule.
 * @param ctx Context of the addition expression rule.
 */
void MiniaListener::exitAddExpr([
    [maybe_unused]] miniaParser::AddExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for addition.\n";
    throw std::runtime_error("Insufficient operands for addition.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "add",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for decimal expression rule.
 * @param ctx Context of the decimal expression rule.
 */
void MiniaListener::exitDecimalExpr(miniaParser::DecimalExprContext *ctx) {
  std::string str = ctx->getText();
  try {
    float value = std::stof(str);
    FeaturePtr f = std::make_shared<Feature>(std::move(value));

    std::shared_ptr<Expr> ptr =
        std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
    exprs_.push(ptr);
    node_count_++;
  } catch (const std::invalid_argument &e) {
    LOG(ERROR) << "Invalid number format:" << str << "\n";
    throw std::runtime_error("Invalid number format: " + str);
  } catch (const std::out_of_range &e) {
    LOG(ERROR) << "Number out of range: " << str << "\n";
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
    LOG(ERROR) << "Invalid format: " << str << "\n";
    throw std::runtime_error("Invalid format: " + str);
  }

  FeaturePtr f = std::make_shared<Feature>(std::move(result));

  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
  exprs_.push(ptr);
  node_count_++;
}

/**
 * @brief Exit function for integer expression rule.
 * @param ctx Context of the integer expression rule.
 */
void MiniaListener::exitIntegerExpr(miniaParser::IntegerExprContext *ctx) {
  std::string str = ctx->INTEGER()->getText();
  try {
    int64_t value = std::stoll(str);

    FeaturePtr f = std::make_shared<Feature>(std::move(value));
    std::shared_ptr<Expr> ptr =
        std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
    exprs_.push(ptr);
    node_count_++;
  } catch (const std::invalid_argument &e) {
    LOG(ERROR) << "Invalid number format: " << str << "\n";
    throw std::runtime_error("Invalid number format: " + str);
  } catch (const std::out_of_range &e) {
    LOG(ERROR) << "Number out of range: " << str << "\n";
    throw std::runtime_error("Number out of range: " + str);
  }
}

/**
 * @brief Exit function for division expression rule.
 * @param ctx Context of the division expression rule.
 */
void MiniaListener::exitDivExpr([
    [maybe_unused]] miniaParser::DivExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for division.\n";
    throw std::runtime_error("Insufficient operands for division.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "div",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for modulo expression rule.
 * @param ctx Context of the modulo expression rule.
 */
void MiniaListener::exitModExpr([
    [maybe_unused]] miniaParser::ModExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for modulo operation.\n";
    throw std::runtime_error("Insufficient operands for modulo operation.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "mod",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
          LOG(ERROR) << "Invalid number format: " << currentNumber << "\n";
          throw std::runtime_error("Invalid number format: " + currentNumber);
        } catch (const std::out_of_range &) {
          LOG(ERROR) << "Number out of range: " << currentNumber << "\n";
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
        LOG(ERROR) << "Invalid number format: " << currentNumber << "\n";
        throw std::runtime_error("Invalid number format: " + currentNumber);
      } catch (const std::out_of_range &) {
        LOG(ERROR) << "Number out of range: " << currentNumber << "\n";
        throw std::runtime_error("Number out of range: " + currentNumber);
      }
    }
  } else {
    LOG(ERROR) << "Invalid format: " << str << "\n";
    throw std::runtime_error("Invalid format: " + str);
  }

  FeaturePtr f = std::make_shared<Feature>(std::move(result));
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
  exprs_.push(ptr);
  node_count_++;
}

/**
 * @brief Exit function for "and" expression rule.
 * @param ctx Context of the "and" expression rule.
 */
void MiniaListener::exitAndExpr([
    [maybe_unused]] miniaParser::AndExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for and.\n";
    throw std::runtime_error("Insufficient operands for and.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "and",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for "true" expression rule.
 * @param ctx Context of the "true" expression rule.
 */
void MiniaListener::exitTrueExpr([
    [maybe_unused]] miniaParser::TrueExprContext *ctx) {
  int64_t value = 1;
  FeaturePtr f = std::make_shared<Feature>(std::move(value));
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
  exprs_.push(ptr);
  node_count_++;
}

/**
 * @brief Exit function for "or" expression rule.
 * @param ctx Context of the "or" expression rule.
 */
void MiniaListener::exitOrExpr([
    [maybe_unused]] miniaParser::OrExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for or.\n";
    throw std::runtime_error("Insufficient operands for or.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "or",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for "false" expression rule.
 * @param ctx Context of the "false" expression rule.
 */
void MiniaListener::exitFalseExpr([
    [maybe_unused]] miniaParser::FalseExprContext *ctx) {
  int64_t value = 0;
  FeaturePtr f = std::make_shared<Feature>(std::move(value));
  std::shared_ptr<Expr> ptr =
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f);
  exprs_.push(ptr);
  node_count_++;
}

/**
 * @brief Exit function for "not" expression rule.
 * @param ctx Context of the "not" expression rule.
 */
void MiniaListener::exitNotExpr([
    [maybe_unused]] miniaParser::NotExprContext *ctx) {
  if (exprs_.size() < 1) {
    LOG(ERROR) << "Insufficient operands for not.\n";
    throw std::runtime_error("Insufficient operands for not.");
  }
  auto expr = exprs_.top();
  exprs_.pop();

  std::shared_ptr<Expr> ptr =
      std::make_shared<Variable>("node:" + std::to_string(node_count_), "not",
                                 std::vector<std::shared_ptr<Expr>>{expr});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

/**
 * @brief Exit function for "-" expression rule.
 * @param ctx Context of the "-" expression rule.
 */
void MiniaListener::exitNegExpr([
    [maybe_unused]] miniaParser::NegExprContext *ctx) {
  if (exprs_.size() < 1) {
    LOG(ERROR) << "Insufficient operands for `-`.\n";
    throw std::runtime_error("Insufficient operands for `-`.");
  }
  auto expr = exprs_.top();
  exprs_.pop();

  std::vector<std::shared_ptr<Expr>> args;

  int64_t value = 0;
  FeaturePtr f = std::make_shared<Feature>(std::move(value));
  args.push_back(
      std::make_shared<Literal>("node:" + std::to_string(node_count_), f));
  node_count_++;
  args.push_back(expr);
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "sub", args);
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
void MiniaListener::exitGreaterThanEqualExpr([
    [maybe_unused]] miniaParser::GreaterThanEqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for gte.\n";
    throw std::runtime_error("Insufficient operands for gte.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "gte",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
void MiniaListener::exitLessThanEqualExpr([
    [maybe_unused]] miniaParser::LessThanEqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for lte.\n";
    throw std::runtime_error("Insufficient operands for lte.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "lte",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
void MiniaListener::exitLessThanExpr([
    [maybe_unused]] miniaParser::LessThanExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for lt.\n";
    throw std::runtime_error("Insufficient operands for lt.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "lt",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
void MiniaListener::exitGreaterThanExpr([
    [maybe_unused]] miniaParser::GreaterThanExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for gt.\n";
    throw std::runtime_error("Insufficient operands for gt.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "gt",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
void MiniaListener::exitNotEqualExpr([
    [maybe_unused]] miniaParser::NotEqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for neq.\n";
    throw std::runtime_error("Insufficient operands for neq.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "neq",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
void MiniaListener::exitEqualExpr([
    [maybe_unused]] miniaParser::EqualExprContext *ctx) {
  if (exprs_.size() < 2) {
    LOG(ERROR) << "Insufficient operands for eq.\n";
    throw std::runtime_error("Insufficient operands for eq.");
  }
  auto right = exprs_.top();
  exprs_.pop();
  auto left = exprs_.top();
  exprs_.pop();
  std::shared_ptr<Expr> ptr = std::make_shared<Variable>(
      "node:" + std::to_string(node_count_), "eq",
      std::vector<std::shared_ptr<Expr>>{left, right});
  node_count_++;
  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
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
      LOG(ERROR) << "Insufficient args for func call.\n";
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
      "node:" + std::to_string(node_count_), str, args);
  node_count_++;

  ptr = caluc(ptr);
  exprs_.push(ptr);

  if (ptr->type != ExprType::kExprTypeLiteral) {
    nodes_.push_back(ptr);
  }
}

std::shared_ptr<Expr> MiniaListener::caluc(std::shared_ptr<Expr> expr) {
  if (expr->type != ExprType::kExprTypeVariable) {
    return expr;
  }

  std::shared_ptr<Variable> func = std::dynamic_pointer_cast<Variable>(expr);

  // particular process `and` / `or` / `not`
  if (func->name == "and") {
    if (func->args[0]->type == ExprType::kExprTypeLiteral) {
      std::shared_ptr<Literal> argv =
          std::dynamic_pointer_cast<Literal>(func->args[0]);
      if (argv->value->get<int64_t>() == 1) {
        return func->args[1];
      } else {
        int64_t value = 0;
        FeaturePtr f = std::make_shared<Feature>(std::move(value));
        std::shared_ptr<Expr> ptr = std::make_shared<Literal>(func->name, f);
        return ptr;
      }
    } else if (func->args[1]->type == ExprType::kExprTypeLiteral) {
      std::shared_ptr<Literal> argv =
          std::dynamic_pointer_cast<Literal>(func->args[1]);
      if (argv->value->get<int64_t>() == 1) {
        return func->args[0];
      } else {
        int64_t value = 0;
        FeaturePtr f = std::make_shared<Feature>(std::move(value));
        std::shared_ptr<Expr> ptr = std::make_shared<Literal>(func->name, f);
        return ptr;
      }
    }
    return func;
  } else if (func->name == "or") {
    if (func->args[0]->type == ExprType::kExprTypeLiteral) {
      std::shared_ptr<Literal> argv =
          std::dynamic_pointer_cast<Literal>(func->args[0]);
      if (argv->value->get<int64_t>() == 0) {
        return func->args[1];
      } else {
        int64_t value = 1;
        FeaturePtr f = std::make_shared<Feature>(std::move(value));
        std::shared_ptr<Expr> ptr = std::make_shared<Literal>(func->name, f);
        return ptr;
      }
    } else if (func->args[1]->type == ExprType::kExprTypeLiteral) {
      std::shared_ptr<Literal> argv =
          std::dynamic_pointer_cast<Literal>(func->args[1]);
      if (argv->value->get<int64_t>() == 0) {
        return func->args[0];
      } else {
        int64_t value = 1;
        FeaturePtr f = std::make_shared<Feature>(std::move(value));
        std::shared_ptr<Expr> ptr = std::make_shared<Literal>(func->name, f);
        return ptr;
      }
      return func;
    }
  } else if (func->name == "not") {
    if (func->args[0]->type == ExprType::kExprTypeLiteral) {
      int64_t value = 0;
      std::shared_ptr<Literal> argv =
          std::dynamic_pointer_cast<Literal>(func->args[0]);
      if (argv->value->get<int64_t>() == 0) {
        value = 1;
      }
      FeaturePtr f = std::make_shared<Feature>(std::move(value));
      std::shared_ptr<Expr> ptr = std::make_shared<Literal>(func->name, f);
      return ptr;
    }
    return func;
  }

  bool literal = true;
  for (const auto &argv : func->args) {
    if (argv->type != ExprType::kExprTypeLiteral) {
      literal = false;
      break;
    }
  }

  if (!literal) {
    return expr;
  }

  std::string name =
      func->func + ":" + std::to_string(func->args.size()) + "=[";
  std::vector<FeaturePtr> args;

  for (size_t j = 0; j < func->args.size(); ++j) {
    auto tmp = std::dynamic_pointer_cast<Literal>(func->args[j]);
    name +=
        (j > 0 ? "," : "") + std::to_string(static_cast<int>(tmp->value->type));
    args.push_back(tmp->value);
  }
  name += "]";

  auto it = builtins.find(name);
  if (it != builtins.end()) {
    return std::make_shared<Literal>(func->name, it->second(args));
  }
  LOG(ERROR) << "Error: Built-in function not found for: " << name << "\n";
  return func;
}
} // namespace minia