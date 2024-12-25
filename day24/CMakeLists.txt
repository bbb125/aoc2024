add_executable(day24 src/main.cpp)
target_link_libraries(day24 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt ctre::ctre)
