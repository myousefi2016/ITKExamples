cmake_minimum_required( VERSION 2.8.5 )

project( ApplyMedianFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyMedianFilter Code.cxx )
target_link_libraries( ApplyMedianFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyMedianFilter
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/ApplyMedianFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyMedianFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyMedianFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    2
)