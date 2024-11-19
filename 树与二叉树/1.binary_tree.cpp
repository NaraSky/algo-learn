#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义二叉树节点的结构体
typedef struct Node {
    int key;                      // 节点的键值
    struct Node *lchild, *rchild; // 左右子节点指针
} Node;

// 创建新节点的函数
Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node)); // 分配内存空间
    p->key = key;                           // 设置节点键值
    p->lchild = p->rchild = NULL;           // 初始化左右子节点为空
    return p;
}

// 插入节点到二叉树
Node *insert(Node *root, int key) {
    if (root == NULL)
        return getNewNode(key); // 如果当前根节点为空，直接创建新节点
    if (rand() % 2)             // 随机决定插入左子树还是右子树
        root->lchild = insert(root->lchild, key);
    else
        root->rchild = insert(root->rchild, key);
    return root; // 返回更新后的根节点
}

// 递归清空二叉树的内存
void clear(Node *root) {
    if (root == NULL)
        return;          // 空树不需要处理
    clear(root->lchild); // 递归清理左子树
    clear(root->rchild); // 递归清理右子树
    free(root);          // 释放当前节点的内存
    return;
}

#define MAX_NODE 10        // 定义最大节点数
Node *queue[MAX_NODE + 5]; // 定义队列，用于广度优先遍历
int head, tail;            // 队列头尾指针

// 广度优先遍历 (BFS)
void bfs(Node *root) {
    head = tail = 0;                        // 初始化队列指针
    queue[tail++] = root;                   // 将根节点加入队列
    while (head < tail) {                   // 队列非空时继续循环
        Node *node = queue[head];           // 取出队首节点
        printf("\nnode : %d\n", node->key); // 输出当前节点的值
        if (node->lchild) {                 // 如果有左子节点，加入队列
            queue[tail++] = node->lchild;
            printf("\t%d->%d (left)\n", node->key, node->lchild->key);
        }
        if (node->rchild) { // 如果有右子节点，加入队列
            queue[tail++] = node->rchild;
            printf("\t%d->%d (right)\n", node->key, node->rchild->key);
        }
        head++; // 队首指针后移
    }
    return;
}

int tot = 0; // 记录深度优先遍历的计数器

// 深度优先遍历 (DFS)，同时打印每个节点的时间区间
void dfs(Node *root) {
    if (root == NULL)
        return; // 空节点直接返回
    int start, end;
    tot += 1;    // 进入当前节点时计数器加一
    start = tot; // 记录进入时间
    if (root->lchild)
        dfs(root->lchild); // 递归处理左子节点
    if (root->rchild)
        dfs(root->rchild); // 递归处理右子节点
    tot += 1;              // 离开当前节点时计数器加一
    end = tot;             // 记录离开时间
    printf("%d : [%d, %d]\n", root->key, start, end); // 输出当前节点的时间区间
    return;
}

int main() {
    srand(time(0));    // 初始化随机数种子
    Node *root = NULL; // 初始化二叉树为空
    for (int i = 0; i < MAX_NODE; i++) {
        root = insert(root, rand() % 100); // 插入随机键值的节点
    }
    bfs(root); // 调用广度优先遍历
    dfs(root); // 调用深度优先遍历
    return 0;
}
