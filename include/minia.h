//
// `Minia` - A C++ tool for feature transformation and hashing
// Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
// This software is distributed under the GNU Affero General Public License
// (AGPL3.0) For more information, please visit:
// https://www.gnu.org/licenses/agpl-3.0.html
//
// This program is free software: you are free to redistribute and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Refer to the
// GNU Affero General Public License for more details.
//

#ifndef MINIA_H_
#define MINIA_H_

#include "grammar/minia.h"
#include "grammar/miniaLexer.h"
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>

namespace minia {
class Minia {
public:
  /**
   * @brief Constructs a Minia object by parsing a configuration file.
   *
   * This constructor initializes the Minia object by reading expressions and
   * features from a TOML configuration file. It parses the file, extracts the
   * necessary data, and handles any parsing errors.
   *
   * @param config_file The path to the configuration file.
   */
  explicit Minia(const std::string &config_file);

  ~Minia() = default;

  /**
   * @brief Executes all operations on the provided features.
   *
   * This function iterates over all operations stored in the `ops_` vector
   * and applies each operation to the `features` object, updating it
   * accordingly.
   *
   * @param features The features object to be updated by the operations.
   */
  void call(Features &features);

  /**
   * @brief Retrieves the list of feature names.
   *
   * This function returns a constant reference to the internal vector of
   * feature names, allowing users to access all feature names currently
   * managed by the Minia object.
   *
   * @return A constant reference to a vector of feature names.
   */
  const std::vector<std::string> &features() const { return features_; }

private:
  // Type alias for a variable indexed by an integer and associated with a
  // string
  using IndexedVar = std::tuple<int32_t, std::string>;

  /**
   * @brief Represents an operation with output, function, variables, and
   * arguments.
   *
   * This struct is used to encapsulate an operation, including its output
   * identifier, the function name, a list of indexed variables, and a list of
   * feature arguments.
   */
  struct Op {
    std::string out;  ///< The output identifier of the operation
    std::string func; ///< The function name associated with the operation
    std::vector<IndexedVar>
        vars; ///< A vector of indexed variables used in the operation
    std::vector<FeaturePtr> args; ///< A vector of feature pointers as arguments

    /**
     * @brief Constructs the function name based on the operation's function
     * and arguments.
     *
     * This function generates a unique name for the operation's function
     * based on the number and type of arguments provided.
     *
     * @param my_args A vector of feature pointers representing the
     * arguments.
     * @return A string representing the function name with argument types.
     */
    const std::string get_func(const std::vector<FeaturePtr> &my_args) const;

    /**
     * @brief Executes the operation on the provided features.
     *
     * This operator function updates the features map by executing the
     * built-in function associated with the operation's generated function
     * name.
     *
     * @param features The features map to be updated.
     * @throws std::runtime_error if the built-in function is not found.
     */
    void operator()(Features &features) const;
  };

  /**
   * @brief Removes duplicate expressions from a list and updates references
   * to them.
   *
   * This function iterates through a list of expressions, identifies
   * duplicates, and updates a renaming map to ensure that all references
   * point to the unique instances.
   *
   * @param all_nodes A vector of shared pointers to expressions to be
   * deduplicated.
   */
  void deduplicate(std::vector<std::shared_ptr<Expr>> &all_nodes);

  /**
   * @brief Simplifies a collection of expressions by replacing variable
   * expressions with literal expressions if all their arguments are literals.
   *
   * This function iterates through a list of expressions and attempts to
   * simplify variable expressions into literal expressions. It uses a
   * dictionary to map expression names to their respective expressions and
   * looks up built-in functions to perform the simplification.
   *
   * @param all_nodes A vector of shared pointers to expressions to be
   * simplified.
   * @throws std::runtime_error If a built-in function is not found for a
   * given expression.
   */
  void simplify(std::vector<std::shared_ptr<Expr>> &all_nodes);

  /**
   * @brief Parses a list of expressions, simplifies and deduplicates nodes.
   *
   * This function combines given expressions into a single string, parses it
   * using ANTLR4, and processes the resulting parse tree to simplify and
   * deduplicate nodes.
   *
   * @param exprs A vector of expressions to be parsed.
   */
  void parse(const std::vector<std::string> &exprs);

private:
  std::vector<std::string>
      features_; /**< A vector storing the names of features. */
  std::vector<Op>
      ops_; /**< A vector storing the operations to be applied to features. */
  std::unordered_map<std::string, std::string>
      name_mappings_; /**< A map for feature name mappings. */
};

} // namespace minia

#endif // MINIA_H_