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

#ifndef MINIA_BUILTIN_H_
#define MINIA_BUILTIN_H_

#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>

#include "MurmurHash3.h"
#include "feature.h"
#include "helper.h"

namespace minia {

constexpr int64_t mask = 0x0fffffffffffffffll;

/**
 * @brief Alias for a function wrapper that processes FeaturePtr arguments and
 * returns a FeaturePtr.
 */
using Function = std::function<FeaturePtr(const std::vector<FeaturePtr> &)>;

/**
 * @brief Helper function template that unpacks arguments and executes the
 * target function.
 * @tparam Func The function to be invoked
 * @tparam Ts... Argument types for the function
 * @tparam Is... Index sequence for argument unpacking
 * @param args Vector of input features
 * @return FeaturePtr wrapping the result of the function call
 *
 * @internal
 * This is an implementation detail that handles argument unpacking using index
 * sequences. Clients should not call this directly.
 */
template <auto Func, typename... Ts, size_t... Is>
auto helper(const std::vector<FeaturePtr> &args, std::index_sequence<Is...>) {
  return Func(
      args[Is]
          ->get<typename std::tuple_element<Is, std::tuple<Ts...>>::type>()...);
}

/**
 * @brief Invokes the target function with argument safety checks.
 * @tparam Func The function to be invoked
 * @tparam Ts... Argument types for the function
 * @param args Vector of input features
 * @return FeaturePtr containing result or nullptr if any argument is invalid
 *
 * Performs null checks on all arguments before invoking the target function.
 * Ensures type-safe argument conversion through the FeaturePtr get<>() method.
 */
template <auto Func, typename... Ts>
FeaturePtr invoke(const std::vector<FeaturePtr> &args) {
  if (std::any_of(args.begin(), args.begin() + sizeof...(Ts),
                  [](const auto &ptr) { return ptr == nullptr; })) {
    return nullptr;
  }

  return std::make_shared<Feature>(std::move(
      helper<Func, Ts...>(args, std::make_index_sequence<sizeof...(Ts)>{})));
}

/**
 * @brief Creates a Function wrapper for the specified operation.
 * @tparam Func The target function to wrap
 * @tparam Ts... Argument types for the function
 * @return Function object that can be called with FeaturePtr arguments
 *
 * The returned function handles argument validation and type conversion,
 * making it safe to use with heterogeneous feature types.
 */
template <auto Func, typename... Ts> Function get_func() {
  return [](const std::vector<FeaturePtr> &args) -> FeaturePtr {
    return invoke<Func, Ts...>(args);
  };
}

/**
 * @brief Computes Cartesian product of two vectors by applying a function.
 * @tparam Func Binary operation to apply (T0, T1) = ResultType
 * @tparam T0, T1 Type of input elements
 * @param a First input vector
 * @param b Second input vector
 * @return Vector of results from applying Func to all pairs (a_i, b_j)
 *
 * The cross product operation creates a result for every combination of
 * elements from the input vectors.
 */
template <auto Func, typename T0, typename T1>
auto cross_apply(const std::vector<T0> &a, const std::vector<T1> &b) {
  using ResultType = decltype(Func(std::declval<T0>(), std::declval<T1>()));
  std::vector<ResultType> ret;
  ret.reserve(a.size() * b.size()); // Pre-allocate memory for efficiency

  for (const auto &i : a) {
    for (const auto &j : b) {
      ret.push_back(Func(i, j));
    }
  }
  return ret;
}

/**
 * @brief Applies a binary function to pairs of elements from two vectors and
 * returns a vector of results.
 *
 * This function applies a specified binary function to corresponding elements
 * of two input vectors. The vectors must be of the same size; otherwise, an
 * exception is thrown.
 *
 * @tparam Func A binary function to apply to the elements of the vectors.
 * @tparam T0 The type of elements in the first vector.
 * @tparam T1 The type of elements in the second vector.
 * @param a The first input vector.
 * @param b The second input vector.
 * @return A vector containing the results of applying the binary function to
 * each pair of elements.
 * @throws std::invalid_argument If the input vectors do not have the same size.
 */
template <auto Func, typename T0, typename T1>
auto map_apply(const std::vector<T0> &a, const std::vector<T1> &b) {
  if (a.size() != b.size()) {
    LOG(ERROR) << "Input vectors must have the same size.\n";
    throw std::invalid_argument("Input vectors must have the same size.");
  }

  using ResultType = decltype(Func(std::declval<T0>(), std::declval<T1>()));
  std::vector<ResultType> ret;
  ret.reserve(a.size()); // Pre-allocate memory for efficiency

  for (size_t i = 0; i < a.size(); i++) {
    ret.push_back(Func(a[i], b[i]));
  }
  return ret;
}

/**
 * @brief Applies a function to each element of a vector within the given
 * arguments.
 *
 * @tparam Func The function to apply.
 * @tparam Types The types of the arguments, one of which must be a std::vector.
 * @param args The arguments, including exactly one std::vector.
 * @return A vector containing the results of applying the function to each
 * element.
 */
template <auto Func, typename... Types>
auto repeat_apply(const Types &... args) {
  static_assert(exactly_one_vector<Types...>(),
                "Exactly one type must be a std::vector.");

  constexpr const size_t index = get_vector_type_index<Types...>();
  auto tuple_args = std::make_tuple(args...);
  using VecType = std::decay_t<decltype(std::get<index>(tuple_args))>;
  const auto &vec = std::get<index>(tuple_args);

  using ElementType = typename VecType::value_type;
  using ResultType = decltype(
      Func((std::conditional_t<std::is_same_v<std::decay_t<Types>, VecType>,
                               ElementType, Types>())...));

  std::vector<ResultType> ret;
  ret.reserve(vec.size());

  for (const ElementType &elem : vec) {
    ret.push_back(
        Func(*static_cast<
             std::conditional_t<std::is_same_v<std::decay_t<Types>, VecType>,
                                ElementType, Types> *>(
            std::is_same_v<std::decay_t<decltype(args)>, VecType>
                ? (void *)(&elem)
                : (void *)&args)...));
  }
  return ret;
}

/**
 * @brief Returns the input value without any modification.
 *
 * This function acts as an identity function, returning the input
 * parameter exactly as it was passed in. It supports any type
 * that can be passed as a constant reference.
 *
 * @tparam T The type of the input parameter.
 * @param a The input value of type T, passed as a constant reference.
 * @return The same value as the input, of type T.
 */
template <typename T> T identity(const T &a) { return a; }

/**
 * @brief Basic arithmetic addition operation
 * @tparam T Numeric type
 * @param a First operand
 * @param b Second operand
 * @return Sum of a and b
 */
template <typename T> T add(const T &a, const T &b) { return a + b; }

/**
 * @brief Basic arithmetic subtraction operation
 * @tparam T Numeric type
 * @param a Minuend
 * @param b Subtrahend
 * @return Result of a - b
 */
template <typename T> T sub(const T &a, const T &b) { return a - b; }

/**
 * @brief Basic arithmetic multiplication operation
 * @tparam T Numeric type
 * @param a First factor
 * @param b Second factor
 * @return Product of a and b
 */
template <typename T> T mul(const T &a, const T &b) { return a * b; }

/**
 * @brief Basic arithmetic division operation
 * @tparam T Numeric type
 * @param a Dividend
 * @param b Divisor (must not be zero)
 * @return Quotient of a divided by b
 * @throws std::invalid_argument if b is zero
 */
template <typename T> T div(const T &a, const T &b) {
  if (b == 0)
    throw std::invalid_argument("Division by zero");
  return a / b;
}

/**
 * @brief Absolute value function
 * @tparam T Signed numeric type
 * @param x Input value
 * @return Absolute value of x
 */
template <typename T> T _abs(const T &x) { return x < 0 ? -x : x; }

/**
 * @brief Find minimum value in a vector
 * @tparam T Comparable type
 * @param src Input vector (non-empty)
 * @return Minimum value in the vector
 * @throws std::invalid_argument if src is empty
 */
template <typename T>
T min(const std::vector<T> &src) { // Changed from float to T
  if (src.empty()) {
    LOG(ERROR) << "Cannot find min of empty vector.\n";
    throw std::domain_error("Cannot find min of empty vector");
  }
  T ret = src[0];
  for (auto &v : src) {
    ret = std::min(ret, v);
  }
  return ret;
}

/**
 * @brief Find maximum value in a vector
 * @tparam T Comparable type
 * @param src Input vector (non-empty)
 * @return Maximum value in the vector
 * @throws std::invalid_argument if src is empty
 */
template <typename T> T max(const std::vector<T> &src) {
  if (src.empty()) {
    LOG(ERROR) << "Cannot find max of empty vector.\n";
    throw std::domain_error("Cannot find max of empty vector");
  }
  T ret = src[0];
  for (auto &v : src) {
    ret = std::max(ret, v);
  }
  return ret;
}

/**
 * @brief Calculate arithmetic mean
 * @tparam T Numeric type
 * @param src Input vector (non-empty)
 * @return Average value of elements
 * @throws std::invalid_argument if src is empty
 */
template <typename T> float average(const std::vector<T> &src) {
  if (src.empty()) {
    LOG(ERROR) << "Cannot find average of empty vector.\n";
    throw std::domain_error("Cannot compute average of empty vector");
  }

  T sum = std::accumulate(src.begin(), src.end(), T{0});
  return static_cast<float>(sum) / src.size();
}

/**
 * @brief Calculate population variance
 * @tparam T Numeric type
 * @param src Input vector
 * @return Variance of the population
 * @note Returns 0 for vectors with size <= 1
 */
template <typename T> float variance(const std::vector<T> &src) {
  if (src.size() <= 1)
    return 0.0f;

  const auto [sum, sq_sum] = std::accumulate(
      src.begin(), src.end(), std::pair<T, T>{0, 0},
      [](auto acc, const T &val) {
        return std::pair{acc.first + val, acc.second + val * val};
      });

  const float n = src.size();
  return (static_cast<float>(sq_sum) - (static_cast<float>(sum) * sum) / n) / n;
}

/**
 * @brief Calculate population standard deviation
 * @tparam T Numeric type
 * @param src Input vector
 * @return Standard deviation of the population
 */
template <typename T> float stddev(const std::vector<T> &src) {
  float var = variance<T>(src);
  return var > 0 ? sqrtf(var) : 0.0f;
}

/**
 * @brief Calculate L-n norm of a vector
 * @tparam T Numeric type
 * @param src Input vector
 * @param n Norm degree (must be >= 1)
 * @return L-n norm value
 */
template <typename T> float norm(const std::vector<T> &src, const float n) {
  float sum = std::accumulate(src.begin(), src.end(), 0.0f,
                              [n](float acc, const T &val) {
                                return acc + powf(static_cast<float>(val), n);
                              });
  return powf(sum, 1.0f / n);
}

/**
 * @brief Min-max normalization to [0,1] range
 * @tparam T Numeric type
 * @param v Value to normalize
 * @param min Minimum range value
 * @param max Maximum range value
 * @return Normalized value in [0,1]
 * @throws std::invalid_argument if min == max
 */
template <typename T> float min_max(const T &v, const T &min, const T &max) {
  if (min == max) {
    LOG(ERROR) << "Min and max cannot be equal.\n";
    throw std::invalid_argument("min and max cannot be equal");
  }
  return static_cast<float>(v - min) / static_cast<float>(max - min);
}

/**
 * @brief Binarize value based on threshold
 * @tparam T Comparable type
 * @param v Input value
 * @param threshold Decision boundary
 * @return 0 if v < threshold, 1 otherwise
 */
template <typename T> int64_t binarize(const T &v, const T &threshold) {
  return v < threshold ? 0 : 1;
}

/**
 * @brief Bucketize value into discrete bins
 * @tparam T Comparable type
 * @param v Input value
 * @param boundaries Sorted vector of bin boundaries
 * @return Index of the bucket the value belongs to
 * @note boundaries must be sorted in ascending order
 */
template <typename T>
int64_t bucketize(const T &v, const std::vector<T> &boundaries) {
  return std::upper_bound(boundaries.begin(), boundaries.end(), v) -
         boundaries.begin();
}

template <typename T>
std::vector<int64_t> repeat_bucketize(const std::vector<T> &v,
                                      const std::vector<T> &boundaries) {
  std::vector<int64_t> ret;
  ret.reserve(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    ret.push_back(bucketize<T>(v[i], boundaries));
  }
  return ret;
}

/**
 * @brief Normalize vector to unit norm
 * @tparam T Numeric type
 * @param src Input vector
 * @param norm Norm degree (must be >= 1)
 * @return Vector of normalized values
 * @throws std::invalid_argument if norm < 1
 */
template <typename T>
std::vector<float> normalize(const std::vector<T> &src, const float norm) {
  if (norm < 1) {
    LOG(ERROR) << "Norm degree must be >= 1.\n";
    throw std::invalid_argument("Norm degree must be >= 1");
  }
  const float norm_value = [&]() {
    float sum = 0.0f;
    for (const auto &v : src) {
      sum += powf(std::abs(static_cast<float>(v)), norm);
    }
    return powf(sum, 1.0f / norm);
  }();
  std::vector<float> dst;
  dst.reserve(src.size());
  for (const auto &v : src) {
    dst.push_back(static_cast<float>(v) / norm_value);
  }
  return dst;
}

/**
 * @brief Returns the first k elements from a vector
 * @tparam T Type of elements in the vector
 * @param src Source vector containing elements to select from
 * @param k Number of elements to select (will be clamped to [0, src.size()])
 * @return Vector containing the first min(k, src.size()) elements
 *
 * @note Time complexity: O(1) for number of elements copied (typically O(k))
 * @note If k is negative, returns an empty vector
 * @example
 * std::vector<int> v{1,2,3,4};
 * auto top2 = topk(v, 2);  // Returns {1,2}
 */
template <typename T>
std::vector<T> topk(const std::vector<T> &src, int64_t k) noexcept {
  k = std::clamp<int64_t>(k, 0, src.size());
  return {src.begin(), src.begin() + k};
}

/**
 * @brief Converts a 64-bit integer to floating-point value
 *
 * @param v The 64-bit integer value to convert
 * @return float The converted floating-point value
 *
 * @note This conversion may result in precision loss for values outside the
 *       range of float (typically ±3.4e±38)
 * @warning Floating-point numbers have limited precision for large integer
 * values
 * @exception noexcept Guaranteed not to throw
 */
float cast(int64_t v) noexcept;

/**
 * @brief Converts a numeric value to its string representation
 *
 * @tparam T Numeric type (integral or floating-point)
 * @param v The value to convert
 * @return std::string String representation of the value
 *
 * @note Supported types:
 * - All standard arithmetic types (int, float, etc.)
 *
 * @warning Not recommended for use with non-arithmetic types
 * @throws std::invalid_argument if type cannot be converted
 *
 * @code
 *   to_string(42);    // returns "42"
 *   to_string(3.14f); // returns "3.140000"
 * @endcode
 */
template <typename T> std::string to_string(const T &v) {
  static_assert(std::is_arithmetic_v<T>, "to_string requires arithmetic types");

  if constexpr (std::is_floating_point_v<T>) {
    // Handle floating-point precision
    return std::to_string(v);
  } else {
    // Default case for integral types
    return std::to_string(v);
  }
}

/**
 * @brief Sigmoid activation function
 * @param x Input value
 * @return Value in range (0, 1)
 */
float sigmoid(const float x);

/**
 * @brief Computes the smallest integer value not less than the given float.
 *
 * This function calculates the ceiling of the given float value, returning the
 * smallest integral value that is not less than the input.
 *
 * @param v The float value to compute the ceiling for.
 * @return The smallest integer not less than v.
 */
int64_t ceil(float v);

/**
 * @brief Rounds a float to the nearest integer.
 *
 * This function rounds the given float value to the nearest integer. If the
 * value is equidistant between two integers, it rounds away from zero.
 *
 * @param v The float value to round.
 * @return The integer closest to v.
 */
int64_t round(float v);

/**
 * @brief Computes the largest integer value not greater than the given float.
 *
 * This function calculates the floor of the given float value, returning the
 * largest integral value that is not greater than the input.
 *
 * @param v The float value to compute the floor for.
 * @return The largest integer not greater than v.
 */
int64_t floor(float v);

/**
 * @brief Computes the mathematical modulus of two integers
 *
 * Implements Euclidean modulus that always returns non-negative results
 * when the divisor is positive. The result satisfies:
 * (a / b) * b + a mod b == a
 *
 * @param dividend The number to be divided
 * @param divisor The divisor (must not be zero)
 * @return int64_t Result in range [0, |divisor|) when divisor > 0
 * @throws std::invalid_argument if divisor is zero
 *
 * @note Differs from C++ % operator for negative numbers
 * @example
 * mod(7, 3);   // returns 1
 * mod(-7, 3);  // returns 2
 * mod(7, -3);  // throws due to negative divisor
 */
int64_t mod(const int64_t a, const int64_t b);

/**
 * @brief Computes the z-score normalization of a value
 *
 * The z-score represents how many standard deviations an element is from the
 * mean. Formula: z = (x - μ) / σ
 *
 * @param value The input value to normalize
 * @param mean The mean (μ) of the distribution
 * @param std_dev The standard deviation (σ) of the distribution. Must be
 * positive.
 * @return float The z-score
 * @throws std::invalid_argument if standard deviation is not positive
 *
 * @note For non-Gaussian distributions, consider using robust scaling instead
 * @example
 * float z = z_score(75.0f, 100.0f, 15.0f);  // Returns -1.666...
 */
float z_score(const float value, const float mean, const float std_dev);

/**
 * @brief Computes the Box-Cox transformation of a value
 *
 * The Box-Cox transformation is defined as:
 * - (x^λ - 1)/λ when λ ≠ 0
 * - ln(x) when λ = 0
 *
 * @param value Input value to transform. Must be positive.
 * @param lambda Transformation parameter (λ)
 * @return float Transformed value
 * @throws std::invalid_argument if value is not positive
 * @throws std::domain_error for invalid lambda with negative value
 *
 * @note For computational stability, when |λ| < 1e-7, uses log approximation
 * @see https://en.wikipedia.org/wiki/Power_transform
 * @example
 * float bc = box_cox(4.0f, 0.5f);  // Returns (√4 - 1)/0.5 = 3.0
 */
float box_cox(const float v, const float lambda);

/**
 * @brief Performs logical AND operation between two boolean values.
 *
 * Logical AND returns true if both operands are true, otherwise false.
 *
 * @param a First boolean operand.
 * @param b Second boolean operand.
 * @return int64_t 1 if both `a` and `b` are true, 0 otherwise.
 */
int64_t _and(const int64_t a, const int64_t b);

/**
 * @brief Performs logical OR operation between two boolean values.
 *
 * Logical OR returns true if at least one of the operands is true.
 *
 * @param a First boolean operand.
 * @param b Second boolean operand.
 * @return int64_t 1 if either `a` or `b` is true, 0 otherwise.
 */
int64_t _or(const int64_t a, const int64_t b);

/**
 * @brief Performs logical NOT operation on a boolean value.
 *
 * Logical NOT returns true if the operand is false, and false if the operand is
 * true.
 *
 * @param v Input boolean value.
 * @return int64_t 1 if `v` is false, 0 if `v` is true.
 */
int64_t _not(const int64_t v);

/**
 * @brief Checks if a value is in a given list.
 *
 * Iterates through the list and returns 1 if the value is present, 0 otherwise.
 *
 * @tparam T Type of the value and list elements.
 * @param v Value to check.
 * @param list List of elements.
 * @return int64_t 1 if the value is in the list, 0 otherwise.
 */
template <typename T> int64_t contains(const std::vector<T> &list, const T v) {
  for (const T &item : list) {
    if (v == item) {
      return 1;
    }
  }
  return 0;
}

/**
 * @brief Checks if two values are equal.
 *
 * @tparam T Type of the values to compare.
 * @param a First value.
 * @param b Second value.
 * @return int64_t 1 if values are equal, 0 otherwise.
 */
template <typename T> int64_t equal(const T a, const T b) { return a == b; }

/**
 * @brief Checks if two values are not equal.
 *
 * @tparam T Type of the values to compare.
 * @param a First value.
 * @param b Second value.
 * @return int64_t 1 if values are not equal, 0 otherwise.
 */
template <typename T> int64_t not_equal(const T a, const T b) { return a != b; }

/**
 * @brief Checks if one value is less than another.
 *
 * @tparam T Type of the values to compare.
 * @param a First value.
 * @param b Second value.
 * @return int64_t 1 if a is less than b, 0 otherwise.
 */
template <typename T> int64_t less_than(const T a, const T b) { return a < b; }

/**
 * @brief Checks if one value is less than or equal to another.
 *
 * @tparam T Type of the values to compare.
 * @param a First value.
 * @param b Second value.
 * @return int64_t 1 if a is less than or equal to b, 0 otherwise.
 */
template <typename T> int64_t less_than_equal(const T a, const T b) {
  return a <= b;
}

/**
 * @brief Checks if one value is greater than another.
 *
 * @tparam T Type of the values to compare.
 * @param a First value.
 * @param b Second value.
 * @return int64_t 1 if a is greater than b, 0 otherwise.
 */
template <typename T> int64_t greater_than(const T a, const T b) {
  return a > b;
}

/**
 * @brief Checks if one value is greater than or equal to another.
 *
 * @tparam T Type of the values to compare.
 * @param a First value.
 * @param b Second value.
 * @return int64_t 1 if a is greater than or equal to b, 0 otherwise.
 */
template <typename T> int64_t greater_than_equal(const T a, const T b) {
  return a >= b;
}

/**
 * @brief Formats a timestamp into a date string
 * @param t Time value in seconds since epoch
 * @param fmt Format specification (default: "%Y-%m-%d")
 * @return Formatted date string according to the format specification
 * @throws std::invalid_argument if format string is invalid
 */
std::string format_date(time_t t, const std::string &fmt = "%Y-%m-%d");

/**
 * @brief Gets current year as a 4-digit string
 * @return Current year in "YYYY" format
 */
std::string year();
std::string year_(const int64_t timestamp);

/**
 * @brief Gets current month as a 2-digit string
 * @return Current month in "MM" format (01-12)
 */
std::string month();
std::string month_(const int64_t timestamp);

/**
 * @brief Gets current day of month as a 2-digit string
 * @return Current day in "DD" format (01-31)
 */
std::string day();
std::string day_(const int64_t timestamp);

/**
 * @brief Gets current date in local time
 * @return Current date in "YYYY-MM-DD" format
 */
std::string curdate();
std::string curdate_(const int64_t timestamp);

/**
 * @brief Gets current Unix timestamp
 * @return Number of seconds since 1970-01-01 00:00:00 UTC
 */
int64_t unix_timestamp();
int64_t unix_timestamp_(const int64_t timestamp);

/**
 * @brief Converts Unix timestamp to formatted date string
 * @param timestamp Seconds since 1970-01-01 00:00:00 UTC
 * @param format DateTime format string (e.g., "%Y-%m-%d %H:%M:%S")
 * @return Formatted datetime string
 * @throws std::invalid_argument for invalid timestamp or format
 */
std::string from_unixtime(const int64_t timestamp, const std::string &format);

/**
 * @brief Adds interval to a date
 * @param date_str Start date in "YYYY-MM-DD" format
 * @param interval Number of units to add
 * @param unit Interval unit (DAY, MONTH, YEAR)
 * @return Resulting date in "YYYY-MM-DD" format
 * @throws std::invalid_argument for invalid date or unit
 */
std::string date_add(const std::string &date_str, const int64_t interval,
                     const std::string &unit);
/**
 * @brief Subtracts interval from a date
 * @param date_str Start date in "YYYY-MM-DD" format
 * @param interval Number of units to subtract
 * @param unit Interval unit (DAY, MONTH, YEAR)
 * @return Resulting date in "YYYY-MM-DD" format
 * @throws std::invalid_argument for invalid date or unit
 */
std::string date_sub(const std::string &date_str, const int64_t interval,
                     const std::string &unit);
/**
 * @brief Calculates difference between two dates in days
 * @param date1 First date in "YYYY-MM-DD" format
 * @param date2 Second date in "YYYY-MM-DD" format
 * @return Number of days between date1 and date2 (date1 - date2)
 * @throws std::invalid_argument for invalid date formats
 */
int64_t datediff(const std::string &date1, const std::string &date2);

/**
 * @brief Reverses the characters in a string
 * @param s Input string to reverse
 * @return Reversed string
 */
std::string reverse(const std::string &s);

/**
 * @brief Converts string to uppercase
 * @param s Input string
 * @return Uppercase version of input string
 */
std::string upper(const std::string &s);

/**
 * @brief Converts string to lowercase
 * @param s Input string
 * @return Lowercase version of input string
 */
std::string lower(const std::string &s);

/**
 * @brief Extracts substring from a string
 * @param s Source string
 * @param start Starting position (0-based index)
 * @param len Number of characters to extract
 * @return Substring of specified length
 * @throws std::out_of_range for invalid start position
 */
std::string substr(const std::string &s, const int64_t start,
                   const int64_t len);

/**
 * @brief Concatenates two strings into one.
 *
 * This function takes two strings, `a` and `b`, and returns a new string
 * that is the result of concatenating `a` followed by `b`.
 *
 * @param a The first string to concatenate.
 * @param b The second string to concatenate.
 * @return A new string containing `a` followed by `b`.
 */
std::string concat(const std::string &a, const std::string &b);

/**
 * @brief Computes a 64-bit hash value for a given string using the MurmurHash3
 * algorithm.
 *
 * This function utilizes the MurmurHash3_x64_128 function to compute a 128-bit
 * hash of the input string and then returns the lower 64 bits masked with a
 * predefined mask.
 *
 * @param key The input string to hash.
 * @return A 64-bit integer hash value.
 */
int64_t mmh3(const std::string &key);

const std::unordered_map<std::string, Function> builtins = {
    {"hash:1=[2]", get_func<mmh3, std::string>()},
    {"hash:1=[5]", get_func<repeat_apply<mmh3, std::vector<std::string>>,
                            std::vector<std::string>>()},
    {"identity:1=[0]", get_func<identity<int64_t>, int64_t>()},
    {"identity:1=[1]", get_func<identity<float>, float>()},
    {"identity:1=[2]", get_func<identity<std::string>, std::string>()},
    {"identity:1=[3]",
     get_func<identity<std::vector<int64_t>>, std::vector<int64_t>>()},
    {"identity:1=[4]",
     get_func<identity<std::vector<float>>, std::vector<float>>()},
    {"identity:1=[5]",
     get_func<identity<std::vector<std::string>>, std::vector<std::string>>()},
    {"and:2=[0,0]", get_func<_and, int64_t, int64_t>()},
    {"or:2=[0,0]", get_func<_or, int64_t, int64_t>()},
    {"not:1=[0]", get_func<_not, int64_t>()},
    {"lt:2=[0,0]", get_func<less_than<int64_t>, int64_t, int64_t>()},
    {"lt:2=[1,1]", get_func<less_than<float>, float, float>()},
    {"lte:2=[0,0]", get_func<less_than_equal<int64_t>, int64_t, int64_t>()},
    {"lte:2=[1,1]", get_func<less_than_equal<float>, float, float>()},
    {"eq:2=[0,0]", get_func<equal<int64_t>, int64_t, int64_t>()},
    {"eq:2=[2,2]", get_func<equal<std::string>, std::string, std::string>()},
    {"neq:2=[0,0]", get_func<not_equal<int64_t>, int64_t, int64_t>()},
    {"neq:2=[2,2]",
     get_func<not_equal<std::string>, std::string, std::string>()},
    {"gt:2=[0,0]", get_func<greater_than<int64_t>, int64_t, int64_t>()},
    {"gt:2=[1,1]", get_func<greater_than<float>, float, float>()},
    {"gte:2=[0,0]", get_func<greater_than_equal<int64_t>, int64_t, int64_t>()},
    {"gte:2=[1,1]", get_func<greater_than_equal<float>, float, float>()},
    {"contains:2=[3,0]",
     get_func<contains<int64_t>, std::vector<int64_t>, int64_t>()},
    {"contains:2=[5,2]",
     get_func<contains<std::string>, std::vector<std::string>, std::string>()},
    {"add:2=[0,0]", get_func<add<int64_t>, int64_t, int64_t>()},
    {"add:2=[0,1]", get_func<add<float>, int64_t, float>()},
    {"add:2=[1,0]", get_func<add<float>, float, int64_t>()},
    {"add:2=[1,1]", get_func<add<float>, float, float>()},
    {"add:2=[0,3]",
     get_func<repeat_apply<add<int64_t>, int64_t, std::vector<int64_t>>,
              int64_t, std::vector<int64_t>>()},
    {"add:2=[3,0]",
     get_func<repeat_apply<add<int64_t>, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},
    {"add:2=[1,3]",
     get_func<repeat_apply<add<float>, float, std::vector<int64_t>>, float,
              std::vector<int64_t>>()},
    {"add:2=[3,1]",
     get_func<repeat_apply<add<float>, std::vector<int64_t>, float>,
              std::vector<int64_t>, float>()},
    {"add:2=[3,3]", get_func<map_apply<add<int64_t>, int64_t, int64_t>,
                             std::vector<int64_t>, std::vector<int64_t>>()},
    {"add:2=[1,4]",
     get_func<repeat_apply<add<float>, float, std::vector<float>>, float,
              std::vector<float>>()},
    {"add:2=[0,4]",
     get_func<repeat_apply<add<float>, int64_t, std::vector<float>>, int64_t,
              std::vector<float>>()},
    {"add:2=[4,1]",
     get_func<repeat_apply<add<float>, std::vector<float>, float>,
              std::vector<float>, float>()},
    {"add:2=[4,0]",
     get_func<repeat_apply<add<float>, std::vector<float>, int64_t>,
              std::vector<float>, int64_t>()},
    {"add:2=[4,4]", get_func<map_apply<add<float>, float, float>,
                             std::vector<float>, std::vector<float>>()},

    {"sub:2=[0,0]", get_func<sub<int64_t>, int64_t, int64_t>()},
    {"sub:2=[0,1]", get_func<sub<float>, int64_t, float>()},
    {"sub:2=[1,0]", get_func<sub<float>, float, int64_t>()},
    {"sub:2=[1,1]", get_func<sub<float>, float, float>()},
    {"sub:2=[0,3]",
     get_func<repeat_apply<sub<int64_t>, int64_t, std::vector<int64_t>>,
              int64_t, std::vector<int64_t>>()},
    {"sub:2=[3,0]",
     get_func<repeat_apply<sub<int64_t>, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},
    {"sub:2=[1,3]",
     get_func<repeat_apply<sub<float>, float, std::vector<int64_t>>, float,
              std::vector<int64_t>>()},
    {"sub:2=[3,1]",
     get_func<repeat_apply<sub<float>, std::vector<int64_t>, float>,
              std::vector<int64_t>, float>()},
    {"sub:2=[3,3]", get_func<map_apply<sub<int64_t>, int64_t, int64_t>,
                             std::vector<int64_t>, std::vector<int64_t>>()},
    {"sub:2=[1,4]",
     get_func<repeat_apply<sub<float>, float, std::vector<float>>, float,
              std::vector<float>>()},
    {"sub:2=[0,4]",
     get_func<repeat_apply<sub<float>, int64_t, std::vector<float>>, int64_t,
              std::vector<float>>()},
    {"sub:2=[4,1]",
     get_func<repeat_apply<sub<float>, std::vector<float>, float>,
              std::vector<float>, float>()},
    {"sub:2=[4,0]",
     get_func<repeat_apply<sub<float>, std::vector<float>, int64_t>,
              std::vector<float>, int64_t>()},
    {"sub:2=[4,4]", get_func<map_apply<sub<float>, float, float>,
                             std::vector<float>, std::vector<float>>()},

    {"mul:2=[0,0]", get_func<mul<int64_t>, int64_t, int64_t>()},
    {"mul:2=[0,1]", get_func<mul<float>, int64_t, float>()},
    {"mul:2=[1,0]", get_func<mul<float>, float, int64_t>()},
    {"mul:2=[1,1]", get_func<mul<float>, float, float>()},
    {"mul:2=[0,3]",
     get_func<repeat_apply<mul<int64_t>, int64_t, std::vector<int64_t>>,
              int64_t, std::vector<int64_t>>()},
    {"mul:2=[3,0]",
     get_func<repeat_apply<mul<int64_t>, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},
    {"mul:2=[1,3]",
     get_func<repeat_apply<mul<float>, float, std::vector<int64_t>>, float,
              std::vector<int64_t>>()},
    {"mul:2=[3,1]",
     get_func<repeat_apply<mul<float>, std::vector<int64_t>, float>,
              std::vector<int64_t>, float>()},
    {"mul:2=[3,3]", get_func<map_apply<mul<int64_t>, int64_t, int64_t>,
                             std::vector<int64_t>, std::vector<int64_t>>()},
    {"mul:2=[1,4]",
     get_func<repeat_apply<mul<float>, float, std::vector<float>>, float,
              std::vector<float>>()},
    {"mul:2=[0,4]",
     get_func<repeat_apply<mul<float>, int64_t, std::vector<float>>, int64_t,
              std::vector<float>>()},
    {"mul:2=[4,1]",
     get_func<repeat_apply<mul<float>, std::vector<float>, float>,
              std::vector<float>, float>()},
    {"mul:2=[4,0]",
     get_func<repeat_apply<mul<float>, std::vector<float>, int64_t>,
              std::vector<float>, int64_t>()},
    {"mul:2=[4,4]", get_func<map_apply<mul<float>, float, float>,
                             std::vector<float>, std::vector<float>>()},

    {"div:2=[0,0]", get_func<div<int64_t>, int64_t, int64_t>()},
    {"div:2=[0,1]", get_func<div<float>, int64_t, float>()},
    {"div:2=[1,0]", get_func<div<float>, float, int64_t>()},
    {"div:2=[1,1]", get_func<div<float>, float, float>()},
    {"div:2=[0,3]",
     get_func<repeat_apply<div<int64_t>, int64_t, std::vector<int64_t>>,
              int64_t, std::vector<int64_t>>()},
    {"div:2=[3,0]",
     get_func<repeat_apply<div<int64_t>, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},
    {"div:2=[1,3]",
     get_func<repeat_apply<div<float>, float, std::vector<int64_t>>, float,
              std::vector<int64_t>>()},
    {"div:2=[3,1]",
     get_func<repeat_apply<div<float>, std::vector<int64_t>, float>,
              std::vector<int64_t>, float>()},
    {"div:2=[3,3]", get_func<map_apply<div<int64_t>, int64_t, int64_t>,
                             std::vector<int64_t>, std::vector<int64_t>>()},
    {"div:2=[1,4]",
     get_func<repeat_apply<div<float>, float, std::vector<float>>, float,
              std::vector<float>>()},
    {"div:2=[0,4]",
     get_func<repeat_apply<div<float>, int64_t, std::vector<float>>, int64_t,
              std::vector<float>>()},
    {"div:2=[4,1]",
     get_func<repeat_apply<div<float>, std::vector<float>, float>,
              std::vector<float>, float>()},
    {"div:2=[4,0]",
     get_func<repeat_apply<div<float>, std::vector<float>, int64_t>,
              std::vector<float>, int64_t>()},
    {"div:2=[4,4]", get_func<map_apply<div<float>, float, float>,
                             std::vector<float>, std::vector<float>>()},

    {"div:2=[0,0]", get_func<div<int64_t>, int64_t, int64_t>()},
    {"div:2=[1,1]", get_func<div<float>, float, float>()},
    {"div:2=[0,3]",
     get_func<repeat_apply<div<int64_t>, int64_t, std::vector<int64_t>>,
              int64_t, std::vector<int64_t>>()},
    {"div:2=[3,0]",
     get_func<repeat_apply<div<int64_t>, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},
    {"div:2=[3,3]", get_func<map_apply<div<int64_t>, int64_t, int64_t>,
                             std::vector<int64_t>, std::vector<int64_t>>()},
    {"div:2=[1,4]",
     get_func<repeat_apply<div<float>, float, std::vector<float>>, float,
              std::vector<float>>()},
    {"div:2=[4,1]",
     get_func<repeat_apply<div<float>, std::vector<float>, float>,
              std::vector<float>, float>()},
    {"div:2=[4,4]", get_func<map_apply<div<float>, float, float>,
                             std::vector<float>, std::vector<float>>()},

    {"mod:2=[0,0]", get_func<mod, int64_t, int64_t>()},
    {"mod:2=[3,0]", get_func<repeat_apply<mod, std::vector<int64_t>, int64_t>,
                             std::vector<int64_t>, int64_t>()},

    {"abs:1=[0]", get_func<_abs<int64_t>, int64_t>()},
    {"abs:1=[1]", get_func<_abs<float>, float>()},
    {"abs:1=[3]", get_func<repeat_apply<_abs<int64_t>, std::vector<int64_t>>,
                           std::vector<int64_t>>()},
    {"abs:1=[4]", get_func<repeat_apply<_abs<float>, std::vector<float>>,
                           std::vector<float>>()},

    {"ceil:1=[1]", get_func<ceil, float>()},
    {"ceil:1=[4]",
     get_func<repeat_apply<ceil, std::vector<float>>, std::vector<float>>()},
    {"floor:1=[1]", get_func<floor, float>()},
    {"floor:1=[4]",
     get_func<repeat_apply<floor, std::vector<float>>, std::vector<float>>()},

    {"round:1=[1]", get_func<round, float>()},
    {"round:1=[4]",
     get_func<repeat_apply<round, std::vector<float>>, std::vector<float>>()},

    {"cosh:1=[1]", get_func<::coshf, float>()},
    {"cosh:1=[0]", get_func<::coshf, int64_t>()},
    {"cosh:1=[3]", get_func<repeat_apply<::coshf, std::vector<int64_t>>,
                            std::vector<int64_t>>()},
    {"cosh:1=[4]",
     get_func<repeat_apply<::coshf, std::vector<float>>, std::vector<float>>()},

    {"cos:1=[1]", get_func<::cosf, float>()},
    {"cos:1=[0]", get_func<::cosf, int64_t>()},
    {"cos:1=[3]", get_func<repeat_apply<::cosf, std::vector<int64_t>>,
                           std::vector<int64_t>>()},
    {"cos:1=[4]",
     get_func<repeat_apply<::cosf, std::vector<float>>, std::vector<float>>()},

    {"exp:1=[1]", get_func<::expf, float>()},
    {"exp:1=[0]", get_func<::expf, int64_t>()},
    {"exp:1=[3]", get_func<repeat_apply<::expf, std::vector<int64_t>>,
                           std::vector<int64_t>>()},
    {"exp:1=[4]",
     get_func<repeat_apply<::expf, std::vector<float>>, std::vector<float>>()},

    {"log:1=[1]", get_func<::logf, float>()},
    {"log:1=[0]", get_func<::logf, int64_t>()},
    {"log:1=[3]", get_func<repeat_apply<::logf, std::vector<int64_t>>,
                           std::vector<int64_t>>()},
    {"log:1=[4]",
     get_func<repeat_apply<::logf, std::vector<float>>, std::vector<float>>()},

    {"log10:1=[1]", get_func<::log10f, float>()},
    {"log10:1=[0]", get_func<::log10f, int64_t>()},
    {"log10:1=[3]", get_func<repeat_apply<::log10f, std::vector<int64_t>>,
                             std::vector<int64_t>>()},
    {"log10:1=[4]", get_func<repeat_apply<::log10f, std::vector<float>>,
                             std::vector<float>>()},

    {"log2:1=[1]", get_func<::log2f, float>()},
    {"log2:1=[0]", get_func<::log2f, int64_t>()},
    {"log2:1=[3]", get_func<repeat_apply<::log2f, std::vector<int64_t>>,
                            std::vector<int64_t>>()},
    {"log2:1=[4]",
     get_func<repeat_apply<::log2f, std::vector<float>>, std::vector<float>>()},

    {"sqrt:1=[1]", get_func<::sqrtf, float>()},
    {"sqrt:1=[0]", get_func<::sqrtf, int64_t>()},
    {"sqrt:1=[3]", get_func<repeat_apply<::sqrtf, std::vector<int64_t>>,
                            std::vector<int64_t>>()},
    {"sqrt:1=[4]",
     get_func<repeat_apply<::sqrtf, std::vector<float>>, std::vector<float>>()},

    {"sigmoid:1=[1]", get_func<sigmoid, float>()},
    {"sigmoid:1=[0]", get_func<sigmoid, int64_t>()},
    {"sigmoid:1=[3]", get_func<repeat_apply<sigmoid, std::vector<int64_t>>,
                               std::vector<int64_t>>()},
    {"sigmoid:1=[4]",
     get_func<repeat_apply<sigmoid, std::vector<float>>, std::vector<float>>()},

    {"sinh:1=[1]", get_func<::sinhf, float>()},
    {"sinh:1=[0]", get_func<::sinhf, int64_t>()},
    {"sinh:1=[3]", get_func<repeat_apply<::sinhf, std::vector<int64_t>>,
                            std::vector<int64_t>>()},
    {"sinh:1=[4]",
     get_func<repeat_apply<::sinhf, std::vector<float>>, std::vector<float>>()},

    {"sin:1=[1]", get_func<sinf, float>()},
    {"sin:1=[0]", get_func<sinf, int64_t>()},
    {"sin:1=[3]", get_func<repeat_apply<sinf, std::vector<int64_t>>,
                           std::vector<int64_t>>()},
    {"sin:1=[4]",
     get_func<repeat_apply<sinf, std::vector<float>>, std::vector<float>>()},

    {"tanh:1=[1]", get_func<::tanhf, float>()},
    {"tanh:1=[0]", get_func<::tanhf, int64_t>()},
    {"tanh:1=[3]", get_func<repeat_apply<::tanhf, std::vector<int64_t>>,
                            std::vector<int64_t>>()},
    {"tanh:1=[4]",
     get_func<repeat_apply<::tanhf, std::vector<float>>, std::vector<float>>()},

    {"pow:2=[0,0]", get_func<::powf, int64_t, int64_t>()},
    {"pow:2=[0,1]", get_func<::powf, int64_t, float>()},
    {"pow:2=[1,0]", get_func<::powf, float, int64_t>()},
    {"pow:2=[1,1]", get_func<::powf, float, float>()},
    {"pow:2=[3,0]",
     get_func<repeat_apply<::powf, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},
    {"pow:2=[4,0]", get_func<repeat_apply<::powf, std::vector<float>, int64_t>,
                             std::vector<float>, int64_t>()},
    {"pow:2=[3,1]", get_func<repeat_apply<::powf, std::vector<int64_t>, float>,
                             std::vector<int64_t>, float>()},
    {"pow:2=[4,1]", get_func<repeat_apply<::powf, std::vector<float>, float>,
                             std::vector<float>, float>()},

    {"avg:1=[3]", get_func<average<int64_t>, std::vector<int64_t>>()},
    {"avg:1=[4]", get_func<average<float>, std::vector<float>>()},

    {"max:1=[3]", get_func<max<int64_t>, std::vector<int64_t>>()},
    {"max:1=[4]", get_func<max<float>, std::vector<float>>()},

    {"min:1=[3]", get_func<min<int64_t>, std::vector<int64_t>>()},
    {"min:1=[4]", get_func<min<float>, std::vector<float>>()},

    {"min_max:3=[0,0,0]",
     get_func<min_max<int64_t>, int64_t, int64_t, int64_t>()},
    {"min_max:3=[3,0,0]",
     get_func<
         repeat_apply<min_max<int64_t>, std::vector<int64_t>, int64_t, int64_t>,
         std::vector<int64_t>, int64_t, int64_t>()},
    {"min_max:3=[1,1,1]", get_func<min_max<float>, float, float, float>()},
    {"min_max:3=[3,0,0]",
     get_func<repeat_apply<min_max<float>, std::vector<float>, float, float>,
              std::vector<float>, float, float>()},

    {"binary:2=[0,0]", get_func<binarize<int64_t>, int64_t, int64_t>()},
    {"binary:2=[3,0]",
     get_func<repeat_apply<binarize<int64_t>, std::vector<int64_t>, int64_t>,
              std::vector<int64_t>, int64_t>()},

    {"binary:2=[1,1]", get_func<binarize<float>, float, float>()},
    {"binary:2=[4,1]",
     get_func<repeat_apply<binarize<float>, std::vector<float>, float>,
              std::vector<float>, float>()},

    {"bucket:2=[0,3]",
     get_func<bucketize<int64_t>, int64_t, std::vector<int64_t>>()},
    {"bucket:2=[1,4]", get_func<bucketize<float>, float, std::vector<float>>()},
    {"bucket:2=[3,3]", get_func<repeat_bucketize<int64_t>, std::vector<int64_t>,
                                std::vector<int64_t>>()},
    {"bucket:2=[4,4]", get_func<repeat_bucketize<float>, std::vector<float>,
                                std::vector<float>>()},

    {"box_cox:2=[1,1]", get_func<box_cox, float, float>()},
    {"box_cox:2=[4,1]",
     get_func<repeat_apply<box_cox, std::vector<float>, float>,
              std::vector<float>, float>()},

    {"norm:2=[3,1]", get_func<norm<int64_t>, std::vector<int64_t>, float>()},
    {"norm:2=[4,1]", get_func<norm<float>, std::vector<float>, float>()},

    {"normalize:2=[3,1]",
     get_func<normalize<int64_t>, std::vector<int64_t>, float>()},
    {"normalize:2=[4,1]",
     get_func<normalize<float>, std::vector<float>, float>()},

    {"var:1=[0]", get_func<variance<int64_t>, std::vector<int64_t>>()},
    {"var:1=[1]", get_func<variance<float>, std::vector<float>>()},

    {"z_score:3=[1,1,1]", get_func<z_score, float, float, float>()},
    {"z_score:3=[4,1,1]",
     get_func<repeat_apply<z_score, std::vector<float>, float, float>,
              std::vector<float>, float, float>()},

    {"std:1=[3]", get_func<stddev<int64_t>, std::vector<int64_t>>()},
    {"std:1=[4]", get_func<stddev<float>, std::vector<float>>()},

    {"year:0=[]", get_func<year>()},
    {"year:1=[1]", get_func<year_, int64_t>()},

    {"month:0=[]", get_func<month>()},
    {"month:1=[1]", get_func<month_, int64_t>()},

    {"day:0=[]", get_func<day>()},
    {"day:1=[1]", get_func<day_, int64_t>()},

    {"curdate:0=[]", get_func<curdate>()},
    {"curdate:1=[1]", get_func<curdate_, int64_t>()},

    {"unix_timestamp:0=[]", get_func<unix_timestamp>()},
    {"unix_timestamp:1=[1]", get_func<unix_timestamp_, int64_t>()},

    {"from_unixtime:2=[0,2]", get_func<from_unixtime, int64_t, std::string>()},
    {"from_unixtime:2=[3,2]",
     get_func<repeat_apply<from_unixtime, std::vector<int64_t>, std::string>,
              std::vector<int64_t>, std::string>()},

    {"date_add:2=[2,0,2]",
     get_func<date_add, std::string, int64_t, std::string>()},
    {"date_add:2=[5,0,2]",
     get_func<
         repeat_apply<date_add, std::vector<std::string>, int64_t, std::string>,
         std::vector<std::string>, int64_t, std::string>()},
    {"date_sub:2=[2,0,2]",
     get_func<date_sub, std::string, int64_t, std::string>()},
    {"date_sub:2=[5,0,2]",
     get_func<
         repeat_apply<date_sub, std::vector<std::string>, int64_t, std::string>,
         std::vector<std::string>, int64_t, std::string>()},
    {"date_diff:2=[2,2]", get_func<datediff, std::string, std::string>()},
    {"datediff:2=[2,5]",
     get_func<repeat_apply<datediff, std::string, std::vector<std::string>>,
              std::string, std::vector<std::string>>()},
    {"datediff:2=[5,2]",
     get_func<repeat_apply<datediff, std::vector<std::string>, std::string>,
              std::vector<std::string>, std::string>()},

    {"concat:2=[2,2]", get_func<concat, std::string, std::string>()},
    {"concat_ws:2=[2,5]",
     get_func<repeat_apply<concat, std::string, std::vector<std::string>>,
              std::string, std::vector<std::string>>()},
    {"cross:2=[5,5]",
     get_func<cross_apply<concat, std::string, std::string>,
              std::vector<std::string>, std::vector<std::string>>()},
    {"reverse:1=[2]", get_func<reverse, std::string>()},
    {"reverse:1=[5]", get_func<repeat_apply<reverse, std::vector<std::string>>,
                               std::vector<std::string>>()},
    {"substr:3=[2,0,0]", get_func<substr, std::string, int64_t, int64_t>()},
    {"substr:3=[2,0,0]",
     get_func<repeat_apply<substr, std::vector<std::string>, int64_t, int64_t>,
              std::vector<std::string>, int64_t, int64_t>()},

    {"upper:1=[2]", get_func<upper, std::string>()},
    {"upper:1=[5]", get_func<repeat_apply<upper, std::vector<std::string>>,
                             std::vector<std::string>>()},

    {"lower:1=[2]", get_func<lower, std::string>()},
    {"lower:1=[5]", get_func<repeat_apply<lower, std::vector<std::string>>,
                             std::vector<std::string>>()},

    {"cast:1=[0]", get_func<cast, int64_t>()},
    {"cast:1=[3]", get_func<repeat_apply<cast, std::vector<int64_t>>,
                            std::vector<int64_t>>()},
    {"to_string:1=[0]", get_func<to_string<int64_t>, int64_t>()},
    {"to_string:1=[3]",
     get_func<repeat_apply<to_string<int64_t>, std::vector<int64_t>>,
              std::vector<int64_t>>()},
    {"to_string:1=[1]", get_func<to_string<float>, float>()},
    {"to_string:1=[4]",
     get_func<repeat_apply<to_string<float>, std::vector<float>>,
              std::vector<float>>()},

    {"topk:2=[3,0]", get_func<topk<int64_t>, std::vector<int64_t>, int64_t>()},
    {"topk:2=[4,0]", get_func<topk<float>, std::vector<float>, int64_t>()},
    {"topk:2=[5,0]",
     get_func<topk<std::string>, std::vector<std::string>, int64_t>()},

};

} // namespace minia

#endif // MINIA_BUILTIN_H_