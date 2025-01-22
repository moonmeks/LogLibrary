#include <thread>
#include <mutex>
#include <atomic>
#include "LogLibrary.h"

using namespace std;

mutex logMutex; // Мьютекс для обеспечения потокобезопасности
atomic<bool> running(true); // Флаг для управления работой приложения

void logMessage(Logger& logger, const string& message, LogLevel level) {
    lock_guard<mutex> guard(logMutex); // Блокируем мьютекс для потокобезопасной записи
    logger.log(message, level);
}

void inputThread(Logger& logger) {
    string choice;
    string levelInput;

    while (running) {
        cout << "\nМеню:\n";
        cout << "1. Написать сообщение\n";
        cout << "2. Изменить уровень важности по умолчанию\n";
        cout << "3. Выход\n";
        cout << "Выберите опцию: ";
        getline(cin, choice);

        if (choice == "1") {
            string message;
            cout << "Введите сообщение: ";
            getline(cin, message);
            cout << "Введите уровень важности (INFO, WARNING, ERR) или оставьте пустым: ";
            getline(cin, levelInput);

            LogLevel level = LogLevel::INFO;
            if (levelInput == "WARNING") {
                level = LogLevel::WARNING;
            }
            else if (levelInput == "ERR") {
                level = LogLevel::ERR;
            }

            // Запускаем поток для записи сообщения
            thread logThread(logMessage, ref(logger), message, level);
            logThread.detach(); // Отсоединяем поток
        }
        else if (choice == "2") {
            cout << "Введите новый уровень важности по умолчанию (INFO, WARNING, ERR): ";
            getline(cin, levelInput);
            if (levelInput == "WARNING") {
                logger.setDefaultLevel(LogLevel::WARNING);
            }
            else if (levelInput == "ERR") {
                logger.setDefaultLevel(LogLevel::ERR);
            }
            else {
                logger.setDefaultLevel(LogLevel::INFO);
            }
            cout << "Уровень важности по умолчанию изменен." << endl;
        }
        else if (choice == "3") {
            running = false; // Завершаем программу
        }
        else {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 3) {
        cerr << "Использование: " << argv[0] << " <имя файла журнала> <уровень важности по умолчанию>" << endl;
        return 1;
    }

    string logFileName = argv[1];
    string defaultLevelInput = argv[2];
    LogLevel defaultLevel = LogLevel::INFO;

    // Устанавливаем уровень по умолчанию на основе аргумента
    if (defaultLevelInput == "WARNING") {
        defaultLevel = LogLevel::WARNING;
    }
    else if (defaultLevelInput == "ERR") {
        defaultLevel = LogLevel::ERR;
    }

    Logger logger(logFileName, defaultLevel);

    // Запускаем поток для ввода
    thread inputThreadObj(inputThread, ref(logger));

    inputThreadObj.join(); // Ждем завершения потока ввода

    return 0;
}