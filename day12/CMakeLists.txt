add_executable(day12 src/main.cpp)
target_link_libraries(day12 PRIVATE range-v3::range-v3 fmt::fmt util)

add_executable(day12_2 src/main2.cpp)
target_link_libraries(day12_2 PRIVATE range-v3::range-v3 fmt::fmt util)
