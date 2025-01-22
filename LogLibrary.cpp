#include "LogLibrary.h"

using namespace std;

// Конструктор класса Logger
Logger::Logger(const string& filename, LogLevel defaultLevel) {
    this->defaultLevel = defaultLevel;
    logFile.open(filename, ios::app);

    if (!logFile.is_open()) {
        cerr << "Ошибка открытия файла журнала" << endl;
    }
}

// Деструктор класса Logger
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Метод для записи сообщения в журнал
void Logger::log(const string& message, LogLevel level) {
    if (level >= defaultLevel) {
        logFile << getCurrentTime() << " [" << logLevelToString(level) << "] " << message << std::endl;
    }
}

// Метод для изменения уровня важности по умолчанию
void Logger::setDefaultLevel(LogLevel level) {
    defaultLevel = level;
}

// Метод для получения текущего времени
std::string Logger::getCurrentTime() {
    time_t now = time(nullptr);
    tm *timeinfo = localtime(&now);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buf;
}

//метод для записи уровня сообщения
std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERR: return "ERR";
    default: return "UNKNOWN";
    }
}