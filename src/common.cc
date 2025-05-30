#include "common.h"

#include <filesystem>
#include <iostream>

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
void enable_glog(const char *log_dir, int32_t log_level) {
#ifdef ENABLE_GLOG
  // Initialize Google Logging with application name
  google::InitGoogleLogging("minia");

  // Configure log format and behavior
  FLAGS_log_prefix = true;  // Enable log prefixes (timestamp, severity, etc.)
  FLAGS_max_log_size = 100; // Maximum log file size in MB
  FLAGS_stop_logging_if_full_disk =
      true; // Stop logging when disk is full to prevent system issues
  FLAGS_logtostderr =
      false; // Disable automatic stderr output (manually controlled below)
  FLAGS_minloglevel = log_level; // Set minimum log level threshold
  FLAGS_timestamp_in_logfile_name =
      false; // Use static filename without timestamp

  // Determine log directory
  std::string actual_log_dir;
  if (log_dir != nullptr && strlen(log_dir) > 0) {
    actual_log_dir = std::string(log_dir);
  } else {
    // Use default log directory if none provided
    actual_log_dir = "./logs";
  }

  // Create log directory if it doesn't exist
  try {
    std::filesystem::create_directories(actual_log_dir);
  } catch (const std::exception &e) {
    // If directory creation fails, fall back to stderr logging
    std::cerr << "Warning: Failed to create log directory '" << actual_log_dir
              << "': " << e.what() << ". Falling back to stderr logging."
              << std::endl;
    google::SetStderrLogging(static_cast<google::LogSeverity>(log_level));
    return;
  }

  // Construct full log file path
  std::string log_path = actual_log_dir + "/minia.log";

  // Set all log levels to write to the same file
  google::SetLogDestination(google::INFO, log_path.c_str());
  google::SetLogDestination(google::WARNING, log_path.c_str());
  google::SetLogDestination(google::ERROR, log_path.c_str());

  // Enable console output for ERROR level and above
  google::SetStderrLogging(google::ERROR);

  // Log successful initialization
  LOG(INFO) << "Logging initialized. Log directory: " << actual_log_dir;

#endif // ENABLE_GLOG
}
