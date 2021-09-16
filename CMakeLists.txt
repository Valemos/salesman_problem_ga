cmake_minimum_required(VERSION 3.5)

project(salesman_problem_gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(genetic_algorithm
        src/genetic_algorithm/Creature.cpp
        src/genetic_algorithm/Creature.h
        src/genetic_algorithm/EnumChromosome.cpp
        src/genetic_algorithm/EnumChromosome.h
        src/genetic_algorithm/Population.cpp
        src/genetic_algorithm/Population.h
        src/genetic_algorithm/ScoredCreature.h
        src/genetic_algorithm/OptimizationProblem.h)

add_library(salesman_problem src/SalesmanProblem.cpp src/SalesmanProblemSolutionProgress.cpp src/SalesmanProblemSolutionProgress.h)
target_link_libraries(salesman_problem genetic_algorithm)


# testing
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(tests tests/test_algorithm.cpp tests/test_calculation_functions.cpp tests/test_crossover.cpp tests/test_calculation_functions.cpp)
target_link_libraries(tests Threads::Threads gtest gtest_main genetic_algorithm salesman_problem)


# qt config
find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(salesman_problem_gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET salesman_problem_gui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(salesman_problem_gui SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(salesman_problem_gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(salesman_problem_gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(salesman_problem_gui PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(salesman_problem_gui PRIVATE salesman_problem)

set_target_properties(salesman_problem_gui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(salesman_problem_gui)
endif()
