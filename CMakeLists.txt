cmake_minimum_required(VERSION 3.14)

project(GreNade)

include_directories(GreNade)

file(GLOB_RECURSE GreNade_SRC
  src/*.cpp
  src/*.h
  src/*/*.cpp
  src/*/*.h
)

add_executable(GreNade ${GreNade_SRC})