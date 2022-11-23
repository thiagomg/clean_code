# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable. Improve that with a src/CMakeList.txt file
add_executable (CleanCode 
	"CleanCodeMain.cpp" 
	"CleanCodeMain.h"
	"src/board.cpp"
	"src/board_slow.cpp" "src/max_area_of_island.cpp" 
	"src/search_matrix.cpp" "src/rotated_bin_search.cpp" 
	"src/intervals.cpp" "src/tree_transversal.cpp" 
	"src/bin_tree_transv_inv.cpp" "src/tree_zigzag.cpp" "src/tree_util.h" 
	"src/tree_avg.cpp"  "src/sub_tree.cpp" 
	"src/is_valid_bst.cpp" "src/frequency_sort.cpp" "src/find_kth_largest.cpp" 
	"src/reorganize_string.cpp" "src/calculator.cpp" "src/min_max.cpp" 
	"src/linked_list_circle.cpp" "src/fastest_path.cpp" "src/bin_search_range.cpp" 
	"src/html_parser.cpp"
)

target_include_directories(CleanCode PUBLIC
	"src/"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CleanCode PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
