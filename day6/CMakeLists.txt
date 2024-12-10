add_executable(day6 src/main.cpp)
add_executable(day6_2 src/main2.cpp)
target_link_libraries(day6_2 PRIVATE range-v3::range-v3 util)