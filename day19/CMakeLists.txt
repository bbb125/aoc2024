add_executable(day19 src/main.cpp)
target_link_libraries(day19 PRIVATE util Boost::boost range-v3::range-v3 fmt::fmt ctre::ctre)