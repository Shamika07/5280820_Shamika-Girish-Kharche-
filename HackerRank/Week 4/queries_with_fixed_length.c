#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

/*
 * Complete the 'solve' function below.
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */

int* solve(int arr_count, int* arr, int queries_count, int* queries, int* result_count) {
    int *left = malloc(arr_count * sizeof(int));
    int *right = malloc(arr_count * sizeof(int));
    int *stack = malloc(arr_count * sizeof(int));
    int top;

    // Initialize nearest greater boundaries
    for (int i = 0; i < arr_count; i++) {
        left[i] = -1;
        right[i] = arr_count;
    }

    // Previous greater (use <= to handle duplicates)
    top = -1;
    for (int i = 0; i < arr_count; i++) {
        while (top >= 0 && arr[stack[top]] <= arr[i]) top--;
        if (top >= 0) left[i] = stack[top];
        stack[++top] = i;
    }

    // Next greater (use < to handle duplicates)
    top = -1;
    for (int i = arr_count - 1; i >= 0; i--) {
        while (top >= 0 && arr[stack[top]] < arr[i]) top--;
        if (top >= 0) right[i] = stack[top];
        stack[++top] = i;
    }

    // res[len] will hold the MIN possible maximum for window length = len
    int *res = malloc((arr_count + 1) * sizeof(int));
    for (int i = 0; i <= arr_count; i++) res[i] = INT_MAX;

    for (int i = 0; i < arr_count; i++) {
        int len = right[i] - left[i] - 1;  // max window where arr[i] can be the maximum
        if (arr[i] < res[len]) res[len] = arr[i];
    }

    // Propagate: for smaller lengths, the answer cannot be greater than for larger lengths
    for (int len = arr_count - 1; len >= 1; len--) {
        if (res[len] > res[len + 1]) res[len] = res[len + 1];
    }

    // Answer queries
    *result_count = queries_count;
    int *answers = malloc(queries_count * sizeof(int));
    for (int i = 0; i < queries_count; i++) {
        int len = queries[i];
        if (len < 1) len = 1;
        if (len > arr_count) len = arr_count;
        answers[i] = res[len];
    }

    free(left);
    free(right);
    free(stack);
    free(res);
    return answers;
}


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));

    char** arr_temp = split_string(rtrim(readline()));
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = parse_int(*(arr_temp + i));
    }

    int* queries = malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) {
        queries[i] = parse_int(ltrim(rtrim(readline())));
    }

    int result_count;
    int* result = solve(n, arr, q, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", result[i]);
        if (i != result_count - 1) fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
    }

    if (data[data_length - 1] == '\n') data[data_length - 1] = '\0';
    return data;
}

char* ltrim(char* str) {
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str || !*str) return str;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;
    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
