#include "log.hpp"

std::ofstream Logger::s_LogFile;
std::string Logger::s_LogFileName;
std::mutex Logger::s_LogMutex;



void Logger::Init(std::string fileName) {
  if (!s_LogFile.is_open()) {
    s_LogFileName = fileName;
    s_LogFile.open(fileName, std::ios::out | std::ios::app);
  
    if (!s_LogFile.is_open()) {
      std::cerr << "Failed to open log file during init" << std::endl;
    }
  }
}



void Logger::ClearLog() {
  if (s_LogFile.is_open()) {
    s_LogFile.close();
  }

  s_LogFile.open(s_LogFileName, std::ios::out | std::ios::trunc);
  
  if (!s_LogFile.is_open()) {
    std::cerr << "Failed to open log file during clearing" << std::endl;
  }
}



void Logger::Log (LogLevel level, std::string message) {
  if (s_LogFile.is_open()) {
    std::lock_guard<std::mutex> lock(s_LogMutex);

    s_LogFile << GetCurrentTime() << " [" << LogLevelToString(level) << "] " << message << std::endl; 
  } else {
    std::cerr << "Log file is not open" << std::endl;
  }
}



std::string Logger::GetCurrentTime() {
  std::stringstream timeStringStream; 
  std::time_t now = std::time(nullptr);
  std::tm* timeInfo = std::localtime(&now);

  timeStringStream << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
  return timeStringStream.str();
}



std::string Logger::LogLevelToString(LogLevel level) {
  switch (level) {
    case LogLevel::TRACE: return "TRACE";
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARN: return "WARNING";
    case LogLevel::ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}
