project(cpp-hse)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/BuildFlags.cmake)
include(cmake/TestSolution.cmake)

find_package(Catch REQUIRED)

include_directories(util)

# 1
add_subdirectory(tasks/multiplication)
add_subdirectory(tasks/hypotenuse)
add_subdirectory(tasks/next_even)
add_subdirectory(tasks/is_leap)
add_subdirectory(tasks/chocolate)
add_subdirectory(tasks/min_divisor)
add_subdirectory(tasks/sum_digits)
add_subdirectory(tasks/fibonacci)
add_subdirectory(tasks/reduce_fraction)


#2
add_subdirectory(tasks/const_diagonal)
add_subdirectory(tasks/variable_diagonal)
add_subdirectory(tasks/palindrome)
add_subdirectory(tasks/password)
add_subdirectory(tasks/range)
add_subdirectory(tasks/factorization)
add_subdirectory(tasks/sort_students)


#3
add_subdirectory(tasks/caesar_cipher)
add_subdirectory(tasks/sort)
add_subdirectory(tasks/stack)
add_subdirectory(tasks/find_last)


#4
add_subdirectory(tasks/is_sorted_until)
add_subdirectory(tasks/remove)
add_subdirectory(tasks/rational)
add_subdirectory(tasks/array)


#5
add_subdirectory(tasks/tests_checking)
add_subdirectory(tasks/word2vec)
add_subdirectory(tasks/admission)
add_subdirectory(tasks/scorer)
add_subdirectory(tasks/provinces)
add_subdirectory(tasks/unixpath)


# homework 1
add_subdirectory(tasks/copy)
add_subdirectory(tasks/rotate)
add_subdirectory(tasks/unique)
add_subdirectory(tasks/queue)
add_subdirectory(tasks/string_view)
add_subdirectory(tasks/string)
add_subdirectory(tasks/cstring)


#6
add_subdirectory(tasks/geometry_vector)
add_subdirectory(tasks/geometry_point)
add_subdirectory(tasks/geometry_line)
add_subdirectory(tasks/geometry_segment)
add_subdirectory(tasks/geometry_ray)
add_subdirectory(tasks/geometry_polygon)
add_subdirectory(tasks/geometry_circle)


#7
add_subdirectory(tasks/dedup)
add_subdirectory(tasks/unique-ptr)
add_subdirectory(tasks/vector)
add_subdirectory(tasks/reader)


#8
add_subdirectory(tasks/itertools)
add_subdirectory(tasks/any)


# homework 2
add_subdirectory(tasks/enumerate)
add_subdirectory(tasks/reversed)
add_subdirectory(tasks/list)
add_subdirectory(tasks/smart-ptr)
add_subdirectory(tasks/unordered_set)