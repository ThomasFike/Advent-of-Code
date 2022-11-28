add_executable(test_folder test.cpp)
target_include_directories(
  test_folder
  PRIVATE ../common
)
target_link_libraries(
  test_folder
  PUBLIC project_options project_warnings common
  )