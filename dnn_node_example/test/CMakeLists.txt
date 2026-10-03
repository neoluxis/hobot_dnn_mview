# Register detector coordinate behavior tests when explicitly enabled.
option(BUILD_NL_DETECTION_GEOMETRY_TESTS "Build detection geometry tests" OFF)
if(BUILD_NLX_TESTS AND BUILD_DNN_NODE_EXAMPLE_TESTS AND BUILD_NL_DETECTION_GEOMETRY_TESTS)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(detection_geometry_tests
    detection_geometry_test.cpp detection_result_builder_test.cpp)
  target_link_libraries(detection_geometry_tests detection_geometry)
endif()
