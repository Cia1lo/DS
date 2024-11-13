#include <iostream>
#include <string.h>
using namespace std;

typedef char ElemType;
typedef  struct  BiNode
{   ElemType  data;
    struct  BiNode   *lchild,*rchild;
    BiNode(char x) : data(x), lchild(nullptr), rchild(nullptr) { };
}BiNode,*BiTree; 
typedef struct StackNode
{
    BiTree node;
    StackNode* next;
    StackNode(BiTree x) : node(x), next(nullptr) {};
}StackNode;

typedef struct Stack
{
    StackNode* topNode;
    Stack()
    {
        topNode = nullptr;
    }
    bool empty()
    {
        return topNode == nullptr;
    }
    void push(BiTree x)
    {
        StackNode* newNode = new StackNode(x);
        newNode->next = topNode;
        topNode = newNode;
    }
    BiTree pop()
    {
        if (topNode == nullptr)
        {
            return nullptr;
        }
        StackNode* temp = topNode;
        BiTree ret = temp->node;
        topNode = topNode->next;
        delete temp;
        return ret;
    }
}Stack;

int index1 = 0;
BiTree preCreate(const char str[])
{
    if (index1 >= strlen(str))
    {
        return nullptr;
    }
    char current = str[index1++];
    if (current == '#')
    {
        return nullptr;
    }
    BiTree node = new BiNode(current);
    node->lchild = preCreate(str);
    node->rchild = preCreate(str);
    return node;
}

void inOrder(BiTree root)
{
    Stack s;
    BiTree current = root;

    while (current != nullptr || !s.empty())
    {
        // 将所有左子节点压入栈
        while (current != nullptr)
        {
            s.push(current);
            current = current->lchild;
        }

        // 弹出栈顶节点并访问
        current = s.pop();
        std::cout << current->data;

        // 转向右子节点
        current = current->rchild;
    }
    cout << endl;
}

typedef struct queueNode
{
    BiTree node;
    queueNode* next;
    queueNode(BiTree x) : node(x), next(nullptr) {};
}queueNode;

typedef struct Queue
{
    queueNode* front;
    queueNode* rear;

    Queue()
    {
        front = rear = nullptr;
    }
    bool empty() {return front == nullptr;}
    void push(BiTree x)
    {
        queueNode* newNode = new queueNode(x);
        if (front == nullptr)
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode; 
    }
    BiTree pop()
    {
        if (this->empty())
        {
            return nullptr;
        }

        queueNode* temp = front;
        front = front->next;
        BiTree ret = temp->node;
        delete temp;
        return ret;
    }
}Queue;

BiTree findParent(BiTree root, char target)
{
    if (root == nullptr)
    {
       return nullptr; 
    }
    Queue q;
    q.push(root);
    while(!q.empty())
    {
        BiTree current = q.pop();
        if (current->lchild != nullptr)
        {
            if (current->lchild->data == target)
            {
                printf("%c",current->lchild->data);
                return current;
            }
            q.push(current->lchild);
        }
        if (current->rchild)
        {
            if (current->rchild->data == target)
            {
                printf("%c",current->rchild->data);
                return current;
            }
            q.push(current->rchild);
        } 
    }
}

BiTree findSibling(BiTree root, char target)
{
    if (root == nullptr)
        return nullptr;
    // 如果左子节点和右子节点都存在
    if (root->lchild && root->rchild)
    {
        if (root->lchild->data == target)
            return root->rchild;
        if (root->rchild->data == target)
            return root->lchild;
    }
    // 在左子树中查找
    BiTree sibling = findSibling(root->lchild, target);
    if (sibling)
        return sibling;
    // 在右子树中查找
    return findSibling(root->rchild, target);
}

void deleteSubTree(BiTree node) {
    if (node == nullptr) return;
    deleteSubTree(node->lchild);
    deleteSubTree(node->rchild);
    delete node;
}

void deleteNode(BiTree root, char target)
{
    if (root == nullptr) return;

    // 检查左子节点
    if (root->lchild != nullptr && root->lchild->data == target) {
        deleteSubTree(root->lchild);  // 删除整个子树
        root->lchild = nullptr;
    } else {
        deleteNode(root->lchild, target);  // 递归检查左子树
    }

    // 检查右子节点
    if (root->rchild != nullptr && root->rchild->data == target) {
        deleteSubTree(root->rchild);  // 删除整个子树
        root->rchild = nullptr;
    } else {
        deleteNode(root->rchild, target);  // 递归检查右子树
    }
}

int main() {
    char str[101];
    char p;
    char q;
    cin >> str;
    cin >> p;
    cin >> q;
    
    index1 = 0; // 重置 index1
    BiTree root = preCreate(str);
    
    cout << "In-order traversal: ";
    inOrder(root);
    BiTree father = findParent(root, p);
    if (father != nullptr) {
        cout << "Parent of " << p << ": " << father->data << endl;
    } else {
        cout << "Parent not found for " << p << endl;
    }
    
    BiTree bro = findSibling(root, p);
    if (bro != nullptr) {
        cout << "Sibling of " << q << ": " << bro->data << endl;
    } else {
        cout << "Sibling not found for " << q << endl;
    }

    deleteNode(root, q);
    inOrder(root);
    cin.get();
    return 0;
}

