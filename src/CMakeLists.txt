add_library(binarylinalg utils.c matrix.c solve_linear_system.c extend_check_matrix.c)
#target_include_directories(binarylinalg PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
#  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
#)

# ensure the headers can be found
target_include_directories(binarylinalg PUBLIC
	"${PROJECT_SOURCE_DIR}/include"
)
