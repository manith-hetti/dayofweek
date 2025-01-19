add_library(Date date.cpp)

target_include_directories(Date
                            PRIVATE ${CMAKE_SOURCE_DIR}/include)
