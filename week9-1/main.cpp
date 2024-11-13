#include <iostream>
#include <string.h>
typedef char ElemType;
typedef  struct  BiNode
{   ElemType  data;
    struct  BiNode   *lchild,*rchild;
    BiNode(char str, BiNode* left, BiNode* right)
    {
        this->data = str;
        lchild = left;
        rchild = right;
    }
}BiNode,*BiTree;  

struct QueueNode
{
    BiTree node;
    QueueNode* next;
    QueueNode(BiTree n) : node(n), next(nullptr) {}
};


struct Queue
{  
    QueueNode* front;
    QueueNode* rear;

    Queue()
    {
        front = rear = nullptr;
    }

    bool empty()
    {
        return front == nullptr;
    }

    void push(BiTree n)
    {
        QueueNode* newNode = new QueueNode(n);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    BiTree pop()
    {
        if (empty()) return nullptr;
        QueueNode* temp = front;
        BiTree ret = temp->node;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete temp;
        return ret;
    }
};


using namespace std;

//创建二叉树
int index1 = 0;
BiTree createTree(const char* preOrder)
{
    if (index1 >= strlen(preOrder))
    {
        return nullptr;
    }
    char current = preOrder[index1++];
    if (current == '#')
    {
        return nullptr;
    }
    BiTree node = new BiNode(current, nullptr, nullptr);
    node->lchild = createTree(preOrder);
    node->rchild = createTree(preOrder);
    return node;
}

//中序遍历
void inOrder(BiTree root)
{
    if (root == nullptr)
    {
        return;
    }
    inOrder(root->lchild);
    cout << root->data << "";
    inOrder(root->rchild);
}

//层序遍历
void levelOrder(BiTree root)
{
    if (root == nullptr)
    {
        return;
    }
    Queue q;
    q.push(root);
    while (!q.empty())
    {
        BiTree current = q.pop();
        cout << current->data;
        if (current->lchild != nullptr)
        {
            q.push(current->lchild);
        }
        if (current->rchild != nullptr)
        {
            q.push(current->rchild);
        }
    }
    cout << endl;
}

int getDepth(BiTree root)
{
    if (root == nullptr) return 0;
    int leftDepth = getDepth(root->lchild);
    int rightDepth = getDepth(root->rchild);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void getLeaf(BiTree root)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->lchild == nullptr && root->rchild == nullptr)
    {
        cout << root->data;
        return;
    }
    else if (root->lchild == nullptr)
    {
        getLeaf(root->lchild);
    }
    else if (root->rchild == nullptr)
    {
        getLeaf(root->rchild);
    }
}

int main()
{
    char preOrder[101] = "\0";
    cin >> preOrder;
    BiTree root = createTree(preOrder);
    inOrder(root);
    cout<<endl;
    levelOrder(root);
    int depth = getDepth(root);
    cout << depth<<endl;
    getLeaf(root);
    cout<<"hello,world";
    
    return 0;
}
