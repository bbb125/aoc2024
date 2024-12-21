add_executable(day25 src/main.cpp)
target_link_libraries(day25 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt)
