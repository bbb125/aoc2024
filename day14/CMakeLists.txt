add_executable(day14 src/main.cpp)
target_link_libraries(day14
        PRIVATE
        range-v3::range-v3 fmt::fmt util ctre::ctre
)