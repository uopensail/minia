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

#ifndef MINIA_FEATURE_H_
#define MINIA_FEATURE_H_

#pragma once

#include "common.h"
#include "json.hpp"
#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

namespace minia {

using json = nlohmann::json;

/**
 * @brief Variant type representing different possible data types.
 */
using Value = std::variant<int64_t, float, std::string, std::vector<int64_t>,
                           std::vector<float>, std::vector<std::string>>;

/**
 * @brief Macro to register a C++ type with its corresponding DataType enum
 * value.
 */
#define REGISTER_TYPE_ID(CppType, EnumValue)                                   \
  template <> struct TypeID<CppType> {                                         \
    static constexpr DataType value = EnumValue;                               \
  }

/**
 * @brief Template struct for obtaining the DataType of a C++ type.
 *
 * Provides a default value of DataType::kError for unsupported types.
 */
template <typename T> struct TypeID {
  static constexpr DataType value = DataType::kError;
};

// Register C++ types with their corresponding DataType enum values
REGISTER_TYPE_ID(int64_t, DataType::kInt64);
REGISTER_TYPE_ID(float, DataType::kFloat32);
REGISTER_TYPE_ID(std::string, DataType::kString);
REGISTER_TYPE_ID(std::vector<int64_t>, DataType::kInt64s);
REGISTER_TYPE_ID(std::vector<float>, DataType::kFloat32s);
REGISTER_TYPE_ID(std::vector<std::string>, DataType::kStrings);

#undef REGISTER_TYPE_ID

/**
 * @brief Represents a feature with a type and a value.
 */
struct Feature {
  Value value;   ///< The value of the feature
  DataType type; ///< The type of the feature

  /**
   * @brief Constructs a feature from a given value.
   *
   * Determines the DataType of the value using TypeID.
   *
   * @tparam T The type of the value.
   * @param val The value to initialize the feature with.
   */
  template <typename T>
  explicit Feature(T &&val)
      : value(std::forward<T>(val)),
        type(std::visit(
            [](auto &&arg) -> DataType {
              return TypeID<std::decay_t<decltype(arg)>>::value;
            },
            value)) {}

  /**
   * @brief Retrieves the value of the feature as a specified type.
   *
   * Validates the type before retrieval to ensure type safety.
   *
   * @tparam T The type to retrieve the value as.
   * @return The value cast to the specified type.
   * @throws std::runtime_error if the type is unsupported or mismatched.
   */
  template <typename T> const T &get() const {
    validate_type<T>();
    return std::get<T>(value);
  }

  /**
   * @brief Compares two features for equality.
   *
   * @param f The feature to compare with.
   * @return True if the features are equal, false otherwise.
   */
  bool operator==(const Feature &f) const {
    if (value.index() != f.value.index()) {
      return false;
    }

    return std::visit(
        [](auto &&arg1, auto &&arg2) -> bool {
          using T = std::decay_t<decltype(arg1)>;
          using U = std::decay_t<decltype(arg2)>;
          if constexpr (std::is_same_v<T, U>) {
            return arg1 == arg2;
          } else {
            return false;
          }
        },
        value, f.value);
  }

private:
  /**
   * @brief Validates the type of the feature.
   *
   * Checks if the type is supported and matches the expected type.
   *
   * @tparam T The expected type.
   * @throws std::runtime_error if the type is unsupported or mismatched.
   */
  template <typename T> void validate_type() const {
    if constexpr (TypeID<T>::value == DataType::kError) {
      throw std::runtime_error("Unsupported type");
    }
    if (TypeID<T>::value != type) {
      throw std::runtime_error("Type mismatch");
    }
  }
};

/**
 * @brief Deleter for Features, used with smart pointers.
 */
struct FeatureDeleter {
  bool del; ///< Flag to determine if the feature should be deleted

  /**
   * @brief Deletes the feature if the flag is set.
   *
   * @param ptr The feature pointer to delete.
   */
  void operator()(Feature *ptr) const {
    if (del && ptr) {
      delete ptr;
    }
  }
};

/// Alias for a shared pointer to a Feature
using FeaturePtr = std::shared_ptr<Feature>;

/**
 * @brief Stores and manages a collection of features.
 */
struct Features {
  std::unordered_map<std::string, FeaturePtr>
      values; ///< Map of feature names to feature pointers

  Features() = default;
  /**
   * @brief Constructs features from a JSON string.
   *
   * @param value The JSON string representing features.
   */
  explicit Features(const char *value) {
    const auto parse_feature_from_json =
        [](const nlohmann::json &data) -> FeaturePtr {
      FeaturePtr ptr = nullptr;
      DataType type = data["type"].get<DataType>();
      switch (type) {
      case DataType::kInt64:
        ptr = std::make_shared<Feature>(data["value"].get<int64_t>());
        break;
      case DataType::kFloat32:
        ptr = std::make_shared<Feature>(data["value"].get<float>());
        break;
      case DataType::kString:
        ptr = std::make_shared<Feature>(data["value"].get<std::string>());
        break;
      case DataType::kInt64s:
        ptr = std::make_shared<Feature>(
            data["value"].get<std::vector<int64_t>>());
        break;
      case DataType::kFloat32s:
        ptr =
            std::make_shared<Feature>(data["value"].get<std::vector<float>>());
        break;
      case DataType::kStrings:
        ptr = std::make_shared<Feature>(
            data["value"].get<std::vector<std::string>>());
        break;
      default:
        break;
      }
      return ptr;
    };

    const auto doc = nlohmann::json::parse(value);
    for (const auto &kv : doc.items()) {
      if (FeaturePtr p = parse_feature_from_json(kv.value()); p != nullptr) {
        values.emplace(kv.key(), std::move(p));
      }
    }
  }

  /**
   * @brief Constructs features from a JSON string.
   *
   * @param value The JSON string representing features.
   */
  explicit Features(const std::string &value) : Features(value.c_str()) {}

  /**
   * @brief Retrieves a feature by name.
   *
   * @param name The name of the feature to retrieve.
   * @return A shared pointer to the feature.
   */
  const FeaturePtr get(const std::string &name) const {
    auto it = values.find(name);
    return (it != values.end()) ? it->second : nullptr;
  }

  /**
   * @brief Inserts a feature into the collection.
   *
   * @param name The name of the feature.
   * @param feature The feature to insert.
   */
  void insert(const std::string &name, FeaturePtr feature) {
    values.emplace(name, std::move(feature));
  }
};

} // namespace minia

#endif // MINIA_FEATURE_H_