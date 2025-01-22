# LogLibrary
Проект состоит из двух частей: динамическая библиотека и консольное приложение.

## LogLibrary
Библиотека для записи текстовых сообщений в журнал.
В журнале сохраняется: время сообщения, уровень важности, текст сообщения

## LogApp
Консольное многопоточное приложение для проверки библиотеки записи сообщений в журнал.

## Установка
- > ```git clone ```
+ > ```cd LogLibrary```
* Для сборки всего проекта сразу:
> ```make```
- Для сборки библиотеки отдельно:
> ```make libLogLibrary.so```
+ Для сборки приложения отдельно:
> ```make LogApp```
> ```./LogApp [имя журнала] [уровень важности]```
