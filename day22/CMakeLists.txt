add_executable(day22 src/main.cpp)
target_link_libraries(day22 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt)
