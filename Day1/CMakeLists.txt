add_executable(day1 day1.cpp)
target_include_directories(
  day1
  PRIVATE ../common
)
target_link_libraries(
  day1
  PUBLIC project_options project_warnings common
  )