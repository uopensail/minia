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

#ifndef MINIA_COMMON_H_
#define MINIA_COMMON_H_

#pragma once

#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace minia {

/**
 * @brief Enum representing various data types.
 *
 * This enum is used to define a set of data types with specific integer values
 * assigned to each type, facilitating easy identification and usage in data
 * handling.
 */
enum DataType : int8_t {
  kInt64 = 0,  ///< Represents a 64-bit integer
  kFloat32,    ///< Represents a 32-bit floating-point number
  kString,     ///< Represents a string
  kInt64s,     ///< Represents a vector of 64-bit integers
  kFloat32s,   ///< Represents a vector of 32-bit floating-point numbers
  kStrings,    ///< Represents a vector of strings
  kError = 127 ///< Represents an error state or undefined data type
};

} // namespace minia

#endif // MINIA_COMMON_H_