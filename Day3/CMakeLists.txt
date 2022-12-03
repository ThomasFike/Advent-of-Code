add_executable(day3 day3.cpp)
target_include_directories(
  day3
  PRIVATE ../common
)
target_link_libraries(
  day3
  PUBLIC project_options project_warnings common
  )