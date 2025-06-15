cmake_minimum_required(VERSION 3.28)
project(sfSnake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/3rd/SFML-2.6.0/build")

find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.cc"
)

add_executable(sfSnake ${SOURCES})

target_compile_features(sfSnake PRIVATE cxx_std_17)

target_link_libraries(sfSnake PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio 
    sfml-network
)

file(COPY ${CMAKE_SOURCE_DIR}/Fonts DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)
file(COPY ${CMAKE_SOURCE_DIR}/Music DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)
file(COPY ${CMAKE_SOURCE_DIR}/Sounds DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)
file(COPY ${CMAKE_SOURCE_DIR}/Images DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)

if(WIN32)
    add_custom_command(TARGET sfSnake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE:sfml-network>
        "${CMAKE_SOURCE_DIR}/3rd/SFML-2.6.0/bin/openal32.dll"
        $<TARGET_FILE_DIR:sfSnake>
    )
endif()