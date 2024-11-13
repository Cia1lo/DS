#include <iostream>

using namespace std;

typedef struct Node
{
    int pi;
    int parent;
    int lchild;
    int rchild;
} Node;

int path[1001]; // 保存当前路径
int pathLen = 0;
int all = 0;

void dfs(Node Tree[], int current)
{
    path[pathLen++] = current; // 将当前节点加入路径

    // 判断是否是叶子节点
    if (Tree[current - 1].lchild == 0 && Tree[current - 1].rchild == 0)
    {
        // 如果是叶子节点，输出路径
        for (int i = 0; i < pathLen; ++i)
        {
            cout << Tree[path[i] - 1].pi;
            if (i < pathLen - 1)
                cout << "-";
        }
        cout << ","; // 使用换行符号结束输出
    }
    else
    {
        // 继续遍历左子树和右子树
        if (Tree[current - 1].lchild != 0)
            dfs(Tree, Tree[current - 1].lchild);

        if (Tree[current - 1].rchild != 0)
            dfs(Tree, Tree[current - 1].rchild);
    }
    
    pathLen--; // 递归返回前，路径长度减一
}

int main()
{
    int root = 0;
    cin >> all;
    int parent_Node[all];
    Node node[all];

    // 读取父节点信息并初始化节点
    for (int i = 0; i < all; i++)
    {
        cin >> parent_Node[i];
        node[i].pi = i + 1; // 节点编号从 1 开始
        node[i].parent = parent_Node[i];
        node[i].lchild = 0;
        node[i].rchild = 0;
    }

    // 构建树
    for (int i = 1; i <= all; i++)
    {
        int p = parent_Node[i - 1];
        if (p == 0)
        {
            root = i; // 找到根节点
        }
        else
        {
            // 将当前节点作为其父节点的子节点
            if (node[p - 1].lchild == 0)
            {
                node[p - 1].lchild = i;
            }
            else if (node[p - 1].rchild == 0)
            {
                node[p - 1].rchild = i;
            }
        }
    }

    // 调用 dfs 函数
    dfs(node, root);
    cout << endl;

    return 0;
}
