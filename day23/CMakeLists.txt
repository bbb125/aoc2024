add_executable(day23 src/main.cpp)
target_link_libraries(day23 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt ctre::ctre)
