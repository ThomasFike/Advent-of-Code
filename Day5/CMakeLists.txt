add_executable(day5 day5.cpp)
target_include_directories(
  day5
  PRIVATE ../common
)
target_link_libraries(
  day5
  PUBLIC project_options project_warnings common
  )