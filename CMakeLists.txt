cmake_minimum_required(VERSION 3.8)
project(tf2_geometry)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)


add_library(${PROJECT_NAME} SHARED
  src/vector2.cpp
  src/vector4.cpp
  src/point2d.cpp
  src/point3d.cpp
  src/line2d.cpp
  src/linesegment2d.cpp
  src/plane3d.cpp
  src/transform2d.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE "CUSTOM_ACTION_CPP_BUILDING_DLL"
)

ament_target_dependencies(${PROJECT_NAME}
  tf2
)

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
    test/test_vector2.cpp 
    test/test_vector4.cpp 
    test/test_point2d.cpp 
    test/test_line2d.cpp
    test/test_plane3d.cpp
    test/test_transform2d.cpp
    test/test_linesegment2d.cpp)  # Need to link .cpp file under test
  target_include_directories(test_geometry PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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

install(DIRECTORY include
  DESTINATION include
)

install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(TARGETS 
  ${PROJECT_NAME} 
  EXPORT 
  export_${PROJECT_NAME}
)

ament_export_include_directories(
  include
)

ament_export_libraries(
  ${PROJECT_NAME}
)

ament_export_targets(
  export_${PROJECT_NAME}
)

ament_export_dependencies(
  tf2
)
ament_package()
