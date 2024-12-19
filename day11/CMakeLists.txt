add_executable(day11 src/main.cpp)
target_link_libraries(day11 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt)