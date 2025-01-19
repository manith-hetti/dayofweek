cmake_minimum_required(VERSION 3.27)

project(DayOfWeek VERSION 0.5 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Boost REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(LIB_SOURCES
    src/date.cpp
    src/dategenerator.cpp
    src/game.cpp
    src/challenge_mode.cpp
    src/dow.cpp
)

set(LIB_HEADERS
    include/Date.hpp
    include/dategenerator.h
    include/game.hpp
    include/challenge_mode.hpp
    include/dow.h
)

add_library(DayOfWeekLib STATIC
    ${LIB_SOURCES}
    ${LIB_HEADERS}
    src/dow.ui
)

target_include_directories(DayOfWeekLib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(DayOfWeekLib PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    boost::boost
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(dayofweek
        MANUAL_FINALIZATION
        src/main.cpp
    )
else()
    if(ANDROID)
        add_library(dayofweek SHARED
            src/main.cpp
        )
    else()
        add_executable(dayofweek
            src/main.cpp
        )
    endif()
endif()

target_link_libraries(dayofweek PRIVATE DayOfWeekLib)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.dayofweek)
endif()

set_target_properties(dayofweek PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS dayofweek
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(dayofweek)
endif()

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
    COMMENT "Cleaning all build files..."
)

add_subdirectory(tests)
