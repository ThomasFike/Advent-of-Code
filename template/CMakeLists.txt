add_executable(template test.cpp)
target_include_directories(
  template
  PRIVATE ../common
)
target_link_libraries(
  template
  PUBLIC project_options project_warnings common
  )