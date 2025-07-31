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

#ifndef PY_MINIA_H_
#define PY_MINIA_H_

#include <pybind11/buffer_info.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "minia.h"

namespace py = pybind11;

namespace minia {

/**
 * @class PyMinia
 * @brief A wrapper class for the Minia library to be used in Python via
 * pybind11.
 *
 * The PyMinia class allows Python users to process features using
 * expressions. This class manages the conversion between C++ and
 * Python data types.
 */
class PyMinia {
public:
  /**
   * @brief Deleted default constructor.
   *
   * The default constructor is deleted to enforce the use of `expressions`
   * for initialization.
   */
  PyMinia() = delete;

  /**
   * @brief Constructs a PyMinia object using `expressions`.
   *
   * This constructor initializes the underlying Minia object with the
   * specified `expressions`.
   *
   * @param expressions The expressions to be processed.
   */
  explicit PyMinia(const std::vector<std::string> &expressions)
      : minia_(expressions) {
    enable_glog("./logs", ERROR);
  }

  /**
   * @brief Default destructor.
   */
  ~PyMinia() = default;

  /**
   * @brief Processes features and returns the results as a Python dictionary.
   *
   * This function applies the configured operations to the input features and
   * returns a dictionary of results, with type conversions handled for Python
   * compatibility.
   *
   * @param features A dict representing the features to process.
   * @return A pybind11 dictionary containing the processed feature values.
   */
  py::dict call(py::dict features) {
    Features feas;
    for (auto kv : features) {
      std::string key = py::str(kv.first);
      py::dict data = kv.second.cast<py::dict>();
      DataType type = DataType(data["type"].cast<int>());
      py::object value = data["value"];
      FeaturePtr ptr = nullptr;
      switch (type) {
      case DataType::kInt64:
        ptr = std::make_shared<Feature>(value.cast<int64_t>());
        break;
      case DataType::kFloat32:
        ptr = std::make_shared<Feature>(value.cast<float>());
        break;
      case DataType::kString:
        ptr = std::make_shared<Feature>(std::string(py::str(value)));
        break;
      case DataType::kInt64s:
        ptr = std::make_shared<Feature>(value.cast<std::vector<int64_t>>());
        break;
      case DataType::kFloat32s:
        ptr = std::make_shared<Feature>(value.cast<std::vector<float>>());
        break;
      case DataType::kStrings:
        ptr = std::make_shared<Feature>(value.cast<std::vector<std::string>>());
        break;
      default:
        break;
      }

      if (ptr != nullptr) {
        feas.insert(key, ptr);
      }
    }

    minia_.call(feas);
    const auto &keys = minia_.features();
    py::dict ret;
    for (const auto &k : keys) {
      FeaturePtr f = feas.get(k);
      if (!f) {
        continue;
      }
      switch (f->type) {
      case minia::DataType::kFloat32:
        ret[k.c_str()] = f->get<float>();
        break;
      case minia::DataType::kFloat32s:
        ret[k.c_str()] = py::cast(f->get<std::vector<float>>());
        break;
      case minia::DataType::kInt64:
        ret[k.c_str()] = f->get<int64_t>();
        break;
      case minia::DataType::kInt64s:
        ret[k.c_str()] = py::cast(f->get<std::vector<int64_t>>());
        break;
      case minia::DataType::kString:
        ret[k.c_str()] = f->get<std::string>();
        break;
      case minia::DataType::kStrings:
        ret[k.c_str()] = py::cast(f->get<std::vector<std::string>>());
        break;
      default:
        break;
      }
    }
    return ret;
  }

private:
  Minia minia_; /**< An instance of the Minia class to perform feature
                   processing. */
};

} // namespace minia

#endif // PY_MINIA_H_
