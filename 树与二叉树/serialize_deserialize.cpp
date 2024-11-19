#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define KEY(n) (n ? n->key : -1)
#define MAX_NODE 10

typedef struct Node {
    int key;             // 节点值
    struct Node *lchild; // 左子节点
    struct Node *rchild; // 右子节点
} Node;

// 创建新节点
Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node)); // 动态分配节点内存
    p->key = key;                           // 设置节点值
    p->lchild = p->rchild = NULL;           // 初始化左右子节点为空
    return p;
}

Node *insert(Node *root, int key) {
    if (root == NULL)
        return getNewNode(key); // 若当前节点为空，创建新节点
    if (rand() % 2)
        root->lchild = insert(root->lchild, key); // 随机插入到左子树
    else
        root->rchild = insert(root->rchild, key); // 随机插入到右子树
    return root;
}

// 生成含 n 个随机节点的二叉树
Node *getRandomBinaryTree(int n) {
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, rand() % 100); // 插入随机值（0~99）
    }
    return root;
}

void clear(Node *root) {
    if (root == NULL)
        return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

char buff[1000]; // 序列化的结果存储在字符串缓冲区
int len = 0;     // 当前字符串长度

void __serialize(Node *root) {
    if (root == NULL)
        return;
    len += snprintf(buff + len, 100, "%d", root->key); // 写入当前节点值
    if (root->lchild == NULL && root->rchild == NULL)
        return;                            // 叶子节点直接返回
    len += snprintf(buff + len, 100, "("); // 开始子节点部分
    __serialize(root->lchild);             // 序列化左子树
    if (root->rchild) {                    // 如果存在右子树
        len += snprintf(buff + len, 100, ",");
        __serialize(root->rchild); // 序列化右子树
    }
    len += snprintf(buff + len, 100, ")"); // 子节点部分结束
}

void serialize(Node *root) {
    memset(buff, 0, sizeof(buff)); // 清空缓冲区
    len = 0;                       // 重置长度
    __serialize(root);             // 调用递归序列化函数
}

void print(Node *node) {
    printf("%d(%d, %d)\n", KEY(node), KEY(node->lchild), KEY(node->rchild));
    return;
}

void output(Node *root) {
    if (root == NULL)
        return;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return;
}

Node *deserialize(char *buff, int n) {
    Node **s = (Node **)malloc(sizeof(Node *) * MAX_NODE); // 栈，用于保存父节点
    int top = -1, flag = 0, scode = 0; // 栈顶指针、子节点标志、状态
    Node *p = NULL, *root = NULL;

    for (int i = 0; buff[i]; i++) {
        switch (scode) {
        case 0: { // 初始状态，根据字符决定接下来的操作
            if (buff[i] >= '0' && buff[i] <= '9')
                scode = 1; // 数字
            else if (buff[i] == '(')
                scode = 2; // 左括号
            else if (buff[i] == ',')
                scode = 3; // 逗号
            else
                scode = 4; // 右括号
            i -= 1;        // 回退，确保当前字符被再次处理
        } break;
        case 1: { // 解析节点值
            int key = 0;
            while (buff[i] <= '9' && buff[i] >= '0') { // 累计解析数字
                key = key * 10 + (buff[i] - '0');
                i += 1;
            }
            p = getNewNode(key); // 创建新节点
            if (top >= 0 && flag == 0)
                s[top]->lchild = p; // 连接到左子节点
            if (top >= 0 && flag == 1)
                s[top]->rchild = p; // 连接到右子节点
            i -= 1;                 // 回退字符
            scode = 0;              // 重置状态
        } break;
        case 2: {         // 遇到 `(`
            s[++top] = p; // 将当前节点压入栈中
            flag = 0;     // 设置为左子节点
            scode = 0;    // 重置状态
        } break;
        case 3: {      // 遇到 `,`
            flag = 1;  // 设置为右子节点
            scode = 0; // 重置状态
        } break;
        case 4: {          // 遇到 `)`
            root = s[top]; // 更新当前根节点
            top -= 1;      // 弹出栈
            scode = 0;     // 重置状态
        } break;
        }
    }
    return root;
}

int main() {
    srand(time(0));
    Node *root = getRandomBinaryTree(MAX_NODE); // 随机生成二叉树
    serialize(root);                            // 序列化为字符串
    output(root);                               // 输出原二叉树
    printf("Buff[] : %s\n", buff);              // 打印序列化结果
    Node *new_root = deserialize(buff, len);    // 反序列化回二叉树
    output(new_root);                           // 输出反序列化后的二叉树
    clear(root);                                // 清理内存
    clear(new_root);                            // 清理内存
    return 0;
}
