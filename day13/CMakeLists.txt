add_executable(day13 src/main.cpp)
target_link_libraries(day13
        PRIVATE
        range-v3::range-v3 fmt::fmt util
)