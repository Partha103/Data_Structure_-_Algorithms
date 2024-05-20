#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 5000
#define MAX_CODE_LENGTH 100

struct HuffmanNode
{
    int demand;
    int freq;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
};

struct PriorityQueueNode
{
    struct HuffmanNode *data;
    struct PriorityQueueNode *next;
};

struct PriorityQueue
{
    struct PriorityQueueNode *front;
};

void initPriorityQueue(struct PriorityQueue *pq)
{
    pq->front = NULL;
}

int isPQEmpty(struct PriorityQueue *pq)
{
    return (pq->front == NULL);
}

void insertPQ(struct PriorityQueue *pq, struct HuffmanNode *node)
{
    struct PriorityQueueNode *newNode = (struct PriorityQueueNode *)malloc(sizeof(struct PriorityQueueNode));
    newNode->data = node;
    newNode->next = NULL;

    if (pq->front == NULL || node->freq < pq->front->data->freq)
    {
        newNode->next = pq->front;
        pq->front = newNode;
    }
    else
    {
        struct PriorityQueueNode *current = pq->front;
        while (current->next != NULL && current->next->data->freq <= node->freq)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

struct HuffmanNode *removePQ(struct PriorityQueue *pq)
{
    if (isPQEmpty(pq))
    {
        printf("Priority Queue is empty\n");
        exit(1);
    }
    struct PriorityQueueNode *temp = pq->front;
    struct HuffmanNode *data = temp->data;
    pq->front = pq->front->next;
    free(temp);
    return data;
}

struct HuffmanNode *buildHuffmanTree(int demands[], int frequencies[], int num_symbols)
{
    struct PriorityQueue pq;
    initPriorityQueue(&pq);

    int freqTable[MAX_SYMBOLS] = {0};
    for (int i = 0; i < num_symbols; i++)
    {
        freqTable[demands[i]] += frequencies[i];
    }

    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        if (freqTable[i] > 0)
        {
            struct HuffmanNode *node = (struct HuffmanNode *)malloc(sizeof(struct HuffmanNode));
            node->demand = i;
            node->freq = freqTable[i];
            node->left = NULL;
            node->right = NULL;
            insertPQ(&pq, node);
        }
    }

    while (pq.front->next != NULL)
    {
        struct HuffmanNode *x = removePQ(&pq);
        struct HuffmanNode *y = removePQ(&pq);

        struct HuffmanNode *z = (struct HuffmanNode *)malloc(sizeof(struct HuffmanNode));
        z->demand = -1;
        z->freq = x->freq + y->freq;
        z->left = x;
        z->right = y;

        insertPQ(&pq, z);
    }

    return pq.front->data;
}

void generateHuffmanCodes(struct HuffmanNode *root, char code[], int index, int demand, FILE *outputFile)
{
    if (root == NULL)
        return;

    if (root->demand == demand)
    {
        code[index] = '\0';
        fprintf(outputFile, "%d:\t%s\n", demand, code);
    }
    else
    {
        code[index] = '0';
        generateHuffmanCodes(root->left, code, index + 1, demand, outputFile);

        code[index] = '1';
        generateHuffmanCodes(root->right, code, index + 1, demand, outputFile);
    }
}
int countDigits(int number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int demands[MAX_SYMBOLS];
    int frequencies[MAX_SYMBOLS];
    int num_symbols = 0;

    while (fscanf(file, "%d", &demands[num_symbols]) != EOF)
    {
        fscanf(file, "%d", &frequencies[num_symbols]);
        num_symbols++;
    }

    fclose(file);

    for (int i = 0; i < num_symbols; i++)
    {
        demands[i] = (demands[i] / 10) * 10;
        if (demands[i] != demands[i] / 10 * 10)
            ;
        demands[i] += 10;
    }

    int unique_demands[MAX_SYMBOLS];
    int unique_frequencies[MAX_SYMBOLS];
    int unique_num_symbols = 0;

    for (int i = 0; i < num_symbols; i++)
    {
        int j;
        for (j = 0; j < unique_num_symbols; j++)
        {
            if (unique_demands[j] == demands[i])
            {
                unique_frequencies[j] += frequencies[i];
                break;
            }
        }
        if (j == unique_num_symbols)
        {
            unique_demands[unique_num_symbols] = demands[i];
            unique_frequencies[unique_num_symbols] = frequencies[i];
            unique_num_symbols++;
        }
    }

    struct HuffmanNode *root = buildHuffmanTree(unique_demands, unique_frequencies, unique_num_symbols);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error opening output file.\n");
        return 1;
    }

    int originalSize = 0;
    for (int i = 0; i < num_symbols; i++)
    {
        int numDigits = countDigits(demands[i]);
        originalSize += numDigits * frequencies[i];
    }
    int compressedSize = 0;
    char code[MAX_CODE_LENGTH] = "";

    for (int i = 0; i < unique_num_symbols; i++)
    {
        code[0] = '\0';
        generateHuffmanCodes(root, code, 0, unique_demands[i], outputFile);
        compressedSize += strlen(code) * unique_frequencies[i] / 8;
    }

    fclose(outputFile);

    printf("Original message size: %d bytes\n", originalSize);
    printf("Compressed message size: %d bytes\n", compressedSize);

    double compressionRatio = (double)originalSize / compressedSize;
    printf("Compression ratio: %.2f\n", compressionRatio);

    return 0;
}