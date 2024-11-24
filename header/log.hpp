#ifndef LOG_H 
#define LOG_H

#include <memory>

#include <spdlog/spdlog.h> 

class Log {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return s_ApplicationLogger; }
  inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }

private:
  static std::shared_ptr<spdlog::logger> s_ApplicationLogger;
  static std::shared_ptr<spdlog::logger> s_EngineLogger;
};

#define APP_TRACE(...)  ::Log::GetApplicationLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)  ::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_WARN(...)  ::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)  ::Log::GetApplicationLogger()->error(__VA_ARGS__)

#define ENGINE_TRACE(...)  ::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...)  ::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...)  ::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)  ::Log::GetEngineLogger()->error(__VA_ARGS__)

#endif // !LOG_H
