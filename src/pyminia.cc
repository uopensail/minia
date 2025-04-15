#include "pyminia.h"

/**
 * @brief Python module definition for Minia.
 *
 * Provides the Minia class for feature processing and hashing through
 * configuration-based expression computation.
 */
PYBIND11_MODULE(minia, m) {
  m.doc() = R"pbdoc(
        Minia: Feature Processing and Hashing
        =====================================
        A module for processing features using configured expressions.
    )pbdoc";

  /**
   * @class Minia
   * @brief A class for processing features using configured expressions.
   *
   * The Minia class reads and processes expressions and features from
   * a TOML configuration file, facilitating operations on features.
   */
  py::class_<minia::PyMinia>(m, "Minia")
      .def(py::init<const std::string &>(), py::arg("config_file"),
           R"pbdoc(
             Initialize Minia with a configuration file.
             
             Parses expressions and features from a TOML configuration
             file, extracting necessary data and managing parsing errors.
             
             Parameters
             ----------
             config_file : str
                 Path to the configuration file.
             
             Example config
             --------------
             [transform]
             expressions = ['x = 5 + 5 + h', 'y = sqrt(x)', 'z = y * y']
             )pbdoc")
      .def("__call__", &minia::PyMinia::call, py::arg("features"), R"pbdoc(
            Apply operations to the provided features.
            
            Updates the `features` object by iterating over and applying
            operations stored in the `ops_` vector.
            
            Parameters
            ----------
            features : string
                The features object to be updated.
            )pbdoc");
}
