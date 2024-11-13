#include <iostream>

using namespace std;

typedef struct Node
{
    int pi;
    Node* lchild;
    Node* rsibling;
} Node;

Node nodes[1001]; // 假设最多有 1000 个节点
int level_count[1001]; // 用于记录每一层的节点数

void addChild(Node* parent, Node* child)
{
    if (parent->lchild == nullptr)
    {
        parent->lchild = child;
    }
    else
    {
        Node* sibling = parent->lchild;
        while (sibling->rsibling != nullptr)
        {
            sibling = sibling->rsibling;
        }
        sibling->rsibling = child;
    }
}

int calculateHeight(Node* root)
{
    if (root == nullptr)
        return 0;
    int height = 0;
    Node* child = root->lchild;
    while (child != nullptr)
    {
        height = max(height, calculateHeight(child));
        child = child->rsibling;
    }
    return height + 1;
}

void calculateWidth(Node* root, int level)
{
    if (root == nullptr)
        return;
    level_count[level]++;
    Node* child = root->lchild;
    while (child != nullptr)
    {
        calculateWidth(child, level + 1);
        child = child->rsibling;
    }
}

int main()
{
    int N;
    cin >> N;
    int parent[1001];
    for (int i = 1; i <= N; i++)
    {
        cin >> parent[i];
        nodes[i].pi = i;
        nodes[i].lchild = nullptr;
        nodes[i].rsibling = nullptr;
    }

    Node* root = nullptr;
    for (int i = 1; i <= N; i++)
    {
        if (parent[i] == 0)
        {
            root = &nodes[i];
        }
        else
        {
            addChild(&nodes[parent[i]], &nodes[i]);
        }
    }

    int height = calculateHeight(root);
    calculateWidth(root, 1);

    int max_width = 0;
    for (int i = 1; i <= N; i++)
    {
        if (level_count[i] > max_width)
        {
            max_width = level_count[i];
        }
    }

    cout << height << "、" << max_width << endl;

    return 0;
}