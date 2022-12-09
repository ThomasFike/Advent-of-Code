add_executable(day8 day8.cpp)
target_include_directories(
  day8
  PRIVATE ../common
)
target_link_libraries(
  day8
  PUBLIC project_options project_warnings common
  )