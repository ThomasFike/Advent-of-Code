add_executable(day6 day6.cpp)
target_include_directories(
  day6
  PRIVATE ../common
)
target_link_libraries(
  day6
  PUBLIC project_options project_warnings common
  )