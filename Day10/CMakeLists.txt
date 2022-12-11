add_executable(day10 day10.cpp)
target_include_directories(
  day10
  PRIVATE ../common
)
target_link_libraries(
  day10
  PUBLIC project_options project_warnings common
  )