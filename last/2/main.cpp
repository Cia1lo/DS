#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef struct Node
{
    int x, y;
    Node* next;
}Node;
    
class Stack
{
private:
    Node* top; 
    int size;

public:
    void push(int x, int y)
    {
        Node* newNode = new Node;
        newNode->x = x;
        newNode->y = y;
        newNode->next = top;
        top = newNode;
        size++;
    }    

    pair<int, int> pop()
    {
        if (top == nullptr) {
            return {-1, -1}; // 返回一个无效的节点，表示栈为空
        }
        Node* temp = top;
        int x = temp->x;
        int y = temp->y;
        top = top->next;
        delete temp;
        size--;
        return {x, y};
    }

    int returnSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    Stack()
    {
        top = NULL;
        size = 0;
    }
};

vector<vector<char>> CreatMaze()
{
    vector<vector<char>> maze;
    string line;
    ifstream file("E:\\C_CODE\\DS\\last\\2\\maze.txt");
    while (getline(file, line))
    {
        vector<char> row(line.begin(), line.end());
        maze.push_back(row);
    }
    file.close();
    return maze;
}

bool isValid(vector<vector<char>> maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == '.';
}

Stack path;

bool DFS(vector<vector<char>> maze, int startX, int startY, int endX, int endY, vector<vector<bool>> &Visited)
{
    if (startX == endX && startY == endY)
    {
        path.push(startX, startY);
        return true;
    }

    Visited[startX][startY] = true;
    
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < 4; ++i)
    {
        int newX = startX + directions[i][0];
        int newY = startY + directions[i][1];
        
        if (isValid(maze, newX, newY) && !Visited[newX][newY])  // 如果新位置有效且未访问过
        {
            if (DFS(maze, newX, newY, endX, endY, Visited))  // 递归搜索
            {
                path.push(startX, startY);  // 只有当找到目标时才将节点加入路径
                return true;  // 找到路径后返回
            }
        }
    }

    return false;
}

int main()
{
    vector<vector<char>> maze = CreatMaze();
    vector<vector<bool>> Visited(maze.size(), vector<bool>(maze[0].size(), false));

    int startX, startY, endX, endY;
    cin >> startX >> startY >> endX >> endY;
    if (DFS(maze, startX, startY, endX, endY, Visited)) {
        // 打印路径
        while (!path.isEmpty()) {
            pair<int, int> temp = path.pop();
            cout << "Visiting: (" << temp.first << ", " << temp.second << ")" << endl;
        }
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}