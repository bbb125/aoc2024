add_executable(day21 src/main.cpp)
target_link_libraries(day21 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt)
