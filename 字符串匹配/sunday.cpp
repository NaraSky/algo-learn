#include <cstring> // 用于strlen
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
            // 如果当前位置字符不匹配，标记为没有找到匹配、
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

// Sunday 算法实现
// 如果字符没有在子串规则中出现，直接移动子串长度+1
// 否则向右移动子串中该字符到末尾的长度+1
int sunday(const char *s, const char *t) {
    int len[256] = {0}, n = strlen(s), m = strlen(t);
    // 初始化 len 数组：每个字符默认跳过整个模式串长度 m+1
    for (int i = 0; i < 256; i++)
        len[i] = m + 1;
    // 计算模式串t中每个字符的跳跃长度
    for (int i = 0; t[i]; i++)
        len[t[i]] = m - i;
    // 外层循环：检查s中的每个位置，步长是 len[s[i+m]]，即字符s[i+m]的位置跳跃
    for (int i = 0; i + m <= n; i += len[s[i + m]]) {
        int flag = 1; // 标志变量，检查是否匹配
        // 内层循环：逐字符比较模式串t与主串s当前对齐的部分
        for (int j = 0; t[j]; j++) {
            if (s[i + j] == t[j])
                continue; // 字符匹配则继续
            flag = 0;     // 如果有不匹配的字符，标记为未匹配
            break;        // 立即跳出内层循环
        }
        // 如果所有字符都匹配，返回当前匹配位置
        if (flag == 1)
            return i; // 找到匹配的子字符串，返回其起始位置
    }
    return -1; // 如果循环结束没有找到匹配，返回-1
}

int main() {
    char s[100], t[100];
    // 逐行读取两个字符串并进行匹配测试
    while (~scanf("%s%s", s, t)) {
        TEST(brute_force, s, t); // 测试暴力匹配算法
        TEST(sunday, s, t);      // 测试Sunday算法
    }
    return 0;
}
