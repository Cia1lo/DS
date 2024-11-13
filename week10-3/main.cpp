#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
char str[370];
int index = 0;

struct HuffmanNode
{
    char value;
    int freq;//权重
    HuffmanNode* left;
    HuffmanNode* right;
};

void calculateFrequency(char str[], int freq[])
{
    int len = strlen(str);
    memset(freq, 0, sizeof(int) * 26);

    for (int i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
        freq[str[i] - 'a']++;
    }
}

int main()
{
    cin >> str;
    HuffmanNode Tree[368];
    
    
    
    system("pause");
    return 0;
}
