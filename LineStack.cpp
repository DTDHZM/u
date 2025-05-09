#include "LineStack.h"
#include <stdexcept> // 修复 runtime_error 错误
//添加此行用于UTF-8另存
void LineStack::push(const Line& line) {
    stack.push(line);
}

Line LineStack::pop() {
    if (stack.empty()) throw std::runtime_error("Stack is empty"); // 修复 runtime_error 错误
    Line top = stack.top();
    stack.pop();
    return top;
}

bool LineStack::isEmpty() const {
    return stack.empty();
}

std::vector<Line> LineStack::getAllLines() const {
    std::vector<Line> lines;
    std::stack<Line> tempStack = stack;

    while (!tempStack.empty()) {
        lines.insert(lines.begin(), tempStack.top());
        tempStack.pop();
    }
    return lines;
}
