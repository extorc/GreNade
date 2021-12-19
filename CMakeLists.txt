cmake_minimum_required(VERSION 3.14)

project(GreNade)

include_directories(GreNade)

set(INC 
  src/
  src/Utility/
  src/Hittable/
  src/Materials
  src/Objects
)

file(GLOB_RECURSE GreNade_SRC
  src/*.cpp
  src/*.h
  src/*/*.cpp
  src/*/*.h
)

add_executable(GreNade ${GreNade_SRC})

target_include_directories(GreNade PUBLIC ${INC})