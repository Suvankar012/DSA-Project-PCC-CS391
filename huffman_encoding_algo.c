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

