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

target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "TF2_GEOMETRY_BUILDING_LIBRARY")

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  tf2
)

install(
  DIRECTORY include/
  DESTINATION include
)



install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
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

add_subdirectory(test)

ament_package()
