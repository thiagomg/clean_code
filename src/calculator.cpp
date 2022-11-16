#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <functional>
#include <algorithm>

namespace calculator {

	struct coutln {
		template<typename T>
		coutln& operator <<(const T& t) {
			std::cout << t;
			return *this;
		}

		~coutln() {
			std::cout << std::endl;
		}
	};

	enum class token_type { num, op, unknown };

	std::tuple<std::string, token_type, std::string::const_iterator> next_token(std::string::const_iterator b, std::string::const_iterator e) {
		if (b == e) {
			return {"", token_type::unknown, e};
		}

		// Let's remove the spaces
		while (b != e) {
			if (*b != ' ') {
				break;
			}
			++b;
		}

		bool stop = false;
		token_type type;
		std::function<bool(char c)> same_type;
		if(std::isdigit(*b)) {
			same_type = std::isdigit;
			type = token_type::num;
		}
		else {
			same_type = [&stop](char c) -> bool {
				bool is_operation = !std::isdigit(c);
				if (is_operation) { stop = true; } // Single char
				return is_operation;
			};
			type = token_type::op;
		}

		std::string token;
		while (b != e) {
			if (same_type(*b)) {
				token += *b;
			} else {
				break;
			}
			++b;

			if (stop) {
				break;
			}
		}

		return { token, type, b };
	}

	// greater means more priority
	int priority(const std::string& op) {
		if (op == "^") { return 3; }
		if (op == "*" || op == "/") { return 2; }
		/* (op == "+" || op == "-") */ return 1;
	}

	template<typename T>
	T remove(std::stack<T>& s) {
		T item = s.top();
		s.pop();
		return item;
	}

	int64_t apply_op(const std::string& op, int64_t op1, int64_t op2) {
		if (op == "+") {
			return op1 + op2;
		}
		if (op == "-") {
			return op1 - op2;
		}
		if (op == "*") {
			return op1 * op2;
		}
		if (op == "/") {
			return op1 / op2;
		}
		if (op == "^") {
			return std::pow(op1, op2);
		}
		// TODO: Ops!
		return 0;
	}

	int64_t calculate(const std::string& sentence) {
		std::stack<int64_t> nums;
		std::stack<std::string> ops;

		token_type last_token_type = token_type::op;
		std::string saved_token;

		auto it = std::cbegin(sentence);
		while (it != std::cend(sentence)) {
			auto [token, type, next] = next_token(it, std::cend(sentence));
			
			if (it == std::cbegin(sentence) && token == "-") {
				saved_token = token;
				it = next;
				continue;
			}
			else if(last_token_type == token_type::op && token == "-") {
				saved_token = token;
				it = next;
				continue;
			}

			token = saved_token + token;
			saved_token.clear();
			last_token_type = type;

			std::cout << "[" << token << "]";

			switch (type) {
			case token_type::num: {
				int64_t val = std::stoll(token);
				nums.push(val);
				break;
			}
			case token_type::op: {
				if (ops.empty()) {
					ops.push(token);
					break;
				}

				// If what's in the stack has a more priority or equal, we need to resolve
				int stack_top_p = priority(ops.top());
				int tok_p = priority(token);
				if (tok_p <= stack_top_p) {
					int64_t newest = remove(nums);
					int64_t oldest = remove(nums);
					std::string op = remove(ops);
					int64_t result = apply_op(op, oldest, newest);
					nums.push(result);
				}

				// And add operation to the stack
				ops.push(token);

				break;
			}
			default:
				// TODO: Error - unknown token
				it = it;
			}

			it = next;
		}

		// Calculate everything in order when ending
		while (nums.size() != 1) {
			int64_t newest = remove(nums);
			int64_t oldest = remove(nums);
			std::string op = remove(ops);
			int64_t result = apply_op(op, oldest, newest);
			nums.push(result);
		}

		std::cout << std::endl;

		return nums.top();
	}

	void run() {
		// TODO: Add support to parenthesis and negative numbers


		std::vector<int> v { 5, 2,1, 8,7 };
		auto r1 = std::min_element(begin(v), end(v));
		auto r2 = std::max_element(begin(v), end(v));

		std::string sentence;

		//sentence = "1 + 2+3    * 9";
		//coutln() << calculate(sentence);
		//
		//sentence = "6 - 2 * 3 ^ 2";
		//coutln() << calculate(sentence);

		//sentence = "6 - 2 * -3 ^ 2";
		//coutln() << calculate(sentence);

		sentence = "6 - 2 *-3 ^ 2";
		coutln() << calculate(sentence);
	}
}