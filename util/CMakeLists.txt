add_library(util INTERFACE)
target_include_directories(util
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(util
    INTERFACE
        range-v3::range-v3 Boost::boost fmt::fmt
)
