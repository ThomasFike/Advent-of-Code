add_executable(day9 day9.cpp)
target_include_directories(
  day9
  PRIVATE ../common
)
target_link_libraries(
  day9
  PUBLIC project_options project_warnings common
  )