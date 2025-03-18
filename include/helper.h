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

#ifndef MINIA_HELPER_H_
#define MINIA_HELPER_H_

#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

namespace minia {

// Helper structure to check if a type is std::vector
template <typename T> struct is_vector : std::false_type {};

// Specialization for std::vector types
template <typename T, typename Alloc>
struct is_vector<std::vector<T, Alloc>> : std::true_type {};

// Alias for easier use of is_vector
template <typename T> constexpr bool is_vector_v = is_vector<T>::value;

/**
 * @brief Primary template to find the index of std::vector type in a type list.
 *
 * @tparam Index The current index being checked.
 * @tparam TargetType Unused in this context.
 * @tparam Types The list of types to search through.
 */
template <std::size_t Index, typename TargetType, typename... Types>
struct find_vector_index;

/**
 * @brief Specialization for when a std::vector type is found.
 *
 * This specialization checks if the current type is a std::vector.
 * If it is, it returns the current index.
 * Otherwise, it recursively checks the next type in the list.
 *
 * @tparam Index The current index being checked.
 * @tparam TargetType Unused in this context.
 * @tparam First The current type being checked.
 * @tparam Rest The remaining types in the list.
 */
template <std::size_t Index, typename TargetType, typename First,
          typename... Rest>
struct find_vector_index<Index, TargetType, First, Rest...> {
  static constexpr std::size_t value =
      is_vector_v<First>
          ? Index
          : find_vector_index<Index + 1, TargetType, Rest...>::value;
};

/**
 * @brief Specialization for when no std::vector type is found (end of
 * recursion).
 *
 * This specialization is used when the type list is exhausted and no
 * std::vector is found. It returns an invalid index to indicate the absence of
 * a std::vector type.
 *
 * @tparam Index The current index being checked.
 * @tparam TargetType Unused in this context.
 */
template <std::size_t Index, typename TargetType>
struct find_vector_index<Index, TargetType> {
  static constexpr std::size_t value =
      std::numeric_limits<std::size_t>::max(); ///< Returns an invalid index
};

/**
 * @brief A convenience function template to find the index of a std::vector
 * type in a type list.
 *
 * This function template uses find_vector_index to determine the index of a
 * std::vector type within a given list of types.
 *
 * @tparam Types The list of types to search through.
 * @return The index of the std::vector type, or
 * std::numeric_limits<std::size_t>::max() if not found.
 */
template <typename... Types> constexpr std::size_t get_vector_type_index() {
  return find_vector_index<0, void, Types...>::value;
}

/**
 * @brief Static assertion to ensure exactly one type is std::vector.
 *
 * This function template uses a fold expression to count how many types
 * in the parameter pack are std::vector types. It returns true if exactly
 * one type in the list is a std::vector, otherwise false.
 *
 * @tparam Types The list of types to check.
 * @return True if exactly one type is a std::vector, otherwise false.
 */
template <typename... Types> constexpr bool exactly_one_vector() {
  return (0 + ... + is_vector<std::decay_t<Types>>::value) == 1;
}

} // namespace minia

#endif // MINIA_HELPER_H_