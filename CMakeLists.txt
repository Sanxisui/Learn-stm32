if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-fwrapv)
endif()
cmake_minimum_required(VERSION 3.0.0)

project(my_project)

add_subdirectory(driver/test_one)

# add_executable(my_project )