cmake_minimum_required(VERSION 3.22)
project(GameEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.h")
file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC src)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

message("${PROJECT_SOURCE_DIR}")
message("${SDL2_TTF_INCLUDE_DIRS}")

target_include_directories(${PROJECT_NAME} PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        nlohmann_json::nlohmann_json)