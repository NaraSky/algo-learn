#include <cstdlib>
#include <iostream>
using namespace std;

// 定义二叉树节点结构
typedef struct Node {
    int key;        // 节点存储的值
    int ltag, rtag; // ltag 和 rtag: 标志位，表示线索状态 (1: 线索, 0: 子节点)
    struct Node *lchild; // 左子节点或前驱
    struct Node *rchild; // 右子节点或后继
} Node;

// 创建新节点
Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node)); // 动态分配内存
    p->key = key;                           // 初始化 key
    p->ltag = p->rtag = 0;                  // 默认无线索
    p->lchild = p->rchild = NULL;           // 左右子节点为空
    return p;
}

// 随机插入节点，生成随机二叉树
Node *insert(Node *root, int key) {
    if (root == NULL)
        return getNewNode(key); // 如果当前节点为空，创建新节点
    if (rand() % 2)
        root->lchild = insert(root->lchild, key); // 随机选择左子树
    else
        root->rchild = insert(root->rchild, key); // 或右子树
    return root;
}

// 递归清理二叉树内存
void clear(Node *root) {
    if (root == NULL)
        return; // 空树直接返回
    if (root->ltag == 0)
        clear(root->lchild); // 若左子树非线索，递归清理左子树
    if (root->rtag == 0)
        clear(root->rchild); // 若右子树非线索，递归清理右子树
    free(root);              // 释放当前节点
}

// 先序遍历（根 -> 左 -> 右）
void pre_order(Node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->key); // 打印当前节点
    if (root->ltag == 0)
        pre_order(root->lchild); // 遍历左子树（若非线索）
    if (root->rtag == 0)
        pre_order(root->rchild); // 遍历右子树（若非线索）
}

// 中序遍历（左 -> 根 -> 右）
void in_order(Node *root) {
    if (root == NULL)
        return;
    if (root->ltag == 0)
        in_order(root->lchild); // 遍历左子树（若非线索）
    printf("%d ", root->key);   // 打印当前节点
    if (root->rtag == 0)
        in_order(root->rchild); // 遍历右子树（若非线索）
}

// 后序遍历（左 -> 右 -> 根）
void post_order(Node *root) {
    if (root == NULL)
        return;
    if (root->ltag == 0)
        post_order(root->lchild); // 遍历左子树（若非线索）
    if (root->rtag == 0)
        post_order(root->rchild); // 遍历右子树（若非线索）
    printf("%d ", root->key);     // 打印当前节点
}

// 全局变量，用于记录当前节点的前驱
Node *pre_node = NULL, *inorder_root = NULL;

// 递归构建中序线索树
void __build_inorder_thread(Node *root) {
    if (root == NULL)
        return;

    // 处理左子树
    if (root->ltag == 0)
        __build_inorder_thread(root->lchild);

    // 设置中序遍历的起始点
    if (inorder_root == NULL)
        inorder_root = root;

    // 如果当前节点左子树为空，设置左线索指向前驱
    if (root->lchild == NULL) {
        root->lchild = pre_node;
        root->ltag = 1; // 标记为线索
    }

    // 如果前驱节点的右子树为空，设置右线索指向当前节点
    if (pre_node && pre_node->rchild == NULL) {
        pre_node->rchild = root;
        pre_node->rtag = 1; // 标记为线索
    }

    // 更新前驱节点
    pre_node = root;

    // 处理右子树
    if (root->rtag == 0)
        __build_inorder_thread(root->rchild);
}

// 构建中序线索树的入口函数
void build_inorder_thread(Node *root) {
    __build_inorder_thread(root);
    // 处理最后一个节点的后继
    if (pre_node) {
        pre_node->rchild = NULL;
        pre_node->rtag = 1; // 标记为线索
    }
}

// 获取中序遍历的下一个节点
Node *getNext(Node *root) {
    if (root->rtag == 1)
        return root->rchild; // 如果是线索，直接返回后继节点
    root = root->rchild;     // 否则进入右子树
    while (root->ltag == 0 && root->lchild)
        root = root->lchild; // 找到右子树中最左的节点
    return root;
}

int main() {
    srand(time(0)); // 设置随机数种子
    Node *root = NULL;

// 创建随机二叉树
#define MAX_NODE 10
    for (int i = 0; i < MAX_NODE; i++) {
        root = insert(root, rand() % 100); // 插入随机值
    }

    // 构建中序线索树
    pre_node = inorder_root = NULL;
    build_inorder_thread(root);

    // 打印先序、中序、后序遍历结果
    pre_order(root);
    printf("\n");
    in_order(root);
    printf("\n");
    post_order(root);
    printf("\n");

    // 使用线索化结构进行中序遍历
    Node *node = inorder_root;
    while (node) {
        printf("%d ", node->key);
        node = getNext(node); // 获取中序遍历的下一个节点
    }
    printf("\n");

    // 清理内存
    clear(root);
    return 0;
}
