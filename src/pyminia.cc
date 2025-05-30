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
   * @class Minia
   * @brief A class for processing features using configured expressions.
   *
   * The Minia class reads and processes expressions and features from
   * a TOML configuration file, facilitating operations on features.
   */
  py::class_<minia::PyMinia>(m, "Minia")
      .def(py::init<const std::string &, const std::string &>(),
           py::arg("config_file"), py::arg("log_dir") = std::string("./logs"),
           R"pbdoc(
             Initialize Minia with a configuration file and log dir.
             
             Parses expressions and features from a TOML configuration
             file, extracting necessary data and managing parsing errors.
             
             Parameters
             ----------
             config_file : str
                 Path to the configuration file.
             log_dir : str
                 Dir for the log files.
             
             Example config
             --------------
             [transform]
             expressions = ['x = 5 + 5 + h', 'y = sqrt(x)', 'z = y * y']
             )pbdoc")
      .def("__call__", &minia::PyMinia::call, py::arg("features").noconvert(),
           R"pbdoc(
            Apply operations to the provided features.
            
            Parameters
            ----------
            features : byte array
                The features object to be processed.
            )pbdoc");
}
