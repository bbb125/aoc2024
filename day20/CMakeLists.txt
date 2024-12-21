add_executable(day20 src/main.cpp)
target_link_libraries(day20 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt)
