#include "pyminia.h"

/**
 * @brief Python module definition for Minia.
 *
 * Provides the Minia class for feature processing and hashing through
 * configuration-based expression computation.
 */
PYBIND11_MODULE(pyminia, m) {
  m.doc() = R"pbdoc(
        Minia: Feature Processing and Hashing
        =====================================
        A module for processing features using configured expressions.
    )pbdoc";

  /**
   * @brief Data type enumeration for the minia framework
   * @details Defines scalar and array types for integers, floats, strings, and
   * error handling
   */
  py::enum_<minia::DataType>(m, "DataType")
      .value("kInt64", minia::DataType::kInt64)     ///< 64-bit signed integer
      .value("kFloat32", minia::DataType::kFloat32) ///< 32-bit floating point
      .value("kString", minia::DataType::kString)   ///< String type
      .value("kInt64s", minia::DataType::kInt64s) ///< Array of 64-bit integers
      .value("kFloat32s",
             minia::DataType::kFloat32s)            ///< Array of 32-bit floats
      .value("kStrings", minia::DataType::kStrings) ///< Array of strings
      .value("kError", minia::DataType::kError);    ///< Error type indicator

  /**
   * @class Minia
   * @brief A class for processing features using configured expressions.
   *
   * The Minia class reads and processes expressions
   */
  py::class_<minia::PyMinia>(m, "Minia")
      .def(py::init<const std::vector<std::string> &>(), py::arg("exprs"),
           R"pbdoc(
             Initialize Minia with a configuration file and log dir.
             
             Parses expressions and features from a TOML configuration
             file, extracting necessary data and managing parsing errors.
             
             Parameters
             ----------
             exprs : str
                 Expression to be processed
            )pbdoc")
      .def("__call__", &minia::PyMinia::call, py::arg("features").noconvert(),
           R"pbdoc(
            Apply operations to the provided features.
            
            Parameters
            ----------
            features : dict
                The features dict to be processed.
            )pbdoc");
}
