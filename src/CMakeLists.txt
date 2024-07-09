add_library(binarylinalg utils.c matrix.c solve_linear_system.c extend_check_matrix.c)

# ensure the headers can be found
target_include_directories(binarylinalg PUBLIC
	"${PROJECT_SOURCE_DIR}/include"
)
