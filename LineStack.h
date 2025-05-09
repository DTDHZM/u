#ifndef LINESTACK_H
#define LINESTACK_H
//添加此行用于UTF-8另存
#include <stack>
#include <vector> // 修复 vector 错误
#include <QString>

struct Line {
    int x1, y1, x2, y2;
    QString name; // line名称
};

class LineStack {
public:
    void push(const Line& line);
    Line pop();
    bool isEmpty() const;
    std::vector<Line> getAllLines() const; // 修复 vector 错误

private:
    std::stack<Line> stack;
};

#endif // LINESTACK_H
