#ifdef LOG_LIBRARY_EXPORTS
#define LOG_LIBRARY_API __attribute__((visibility("default")))
#else
#define LOG_LIBRARY_API
#endif

#include <string>
#include <fstream>
#include <ctime>
#include <iostream>

using namespace std;

enum class LogLevel {
    INFO,
    WARNING,
    ERR
};

class LOG_LIBRARY_API Logger {
public:
    Logger(const string& filename, LogLevel defaultLevel);
    ~Logger();

    void log(const string& message, LogLevel level);
    void setDefaultLevel(LogLevel level);

private:
    ofstream logFile;
    LogLevel defaultLevel;

    string getCurrentTime();
    string logLevelToString(LogLevel level);
};