#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct HuffmanNode
{
    char value;
    int freq; // 权重
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

void insertMinHeap(HuffmanNode* heap[], int& size, HuffmanNode* node)
{
    heap[size] = node;
    int i = size;
    while (i > 0 && heap[(i - 1) / 2]->freq > heap[i]->freq)
    {
        swap(heap[(i - 1) / 2], heap[i]);
        i = (i - 1) / 2;
    }
    size++;
}

HuffmanNode* extractMin(HuffmanNode* heap[], int& size)
{
    HuffmanNode* minNode = heap[0];
    heap[0] = heap[size - 1];
    size--;
    int i = 0;
    while (2 * i + 1 < size)
    {
        int smallest = i;
        if (heap[2 * i + 1]->freq < heap[smallest]->freq)
            smallest = 2 * i + 1;
        if (2 * i + 2 < size && heap[2 * i + 2]->freq < heap[smallest]->freq)
            smallest = 2 * i + 2;
        if (smallest == i)
            break;
        swap(heap[i], heap[smallest]);
        i = smallest;
    }
    return minNode;
}

HuffmanNode* buildHuffmanTree(char str[])
{
    int freq[26];
    calculateFrequency(str, freq);

    HuffmanNode* heap[26];
    int size = 0;

    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            HuffmanNode* node = new HuffmanNode();
            node->value = 'a' + i;
            node->freq = freq[i];
            node->left = node->right = nullptr;
            insertMinHeap(heap, size, node);
        }
    }

    while (size > 1)
    {
        HuffmanNode* left = extractMin(heap, size);
        HuffmanNode* right = extractMin(heap, size);

        HuffmanNode* newNode = new HuffmanNode();
        newNode->value = '\0';
        newNode->freq = left->freq + right->freq;
        newNode->left = left;
        newNode->right = right;
        insertMinHeap(heap, size, newNode);
    }

    return heap[0];
}

void generateCodes(HuffmanNode* root, string str, string codes[])
{
    if (!root)
        return;

    if (root->value != '\0')
    {
        codes[root->value - 'a'] = str;
    }

    generateCodes(root->left, str + "0", codes);
    generateCodes(root->right, str + "1", codes);
}

string encodeString(char str[], string codes[])
{
    string encodedStr = "";
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        encodedStr += codes[tolower(str[i]) - 'a'];
    }
    return encodedStr;
}

int main()
{
    char str[370];
    cin >> str;

    HuffmanNode* root = buildHuffmanTree(str);

    string codes[26];
    generateCodes(root, "", codes);

    string encodedStr = encodeString(str, codes);

    cout << "Encoded String: " << encodedStr << endl;

    return 0;
}