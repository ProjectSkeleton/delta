#pragma once

#include <functional>

namespace Delta {

enum class LogSeverity {
  kTrace,
  kInfo,
  kWarning,
  kError,
  kFatal,
};

class Logger {
public:
  Logger();

  void Log(LogSeverity severity, const char* msg);

  void SetCallback(std::function<void(const char*)> on_log);
  void SetMinSeverity(LogSeverity min_severity);

private:
  LogSeverity min_severity_;
  std::function<void(const char*)> on_log_;
};

}
