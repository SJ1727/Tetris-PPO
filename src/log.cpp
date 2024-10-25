#include "log.hpp"

#include "spdlog/sinks/rotating_file_sink.h"

std::shared_ptr<spdlog::logger> Log::s_application_logger;

void Log::init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  

  s_application_logger = spdlog::rotating_logger_mt("APPLICATION", "application.log", 1024 * 1024 * 5, 3); 
  s_application_logger->set_level(spdlog::level::trace);
}

