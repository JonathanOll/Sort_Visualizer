cmake_minimum_required( VERSION 3.23 )
set(CMAKE_BUILD_TYPE Release)
project(Moteur_3d)


file(GLOB SRCS
    ".././source/*.cpp"
    ".././include/*.hpp"
    )

find_package(SFML COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(main ${SRCS})

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/../include)

target_link_libraries(main PRIVATE 
                      sfml-system
                      sfml-main
                      sfml-window
                      sfml-graphics
                      )
