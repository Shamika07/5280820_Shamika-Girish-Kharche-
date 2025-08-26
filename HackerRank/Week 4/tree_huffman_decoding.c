#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

// Define node structure (needed for local compilation)
// HackerRank already provides this in background
struct node {
    int freq;
    char data;
    struct node *left;
    struct node *right;
};

// Check if node is a leaf
bool isLeaf(struct node* root) {
    return (root->left == NULL && root->right == NULL);
}

// Decode function
void decode_huff(struct node *root, char *s) {
    struct node *curr = root;

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // If leaf node found
        if (isLeaf(curr)) {
            printf("%c", curr->data);
            curr = root;  // go back to root
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}