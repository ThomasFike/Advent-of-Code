add_executable(day2 day2.cpp)
target_include_directories(
  day2
  PRIVATE ../common
)
target_link_libraries(
  day2
  PUBLIC project_options project_warnings common
  )