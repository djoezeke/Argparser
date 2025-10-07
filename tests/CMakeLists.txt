cmake_minimum_required(VERSION 3.16...4.1.1 FATAL_ERROR)
project(Argparser-Tests)

#--------------------------------------------------------------------
# Basic Test Configures   
#--------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(WIN32)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

include_directories("." "../")
