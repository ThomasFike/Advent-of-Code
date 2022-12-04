add_library(common STATIC common.cpp)
target_link_libraries(common
    PUBLIC fmt::fmt
)