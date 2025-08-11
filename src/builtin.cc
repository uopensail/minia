#include "builtin.h"

#include <time.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <vector>

namespace minia {

int64_t mod(const int64_t dividend, const int64_t divisor) {
  if (divisor == 0) {
    LOG(ERROR) << "Division by zero in modulus operation\n";
    throw std::invalid_argument("Division by zero in modulus operation");
  }

  // Handle negative divisors
  if (divisor < 0) {
    LOG(ERROR) << "Divisor must be positive for defined behavior\n";
    throw std::invalid_argument(
        "Divisor must be positive for defined behavior");
  }

  int64_t result = dividend % divisor;
  return result >= 0 ? result : result + divisor;
}

int64_t ceil(float v) { return ceilf(v); }

int64_t round(float v) { return roundf(v); }

int64_t floor(float v) { return floorf(v); }

float sigmoid(const float x) { return 1.0 / (1.0 + expf(-x)); }

int64_t _and(const int64_t a, const int64_t b) { return a && b; }

int64_t _or(const int64_t a, const int64_t b) { return a || b; }

int64_t _not(const int64_t v) { return !v; }

std::string format_date(time_t t, const std::string &fmt) {
  std::tm *tm = std::localtime(&t);
  if (!tm) {
    LOG(ERROR) << "Failed to format time\n";
    throw std::runtime_error("Failed to format time");
  }

  char buffer[128];
  if (std::strftime(buffer, sizeof(buffer), fmt.c_str(), tm) == 0) {
    LOG(ERROR) << "Invalid format string:" << fmt << "\n";
    throw std::invalid_argument("Invalid format string: " + fmt);
  }
  return buffer;
}

std::string year() {
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return format_date(now, "%Y");
}

std::string year_(const int64_t timestamp) {
  time_t t = static_cast<time_t>(timestamp);
  return format_date(t, "%Y");
}

std::string month() {
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return format_date(now, "%m");
}

std::string month_(const int64_t timestamp) {
  time_t t = static_cast<time_t>(timestamp);
  return format_date(t, "%m");
}

std::string day() {
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return format_date(now, "%d");
}

std::string day_(const int64_t timestamp) {
  time_t t = static_cast<time_t>(timestamp);
  return format_date(t, "%d");
}

std::string curdate() {
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return format_date(now);
}

std::string curdate_(const int64_t timestamp) {
  time_t t = static_cast<time_t>(timestamp);
  return format_date(t);
}

int64_t unix_timestamp() {
  return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

int64_t unix_timestamp_(const int64_t timestamp) { return timestamp; }

std::string from_unixtime(const int64_t timestamp, const std::string &format) {
  time_t t = static_cast<time_t>(timestamp);
  return format_date(t, format);
}

std::string date_add(const std::string &date_str, const int64_t interval,
                     const std::string &unit) {
  const std::string format = "%Y-%m-%d";
  std::tm timeinfo = {};
  strptime(date_str.c_str(), format.c_str(), &timeinfo);

  time_t new_time = mktime(&timeinfo);
  if (unit == "SECOND") {
    new_time += interval;
  } else if (unit == "MINUTE") {
    new_time += interval * 60;
  } else if (unit == "HOUR") {
    new_time += interval * 3600;
  } else if (unit == "DAY") {
    new_time += 86400 * interval;
  } else if (unit == "MONTH") {
    timeinfo.tm_mon += interval;
    while (timeinfo.tm_mon > 11) {
      timeinfo.tm_mon -= 12;
      timeinfo.tm_year++;
    }
    new_time = std::mktime(&timeinfo);
  } else if (unit == "YEAR") {
    timeinfo.tm_year += interval;
    new_time = std::mktime(&timeinfo);
  } else {
    LOG(ERROR) << "Unsupported unit: " << unit << "\n";
    throw std::invalid_argument("Unsupported unit: " + unit);
  }

  return format_date(new_time);
}

std::string date_sub(const std::string &date_str, const int64_t interval,
                     const std::string &unit) {
  return date_add(date_str, -interval, unit);
}

int64_t datediff(const std::string &date1, const std::string &date2) {
  const std::string format = "%Y-%m-%d";
  std::tm d1 = {};
  std::tm d2 = {};
  strptime(date1.c_str(), format.c_str(), &d1);
  strptime(date2.c_str(), format.c_str(), &d2);
  return int64_t((mktime(&d1) - mktime(&d2)) / 86400);
}

std::string reverse(const std::string &str) {
  std::string reversed(str.rbegin(), str.rend());
  return reversed;
}

std::string upper(const std::string &str) {
  std::string result(str);
  std::transform(str.begin(), str.end(), result.begin(), ::toupper);
  return result;
}

std::string lower(const std::string &str) {
  std::string result(str);
  std::transform(str.begin(), str.end(), result.begin(), ::tolower);
  return result;
}

std::string substr(const std::string &str, const int64_t pos,
                   const int64_t len) {
  int64_t p = pos;
  if (pos < 0) {
    p = str.length() + pos + 1;
  }

  if (p < 1 || p > str.length()) {
    return "";
  }

  int64_t n = len;
  size_t start = p - 1;
  if (n < 0) {
    n = str.length();
  }
  return str.substr(start, len);
}

float z_score(const float value, const float mean, const float std_dev) {
  if (std_dev <= 0.0f) {
    LOG(ERROR) << "Standard deviation must be positive\n";
    throw std::invalid_argument("Standard deviation must be positive");
  }
  return (value - mean) / std_dev;
}

float box_cox(const float value, const float lambda) {
  // Validate input constraints
  if (value <= 0.0f) {
    LOG(ERROR) << "Input value must be positive for Box-Cox transform\n";
    throw std::invalid_argument(
        "Input value must be positive for Box-Cox transform");
  }

  // Handle near-zero lambda using Taylor series approximation
  constexpr float epsilon = 1e-7f;
  if (std::abs(lambda) < epsilon) {
    return std::log(value);
  }

  // Prevent numerical instability for negative lambda
  if (lambda < 0.0f && value < 1.0f) {
    LOG(ERROR)
        << "Combination of lambda < 0 and value < 1 causes instability\n";
    throw std::domain_error(
        "Combination of lambda < 0 and value < 1 causes instability");
  }

  // Compute standard Box-Cox transform
  return (std::pow(value, lambda) - 1.0f) / lambda;
}

std::string concat(const std::string &a, const std::string &b) {
  std::string ret;
  ret.reserve(a.size() + b.size());
  ret.append(a);
  ret.append(b);
  return ret;
}

std::vector<std::string> concat_ws(const std::string &a,
                                   const std::vector<std::string> &b) {
  std::vector<std::string> ret;
  for (auto &vb : b) {
    ret.push_back(concat(a, vb));
  }
  return ret;
}

float cast(int64_t v) noexcept { return static_cast<float>(v); }

int64_t mmh3(const std::string &key) {
  char ret[16]; // Buffer to store the 128-bit hash result
  MurmurHash3_x64_128(key.c_str(), key.size(), 0, ret);
  return ((int64_t *)ret)[0] & mask;
}

} // namespace minia
