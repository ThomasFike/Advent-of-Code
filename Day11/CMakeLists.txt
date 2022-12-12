add_executable(day11 day11.cpp)
target_include_directories(
  day11
  PRIVATE ../common
)
target_link_libraries(
  day11
  PUBLIC project_options project_warnings common
  )