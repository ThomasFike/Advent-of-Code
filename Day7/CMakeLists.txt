add_executable(day7 day7.cpp)
target_include_directories(
  day7
  PRIVATE ../common
)
target_link_libraries(
  day7
  PUBLIC project_options project_warnings common
  )