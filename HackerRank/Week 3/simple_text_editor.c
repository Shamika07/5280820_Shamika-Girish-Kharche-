#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000000   // enough buffer for strings

// Stack structure for undo operations
typedef struct {
    int type;   // 1 for append, 2 for delete
    char *data; // stores string added or deleted
} Operation;

Operation history[MAX];
int top = -1;

// push operation into history
void push(int type, const char* data) {
    history[++top].type = type;
    history[top].data = strdup(data);
}

// pop operation from history
Operation pop() {
    return history[top--];
}

int main() {
    int Q;
    scanf("%d", &Q);

    char S[MAX] = "";  // our text buffer

    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {  // append
            char w[MAX];
            scanf("%s", w);
            strcat(S, w);
            push(1, w);   // record for undo
        } 
        else if (type == 2) {  // delete
            int k;
            scanf("%d", &k);
            int len = strlen(S);
            char deleted[MAX];
            strcpy(deleted, S + len - k); // substring being deleted
            S[len - k] = '\0';            // cut string
            push(2, deleted);             // record for undo
        } 
        else if (type == 3) {  // print
            int k;
            scanf("%d", &k);
            printf("%c\n", S[k - 1]);
        } 
        else if (type == 4) {  // undo
            Operation last = pop();
            if (last.type == 1) {
                // undo append
                int len = strlen(S);
                int k = strlen(last.data);
                S[len - k] = '\0';
            } else if (last.type == 2) {
                // undo delete
                strcat(S, last.data);
            }
            free(last.data);
        }
    }

    return 0;
}
