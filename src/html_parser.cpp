// https://www.hackerrank.com/challenges/attribute-parser/submissions/code/301077041

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string_view>
#include <string>
#include <optional>

using namespace std;

namespace html_parser {

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

         std::cout << "html " << html_lines << " - " << query_lines << std::endl;
         for(int i=0; i < html_lines; ++i) {
             std::cout << i << " " << html[i] << std::endl;
         }
         for(int i=0; i < query_lines; ++i) {
             std::cout << i << " " << queries[i] << std::endl;
         }
        return { html, queries };
    }

    auto remove_spaces(std::string::const_iterator start, std::string::const_iterator end)
        -> std::string::const_iterator {
        for (; start != end; ++start) {
            if (std::isspace(*start) || *start == '\r' || *start == '\n') {
                continue;
            }
            break;
        }
        return start;
    }

    auto get_symbol(std::string::const_iterator start, std::string::const_iterator end)
        -> pair<
        std::string, // symbol
        std::string::const_iterator // last processed char, inclusive
        > {

        // symbols can be <, </, >, =
        start = remove_spaces(start, end);

        if (*start == '<') {
            auto next = start + 1;
            if (next != end && *next == '/') {
                return { "</", next + 1 };
            }
            return { "<", start + 1 };
        }

        std::string symbol;
        switch (*start) {
        case '=':
        case '>':
            symbol += *start;
            break;
        default:
            // Syntax error
            throw std::runtime_error("Ouch");
        }

        return { symbol, start + 1 };
    }

    auto get_string(std::string::const_iterator start, std::string::const_iterator end)
        -> pair<
        std::string, // symbol
        std::string::const_iterator // last processed char, inclusive
        > {

        start = remove_spaces(start, end);

        // Strings are "xxxxxx"
        if (*start != '"') {
            throw std::runtime_error("Ouch str 1");
        }

        ++start;
        auto str_start = start;
        for (; *start != '"'; ++start) {
            if (start == end) { throw std::runtime_error("Ouch str 2"); }
        }

        std::string value(str_start, start);

        return { value, start + 1 };
    }

    auto get_word(std::string::const_iterator start, std::string::const_iterator end)
        -> pair<
        std::string, // symbol
        std::string::const_iterator // last processed char, inclusive
        > {

        start = remove_spaces(start, end);

        auto word_start = start;
        for (; start != end; ++start) {
            if (std::isalnum(*start) || *start == '-' || *start == '_') {
                continue;
            }
            break;
        }

        std::string value(word_start, start);

        // It stops after the last word char, hence we don't need to increment start
        return { value, start };
    }

    struct parser_context {
        std::unordered_map<std::string, std::string> result;
        std::vector<std::string> tags;
        void add_tag(std::string_view tag_name) {
            tags.emplace_back(tag_name);
        }
        void remove_tag(std::string_view tag_name) {
            // TODO: Check tag_name
            tags.pop_back();
        }
        void add_attrib(std::string_view name, std::string_view value) {
            std::string key = "";
            for (auto& tag : tags) {
                if (!key.empty()) key += ".";
                key += tag;
            }
            key += "~";
            key += name;
            result[key] = value;
        }
    };

    auto process_tag(parser_context &context, std::string::const_iterator start, std::string::const_iterator end)
    -> std::string::const_iterator {
        {
            start = remove_spaces(start, end);
            if (start == end) {
                return end;
            }

            std::string symbol1, symbol2, tag_name;

            // It has to be <
            std::tie(symbol1, start) = get_symbol(start, end);
            std::tie(tag_name, start) = get_word(start, end);

            // std::cout << "TAG: " << tag_name << std::endl;
            if(symbol1 == "<") {
                context.add_tag(tag_name);
            } else if (symbol1 == "</") {
                context.remove_tag(tag_name);
            }

            start = remove_spaces(start, end);
            while (*start != '>') {
                std::string attrib;
                std::string equal;
                std::string value;
                std::tie(attrib, start) = get_word(start, end); 
                std::tie(equal, start) = get_symbol(start, end); // It has to be equal
                std::tie(value, start) = get_string(start, end);
                // std::cout << "- " << attrib << " -> " << value << std::endl;
                context.add_attrib(attrib, value);
            }

            // It has to be >
            std::tie(symbol2, start) = get_symbol(start, end);

            // Now we store the values in the structures and go to the next
        }
        return start;
    }

    parser_context parse_lines(const std::vector<std::string>& lines) {
        parser_context context;
        for (const std::string& buffer : lines) {
            // We might have more than one tag per line
            auto start = std::cbegin(buffer);
            auto end = std::cend(buffer);
            while (true) {
                start = process_tag(context, start, end);
                if (start == end) { break; }
            }
        }
        return context;
    }

    std::optional<std::string> run_query(const parser_context& context, const std::string& key) {
        auto it = context.result.find(key);
        if (it != context.result.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void run() {
        // auto [html, queries] = get_input();
        std::vector<std::string> html = {
            R"-(<tag1 value = "HelloWorld" another-value = "HelloWorld2">)-",
            R"-(<tag2 name = "Name1">)-",
            R"-(</tag2>)-",
            R"-(</tag1>)-"
        };

        std::vector<std::string> queries = {
            R"-(tag1.tag2~name)-",
            R"-(tag1~name)-",
            R"-(tag1~value)-"
        };

        parser_context context = parse_lines(html);
        for (auto& query : queries) {
            std::cout << run_query(context, query).value_or("Not Found!") << std::endl;
        }        
    }
}