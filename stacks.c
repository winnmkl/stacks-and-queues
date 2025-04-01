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
    Node* top;
} Stack;

void initializeStack(Stack* stack) {
    stack->top = NULL;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, int dataType, void* value) {
    system(CLEAR);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed in push!\n");
        return;
    }

    newNode->dataType = dataType;
    if (dataType == 1) { 
        newNode->data = malloc(sizeof(int));
        if (newNode->data == NULL) {
            printf("Memory allocation failed for number in push!\n");
            free(newNode);
            return;
        }
        memcpy(newNode->data, value, sizeof(int));
    } else if (dataType == 2) { 
        newNode->data = malloc(sizeof(char) * 100); 
        if (newNode->data == NULL) {
            printf("Memory allocation failed for string in push!\n");
            free(newNode);
            return;
        }
        strcpy((char*)newNode->data, (char*)value);
    } else {
        printf("Invalid data type in push!\n");
        free(newNode);
        return;
    }

    newNode->next = stack->top;
    stack->top = newNode;

    printf("Pushed.\n");
}

void pop(Stack* stack, void* value) {
    system(CLEAR);
    if (isEmpty(stack)) {
        printf("Stack is empty in pop!\n");
        return;
    }

    Node* popNode = stack->top;

    if (popNode->dataType == 1) { 
        memcpy(value, popNode->data, sizeof(int));
    } else if (popNode->dataType == 2) { 
        strcpy((char*)value, (char*)popNode->data);
    }

    stack->top = stack->top->next;
    free(popNode->data);
    free(popNode);

    printf("\nPopped.\n");
}

void traverseStack(Stack* stack) {
    system(CLEAR);
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }

    Node* travNode = stack->top;
    printf("Stack elements (top to bottom):\n");
    while (travNode != NULL) {
        if (travNode->dataType == 1) { 
            printf("%d\n", *(int*)travNode->data);
        } else if (travNode->dataType == 2) { 
            printf("%s\n", (char*)travNode->data);
        } else {
            printf("Unknown data type in traverseStack!\n");
        }
        travNode = travNode->next;
    }
    printf("\nTraversed all nodes.\n");
}

int main() {
    Stack stack;
    initializeStack(&stack);

    int choice, numValue, dataType;
    char strValue[100];

    do {
        system(CLEAR);
        printf("<@@ STACK OPERATIONS @@>\n\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Traverse\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data type (1: Integer, 2: String): ");
                scanf("%d", &dataType);
                if (dataType == 1) {
                    printf("Enter number: ");
                    scanf("%d", &numValue);
                    push(&stack, 1, &numValue);
                } else if (dataType == 2) {
                    printf("Enter string: ");
                    scanf(" %[^\n]", strValue);
                    push(&stack, 2, strValue);
                } else {
                    printf("Invalid data type!\n");
                }
                break;
            case 2:
                if (!isEmpty(&stack)) {
                    if (stack.top->dataType == 1) {
                        pop(&stack, &numValue);
                        printf("Popped: %d\n", numValue);
                    } else if (stack.top->dataType == 2) {
                        pop(&stack, strValue);
                        printf("\n\tPopped: %s\n", strValue);
                    }
                } else {
                    printf("Stack is empty!\n");
                }
                break;
            case 3:
                traverseStack(&stack);
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

    
    while (!isEmpty(&stack)) {
        Node* temp = stack.top;
        stack.top = stack.top->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}