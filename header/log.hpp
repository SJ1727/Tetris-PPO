#ifndef LOG_H 
#define LOG_H

#include <memory>

#include <spdlog/spdlog.h> 

class Log {
public:
  static void init();

  inline static std::shared_ptr<spdlog::logger>& getApplicationLogger() { return s_application_logger; }

private:
  static std::shared_ptr<spdlog::logger> s_application_logger;
};

#define APP_TRACE(...)  ::Log::getApplicationLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)  ::Log::getApplicationLogger()->info(__VA_ARGS__)
#define APP_WARN(...)  ::Log::getApplicationLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)  ::Log::getApplicationLogger()->error(__VA_ARGS__)
#define APP_FATAL(...)  ::Log::getApplicationLogger()->fatal(__VA_ARGS__)

#endif // !LOG_H
