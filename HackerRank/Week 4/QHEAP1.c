#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAXN 100000

int arr[MAXN];
int size = 0;

// insert element into sorted array
void insert(int x) {
    int pos = size;
    while (pos > 0 && arr[pos-1] > x) {
        arr[pos] = arr[pos-1];
        pos--;
    }
    arr[pos] = x;
    size++;
}

// delete element from sorted array
void deleteVal(int x) {
    int i = 0;
    while (i < size && arr[i] != x) i++;
    if (i < size) {
        for (int j = i; j < size-1; j++) arr[j] = arr[j+1];
        size--;
    }
}

// get minimum (first element)
int getMin() {
    return arr[0];
}

int main() {
    int q;
    scanf("%d", &q);

    while (q--) {
        int type, val;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &val);
            insert(val);
        } else if (type == 2) {
            scanf("%d", &val);
            deleteVal(val);
        } else if (type == 3) {
            printf("%d\n", getMin());
        }
    }

    return 0;
}
