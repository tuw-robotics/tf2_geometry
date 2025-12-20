if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)

  ament_add_gtest(test_geometry 
    test_vector2.cpp 
    test_vector4.cpp 
    test_point2d.cpp 
    test_line2d.cpp
    test_plane3d.cpp
    test_transform2d.cpp
    test_linesegment2d.cpp
    test_convert.cpp)  # Need to link .cpp file under test

  target_include_directories(test_geometry PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(test_geometry tf2_geometry)

  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  install(
    TARGETS test_geometry
    DESTINATION lib/${PROJECT_NAME}
  )
  ament_lint_auto_find_test_dependencies()
endif()
