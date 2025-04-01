#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    size_t elementSize;
    int dataType;
} Stack;

void initializeStack(Stack* stack, size_t elementSize, int dataType) {
    stack->top = NULL;
    stack->elementSize = elementSize;
    stack->dataType = dataType;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, void* value) {
    system(CLEAR);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = malloc(stack->elementSize);
    if (newNode->data == NULL) {
        printf("Memory allocation failed!\n");
        free(newNode);
        return;
    }
    memcpy(newNode->data, value, stack->elementSize); 
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(Stack* stack, void* value) {
    system(CLEAR);
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }

    Node* popNode = stack->top;
    memcpy(value, popNode->data, stack->elementSize); 
    stack->top = stack->top->next;
    free(popNode->data);
    free(popNode);
}

void peek(Stack* stack, void* value) {
    system(CLEAR);
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    memcpy(value, stack->top->data, stack->elementSize); 
}

void traverseStack(Stack* stack) {
    system(CLEAR);
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }

    Node* travNode = stack->top;
    printf("Stack elements: ");
    while (travNode != NULL) {
        switch (stack->dataType) {
            case 1:
                printf("%d ", *(int*)travNode->data);
                break;
            case 2:
                printf("%f ", *(float*)travNode->data);
                break;
            case 3:
                printf("%c ", *(char*)travNode->data);
                break;
            case 4:
                printf("%s ", (char*)travNode->data);
                break;
            default:
                printf("Unknown data type.\n");
                return;
        }
        travNode = travNode->next;
    }
    printf("\n");
}

int main() {
    Stack stack;
    int dataType;

    printf("Enter the data type for the stack:\n");
    printf("1. Integer\n");
    printf("2. Float\n");
    printf("3. Character\n");
    printf("4. String\n");
    scanf("%d", &dataType);

    size_t elementSize;
    switch (dataType) {
        case 1:
            elementSize = sizeof(int);
            break;
        case 2:
            elementSize = sizeof(float);
            break;
        case 3:
            elementSize = sizeof(char);
            break;
        case 4:
            elementSize = sizeof(char) * 100;
            break;
        default:
            printf("Invalid data type.\n");
            return 1;
    }

    initializeStack(&stack, elementSize, dataType);

    int choice;
    do {
    	system ("cls");
        printf("STACKS and OPERATIONS\n\tPlease provide input for operation\n\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Traverse Stack\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                void* value = malloc(elementSize);
                if (value == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                switch (dataType) {
                    case 1:
                        printf("Enter integer value: ");
                        scanf("%d", (int*)value);
                        break;
                    case 2:
                        printf("Enter float value: ");
                        scanf("%f", (float*)value);
                        break;
                    case 3:
                        printf("Enter character value: ");
                        scanf(" %c", (char*)value);
                        break;
                    case 4:
                        printf("Enter string value: ");
                        scanf(" %[^\n]", (char*)value);
                        break;
                }
                push(&stack, value);
                free(value);
                break;
            }
            case 2: {
                void* value = malloc(elementSize);
                if (value == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                pop(&stack, value);
                switch (dataType) {
                    case 1:
                        printf("Popped value: %d\n", *(int*)value);
                        break;
                    case 2:
                        printf("Popped value: %f\n", *(float*)value);
                        break;
                    case 3:
                        printf("Popped value: %c\n", *(char*)value);
                        break;
                    case 4:
                        printf("Popped value: %s\n", (char*)value);
                        break;
                }
                free(value);
                break;
            }
            case 3: {
                void* value = malloc(elementSize);
                if (value == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                peek(&stack, value);
                switch (dataType) {
                    case 1:
                        printf("Top value: %d\n", *(int*)value);
                        break;
                    case 2:
                        printf("Top value: %f\n", *(float*)value);
                        break;
                    case 3:
                        printf("Top value: %c\n", *(char*)value);
                        break;
                    case 4:
                        printf("Top value: %s\n", (char*)value);
                        break;
                }
                free(value);
                break;
            }
            case 4:
                traverseStack(&stack);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    while (stack.top != NULL) {
        Node* temp = stack.top;
        stack.top = stack.top->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}