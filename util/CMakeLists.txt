add_library(util src/util.cpp)
target_include_directories(util
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(util
    PUBLIC
        range-v3::range-v3
)
