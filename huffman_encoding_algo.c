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

