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

#include "minia.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace minia {

/**
 * @class PyMinia
 * @brief A wrapper class for the Minia library to be used in Python via
 * pybind11.
 *
 * The PyMinia class allows Python users to process features using
 * configuration-based expressions defined in a TOML file. This class manages
 * the conversion between C++ and Python data types.
 */
class PyMinia {
  public:
    /**
     * @brief Deleted default constructor.
     *
     * The default constructor is deleted to enforce the use of a configuration
     * file for initialization.
     */
    PyMinia() = delete;

    /**
     * @brief Constructs a PyMinia object using a configuration file.
     *
     * This constructor initializes the underlying Minia object with the
     * specified configuration file, setting up the necessary expressions and
     * features.
     *
     * @param config_file The path to the TOML configuration file.
     */
    explicit PyMinia(const std::string &config_file) : minia_(config_file) {}

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
     * @param features A string representing the features to process.
     * @return A pybind11 dictionary containing the processed feature values.
     */
    py::dict call(const std::string &features) {
        py::dict ret;
        Features fea(features);
        minia_.call(fea);
        const auto &keys = minia_.features();

        for (const auto &k : keys) {
            FeaturePtr f = fea.get(k);
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
