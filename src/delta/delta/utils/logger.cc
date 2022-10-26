#include "logger.hh"

#include <cstdio>

namespace Delta {

Logger::Logger() : min_severity_(LogSeverity::kTrace) {
  on_log_ = [](const char* msg) {
    printf("%s\n", msg);
  };
}

void Logger::Log(LogSeverity severity, const char* msg) {
  on_log_(msg);
}

void Logger::SetCallback(std::function<void(const char*)> on_log) {
  on_log_ = on_log;
}

void Logger::SetMinSeverity(LogSeverity min_severity) {
  min_severity_ = min_severity;
}

}
