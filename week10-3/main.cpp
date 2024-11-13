#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
char str[370];

struct HuffmanNode
{
    char value;
    int freq;//权重
    HuffmanNode* left;
    HuffmanNode* right;
};
void caluate(char str[], HuffmanNode Tree[])
{
    int len = strlen(str);
    int cal[26];
    memset(cal, 0, sizeof(cal));
    for (size_t i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
        cal[str[i] - 'a']++;
    }
    int index = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != '0')
        {
            Tree[index].value = str[i];
            Tree[index].freq = cal[str[i] - 'a'];
        }
        index++;
    }
    
}
int main()
{
    cin >> str;
    HuffmanNode Tree[368];
    caluate(str, Tree);
    
    
    system("pause");
    return 0;
}
