add_executable(day4 day4.cpp)
target_include_directories(
  day4
  PRIVATE ../common
)
target_link_libraries(
  day4
  PUBLIC project_options project_warnings common
  )