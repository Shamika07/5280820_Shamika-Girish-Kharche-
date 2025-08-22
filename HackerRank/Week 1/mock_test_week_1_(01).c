#include <stdio.h>
#include <stdlib.h> // For qsort
#include <string.h> // For memcpy if needed, though not directly used here

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to find the median
int findMedian(int arr[], int n) {
    // Sort the array
    qsort(arr, n, sizeof(int), compare);

    // The median is the middle element for an odd-sized array
    // The index of the middle element is (n / 2)
    return arr[n / 2];
}


// Example usage (main function for testing)
int main() {
    int n;

    // Read n (size of array)
    scanf("%d", &n);

    int arr; // Declare array based on n

    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int median = findMedian(arr, n);
    printf("%d\n", median);

    return 0;
}
