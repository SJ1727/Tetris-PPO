#include "log.hpp"

#include "spdlog/sinks/rotating_file_sink.h"

std::shared_ptr<spdlog::logger> Log::s_ApplicationLogger;

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  

  s_ApplicationLogger = spdlog::rotating_logger_mt("APPLICATION", "application.log", 1024 * 1024 * 5, 3); 
  s_ApplicationLogger->set_level(spdlog::level::trace);
}

