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

#ifndef GO_HPP_
#define GO_HPP_

#include <iostream>
#include <string>
#include <vector>
namespace minia {

/**
 * @struct GoString
 * @brief Mirrors Go's string type layout (pointer + length)
 *
 * Memory layout must exactly match Go's runtime.stringHeader structure:
 * - ptr: Pointer to character data (not necessarily null-terminated)
 * - len: Length of string in bytes
 */
struct GoString {
  const char *ptr; ///< Pointer to string data (read-only from Go side)
  size_t len;      ///< Length of string in bytes

  /// @brief Default constructor creates empty string
  GoString() : ptr(nullptr), len(0) {}

  /// @brief Construct from C++ std::string
  /// @param str Input string to copy
  explicit GoString(const std::string &str)
      : ptr(str.data()), len(str.size()) {}

  /// @brief Assignment operator (shallow copy)
  GoString &operator=(const std::string &str) {
    ptr = str.data();
    len = str.size();
    return *this;
  }

  /**
   * @brief Destructor
   */
  ~GoString() = default;
};

/**
 * @brief Compatible representation of Go slice in C++
 *
 * This template structure matches Go's slice memory layout to allow direct
 * interoperability between C++ and Go
 *
 * @tparam T The type of elements stored in the slice
 */
template <typename T> struct GoSlice {
  const T *ptr; ///< Pointer to the underlying array
  size_t len;   ///< Number of elements in the slice
  size_t cap;   ///< Capacity of the underlying array

  /**
   * @brief Default constructor
   */
  GoSlice() : ptr(nullptr), len(0), cap(0) {}

  /**
   * @brief Constructor from std::vector
   * @param vec The vector to shallow copy
   */
  explicit GoSlice(const std::vector<T> &vec)
      : ptr(vec.data()), len(vec.size()), cap(vec.size()) {}

  /**
   * @brief Destructor
   */
  ~GoSlice() = default;
};

/**
 * @brief Specialization of GoSlice for GoString type
 *
 * This specialization handles GoString elements properly, ensuring correct
 * memory management and compatibility with Go
 */
template <> struct GoSlice<GoString> {
  GoString *ptr; ///< Pointer to the underlying array of GoStrings
  size_t len;    ///< Number of elements in the slice
  size_t cap;    ///< Capacity of the underlying array

  /**
   * @brief Default constructor
   */
  GoSlice() : ptr(nullptr), len(0), cap(0) {}

  /**
   * @brief Constructor from std::vector of std::string
   * @param vec The vector to copy
   */
  explicit GoSlice(const std::vector<std::string> &vec)
      : ptr(new GoString[vec.size()]), len(vec.size()), cap(vec.size()) {
    for (size_t i = 0; i < len; i++) {
      ptr[i] = vec[i];
    }
  }

  /**
   * @brief Destructor
   */
  ~GoSlice() { delete[] ptr; }
};

using Int64Slice = GoSlice<int64_t>;
using Float32Slice = GoSlice<float>;
using StringSlice = GoSlice<GoString>;

} // namespace minia

#endif // GO_HPP_
