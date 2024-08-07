# Local search engine

### Описание проекта:
Локальная поисковая система представляет собой консольное приложение, которое выполняет поиск и имеет возможность настройки с помощью файлов в формате JSON. Решения, применяемые в ней, впоследствии могут быть интегрированы в веб-поисковую систему.

### Используемый стек технологий:
C++, STL, Nlohmann_json, GoogleTest

### Инструкция:
Чтобы загрузить архив программы, нажмите на кнопку Code. Распакуйте данные архива в новую папку. Для компиляции можно использовать MinGW64. Чтобы скомпилировать программу, перейдите в папку project в командной строке, затем выберите папку src и запустите команду:

#### g++ main.cpp converterJSON.cpp invertedIndex.cpp searchServer.cpp -o search-engine .exe

Затем запустите программу командой:

#### search-engine.exe



### Принципы работы поисковой системы:

- В конфигурационном файле "config.json" перед запуском приложения задаются имена файлов в поле "files", которые движок будет искать.
- Поисковая система самостоятельно обрабатывает все файлы и индексирует их, чтобы затем найти наиболее релевантные документы по любому поисковому запросу.
- Пользователь делает запрос через JSON-файл "requests.json", затем запрос преобразуется в список слов.
- Индекс выполняет поиск тех документов, в которых встречаются все эти слова.
- Результаты поиска ранжируются, сортируются и выдаются пользователю, максимальное количество возможных документов в ответе задается в конфигурационном файле "config.json" в поле "max_responses".
- В конце концов, программа генерирует файл "answers.json", в который записываются результаты поиска.
