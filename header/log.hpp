#ifndef LOG_H 
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>
#include <sstream>
#include <iomanip>


class Logger {
public:
  enum LogLevel { TRACE, INFO, WARN, ERROR };
  
  static void Init(std::string fileName);
  static void ClearLog();
  static void Log(LogLevel level, std::string message);

private:
  static std::string GetCurrentTime();
  static std::string LogLevelToString(LogLevel level);

private:
  static std::ofstream s_LogFile;
  static std::string s_LogFileName;
  static std::mutex s_LogMutex;
};

#define LOG_TRACE(message)  ::Logger::Log(Logger::LogLevel::TRACE, message)
#define LOG_INFO(message)   ::Logger::Log(Logger::LogLevel::INFO, message)
#define LOG_WARN(message)   ::Logger::Log(Logger::LogLevel::WARN, message)
#define LOG_ERROR(message)  ::Logger::Log(Logger::LogLevel::ERROR, message)

#endif // !LOG_H
