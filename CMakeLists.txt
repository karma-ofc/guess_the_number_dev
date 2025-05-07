cmake_minimum_required(VERSION 3.16)

project(untitled3 VERSION 0.1 LANGUAGES CXX)

# Автоматическая обработка файлов .ui, .moc и .qrc
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем необходимую версию Qt, необходим для использования Qt Widgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Список исходных файлов проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Создание исполнимого файла
qt_add_executable(untitled3
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Подключение библиотеки Qt для работы с Widgets
target_link_libraries(untitled3 PRIVATE Qt6::Widgets)

# Финализация проекта для Qt 6
qt_finalize_executable(untitled3)
