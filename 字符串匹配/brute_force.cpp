#include <iostream>
using namespace std;

// 宏定义 TEST 用于打印测试函数的调用和结果
#define TEST(func, s, t)                                                       \
    {                                                                          \
        printf("%s(%s, %s) = %d\n", #func, s, t, func(s, t));                  \
    }

int brute_force(const char *s, const char *t) {
    // 外层循环遍历主字符串s的每个字符
    for (int i = 0; s[i]; i++) {
        int flag = 1; // 标志变量，用于标识当前是否找到匹配的子字符串

        // 内层循环遍历模式字符串t的每个字符
        for (int j = 0; t[j]; j++) {
            // 如果当前位置字符不匹配，标记为没有找到匹配
            if (s[i + j] == t[j])
                continue; // 如果字符相同，继续检查下一个字符
            flag = 0;     // 不匹配时，标记为未找到
            break;        // 立即跳出内层循环，因为当前匹配失败
        }

        // 如果所有字符都匹配，返回当前匹配位置
        if (flag == 1)
            return i; // 找到了匹配的子字符串，返回其起始位置
    }

    return -1; // 如果循环结束仍未找到匹配，返回-1表示没有找到
}

int main() {
    char s[100], t[100];

    // 使用 scanf 输入两个字符串s和t，直到遇到输入结束
    while (~scanf("%s%s", s, t)) {
        // 测试 brute_force 函数的结果，并打印函数调用及返回值
        TEST(brute_force, s, t);
    }

    return 0;
}
