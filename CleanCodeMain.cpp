#include "CleanCodeMain.h"

#include <string>
#include <vector>

using namespace std;

namespace board { void run(); }
namespace slow_board { void run(); }
namespace island { void run(); }
namespace search_matrix { void run(); }
namespace intervals_ns { void run(); }
namespace bin_tree_transv { void run(); }
namespace bin_tree_transv_inv { void run(); }
namespace tree_zigzag { void run(); }
namespace tree_avg { void run(); }
namespace tree_serialize { void run(); }
namespace is_valid_bst { void run(); }
namespace sub_tree { void run(); }
namespace frequency_sort { void run(); }
namespace find_kth_largest { void run(); }
namespace reorganize_string { void run(); }
namespace calculator { void run(); }
namespace min_max { void run(); }
namespace linked_list_circle { void run(); }
namespace fastest_path { void run(); }
namespace bin_search_range { void run(); }
namespace html_parser { void run(); }

// to use in hacker rank
std::pair<std::vector<std::string>, std::vector<std::string>> get_input() {
    int html_lines, query_lines;
    std::cin >> html_lines;
    std::cin >> query_lines;

    std::vector<std::string> html(html_lines);
    std::vector<std::string> queries(query_lines);

    std::getline(std::cin, html[0]);

    for (int i = 0; i < html_lines; ++i) {
        std::getline(std::cin, html[i]);
    }
    for (int i = 0; i < query_lines; ++i) {
        std::getline(std::cin, queries[i]);
    }

    // std::cout << "html " << html_lines << " - " << query_lines << std::endl;
    // for(int i=0; i < html_lines; ++i) {
    //     std::cout << i << " " << html[i] << std::endl;
    // }
    // for(int i=0; i < query_lines; ++i) {
    //     std::cout << i << " " << queries[i] << std::endl;
    // }
    return { html, queries };
}

int main()
{
	html_parser::run();
	return 0;
}
