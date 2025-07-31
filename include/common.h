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

// #define ENABLE_GLOG

#ifdef ENABLE_GLOG
#include <glog/logging.h>
enum LogLevel {
  INFO = google::INFO,
  WARNING = google::WARNING,
  ERROR = google::ERROR,
  FATAL = google::FATAL
};

#else
#include <iostream>

/**
 * @enum LogLevel
 * @brief Defines an enumeration type for log levels.
 *
 * Log levels are used to control log output behavior. Includes the following
 * levels:
 * - INFO: Information level, used for outputting normal messages.
 * - WARNING: Warning level, used for outputting warning messages.
 * - ERROR: Error level, used for outputting error messages.
 * - FATAL: Fatal error level, used for outputting critical error messages.
 */
enum LogLevel { INFO, WARNING, ERROR, FATAL };

/**
 * @brief Outputs log information based on the log level.
 *
 * If the log level is INFO or WARNING, the log will be output to the standard
 * output stream `std::cout`. If the log level is ERROR or FATAL, the log will
 * be output to the standard error stream `std::cerr`.
 *
 * @param level Log level (INFO, WARNING, ERROR, FATAL).
 * @return Reference to the output stream for further appending log information.
 */
static inline std::ostream &LOG(LogLevel level) {
  switch (level) {
  case INFO:
  case WARNING:
    return std::cout; // Info and warning output to std::cout
  case ERROR:
  case FATAL:
    return std::cerr; // Error and fatal error output to std::cerr
  default:
    return std::cout; // Default output to std::cout
  }
}

#endif // ENABLE_GLOG

/**
 * @brief Initialize the minia logging system with specified directory and log
 * level
 *
 * This function initializes Google Logging (glog) for the minia application
 * with customized settings including log directory, log level, and output
 * configurations. The function is only active when ENABLE_GLOG is defined.
 *
 * @param log_dir Directory path where log files will be stored. If nullptr or
 * empty, logs will only output to stderr at ERROR level
 * @param log_level Minimum log level to output (0=INFO, 1=WARNING, 2=ERROR,
 * 3=FATAL)
 *
 * @note This function requires Google Logging library and ENABLE_GLOG macro to
 * be defined
 * @warning If log_dir is invalid or inaccessible, logging may fail silently
 *
 * @see https://github.com/google/glog for Google Logging documentation
 */
void enable_glog(const char *log_dir, int32_t log_level);

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