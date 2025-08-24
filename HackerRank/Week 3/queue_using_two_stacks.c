#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 100000  // big enough for queries

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Initialize stack
void init(Stack* s) {
    s->top = -1;
}

// Check if empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Push
void push(Stack* s, int val) {
    s->arr[++s->top] = val;
}

// Pop
int pop(Stack* s) {
    return s->arr[s->top--];
}

// Peek
int peek(Stack* s) {
    return s->arr[s->top];
}

// Queue using two stacks
Stack stack_in, stack_out;

void enqueue(int x) {
    push(&stack_in, x);
}

void shiftStacks() {
    if (isEmpty(&stack_out)) {
        while (!isEmpty(&stack_in)) {
            push(&stack_out, pop(&stack_in));
        }
    }
}

void dequeue() {
    shiftStacks();
    if (!isEmpty(&stack_out)) {
        pop(&stack_out);
    }
}

void printFront() {
    shiftStacks();
    if (!isEmpty(&stack_out)) {
        printf("%d\n", peek(&stack_out));
    }
}

int main() {
    init(&stack_in);
    init(&stack_out);

    int q;
    scanf("%d", &q);  // number of queries

    for (int i = 0; i < q; i++) {
        int type, x;
        scanf("%d", &type);

        if (type == 1) {   // enqueue
            scanf("%d", &x);
            enqueue(x);
        } 
        else if (type == 2) {  // dequeue
            dequeue();
        } 
        else if (type == 3) {  // print front
            printFront();
        }
    }

    return 0;
}
