#include <iostream>
#include <stack>
#include <string>

bool areParenthesesMatched(const std::string &expression) {
    std::stack<char> s;

    for (char ch : expression) {
        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            if (s.empty()) {
                return false; // 右括号没有匹配的左括号
            }
            s.pop();
        } else if (ch == '@') {
            break; // 遇到结束符
        }
    }

    return s.empty(); // 如果栈为空，说明括号匹配
}

int main() {
    std::string expression;
    std::getline(std::cin, expression); // 读取输入

    if (areParenthesesMatched(expression)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
