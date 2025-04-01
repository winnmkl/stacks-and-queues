#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct Node {
    int dataType;
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, int dataType, void* value) {
    system(CLEAR);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed in enqueue!\n");
        return;
    }

    newNode->dataType = dataType;
    if (dataType == 1) { 
        newNode->data = malloc(sizeof(int));
        if (newNode->data == NULL) {
            printf("Memory allocation failed for number in enqueue!\n");
            free(newNode);
            return;
        }
        memcpy(newNode->data, value, sizeof(int));
    } else if (dataType == 2) { 
        newNode->data = malloc(sizeof(char) * 100); 
        if (newNode->data == NULL) {
            printf("Memory allocation failed for string in enqueue!\n");
            free(newNode);
            return;
        }
        strcpy((char*)newNode->data, (char*)value);
    } else {
        printf("Invalid data type in enqueue!\n");
        free(newNode);
        return;
    }

    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    printf("Enqueued.\n");
}

void dequeue(Queue* queue, void* value) {
    system(CLEAR);
    if (isEmpty(queue)) {
        printf("Queue is empty for dequeue!\n");
        return;
    }

    Node* delNode = queue->front;

    if (delNode->dataType == 1) { 
        memcpy(value, delNode->data, sizeof(int));
    } else if (delNode->dataType == 2) { 
        strcpy((char*)value, (char*)delNode->data);
    }

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(delNode->data);
    free(delNode);

    printf("Dequeued.\n");
}

void traverseQueue(Queue* queue) {
    system(CLEAR);
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    Node* travNode = queue->front;
    printf("Queue elements (front to rear):\n\n");
    while (travNode != NULL) {
        if (travNode->dataType == 1) {
            printf("%d\n", *(int*)travNode->data);
        } else if (travNode->dataType == 2) { 
            printf("%s\n", (char*)travNode->data);
        } else {
            printf("Unknown data type in traverseQueue!\n");
        }
        travNode = travNode->next;
    }
    printf("\n\tTraversed.\n");
}

int main() {
    Queue queue;
    initializeQueue(&queue);

    int choice, numValue, dataType;
    char strValue[100];

    do {
        system(CLEAR);
        printf("<@@QUEUE OPERATIONS@@>\n\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Traverse\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data type (1: Number, 2: String): ");
                scanf("%d", &dataType);
                if (dataType == 1) {
                    printf("Enter number: ");
                    scanf("%d", &numValue);
                    enqueue(&queue, 1, &numValue);
                } else if (dataType == 2) {
                    printf("Enter string: ");
                    scanf(" %[^\n]", strValue);
                    enqueue(&queue, 2, strValue);
                } else {
                    printf("Invalid data type!\n");
                }
                break;
            case 2:
                if (!isEmpty(&queue)) {
                    if (queue.front->dataType == 1) {
                        dequeue(&queue, &numValue);
                        printf("Dequeued: %d\n", numValue);
                    } else if (queue.front->dataType == 2) {
                        dequeue(&queue, strValue);
                        printf("Dequeued: %s\n", strValue);
                    }
                } else {
                    printf("Queue is empty!\n");
                }
                break;
            case 3:
                traverseQueue(&queue);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
        printf("\n");
        if (choice != 0) {
            printf("Press Enter to continue...");
            getchar();
            getchar();
        }

    } while (choice != 0);

    while (!isEmpty(&queue)) {
        Node* temp = queue.front;
        queue.front = queue.front->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}