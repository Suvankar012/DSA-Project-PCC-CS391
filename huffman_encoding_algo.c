#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 250

typedef struct MinHeapNode{
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
}node;

typedef struct MinHeap{
    unsigned size;
    unsigned capacity;
    node** array;
}MinHeap;

node* newNode(char data, unsigned freq){
    node* temp = (node*)malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* createMinHeap(unsigned capacity){
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (node**)malloc(minHeap->capacity * sizeof(node*));
    return minHeap;
}

void swapMinHeapNode(node** a, node** b){
    node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < (int)minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(MinHeap* minHeap){
    return (minHeap->size == 1);
}

node* extractMin(MinHeap* minHeap){
    node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, node* minHeapNode){
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq){
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap){
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(minHeap, i);
}

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size){
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
node* buildHuffmanTree(char data[], int freq[], int size){
    node *left, *right, *top;

    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)){
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(node* root, int arr[], int top){
    if (root->left){
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right){
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)){
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}
void decodeString(node* root, char* encodedStr){
    node* current = root;
    printf("\nDecoded string: ");
    for (int i = 0; encodedStr[i] != '\0'; i++){
        if (encodedStr[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right){
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

void HuffmanCodes(char data[], int freq[], int size){
    node* root = buildHuffmanTree(data, freq, size);
    int arr[MAX], top = 0;

    printf("\nHuffman Codes:\n");
    printCodes(root, arr, top);

    char encodedStr[100];
    printf("\nEnter encoded string (e.g.- 010011...): ");
    scanf("%s", encodedStr);

    decodeString(root, encodedStr);
}


int main() {
    int n;
    printf("Enter number of unique characters: ");
    scanf("%d", &n);

    char data[n];
    int freq[n];

    printf("Enter characters:\n");
    for (int i = 0; i < n; i++)
        scanf(" %c", &data[i]);

    printf("Enter frequencies of respective characters:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    HuffmanCodes(data, freq, n);
    return 0;
}

