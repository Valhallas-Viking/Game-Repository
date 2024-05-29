cmake_minimum_required(VERSION 3.5)

project(Game_For_SoftwareExam LANGUAGES CXX)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Game_For_SoftwareExam
    main.cpp
    database.h
    hero.h
    Fight.h
    enemy.h)

target_link_libraries(Game_For_SoftwareExam
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Sql
)
