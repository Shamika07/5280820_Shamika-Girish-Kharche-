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

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* isValid(char* s) {
 int freq[26] = {0};
    int n = strlen(s);

    // Count frequency of each character
    for (int i = 0; i < n; i++) {
        freq[s[i] - 'a']++;
    }

    // Collect non-zero frequencies
    int counts[26], k = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            counts[k++] = freq[i];
        }
    }

    // Find distinct frequencies
    int min = counts[0], max = counts[0];
    for (int i = 1; i < k; i++) {
        if (counts[i] < min) min = counts[i];
        if (counts[i] > max) max = counts[i];
    }

    // Case 1: all equal
    if (min == max) return "YES";

    // Count how many have min and max
    int minCount = 0, maxCount = 0;
    for (int i = 0; i < k; i++) {
        if (counts[i] == min) minCount++;
        if (counts[i] == max) maxCount++;
    }

    // Case 2: one char has freq 1, rest are max
    if (min == 1 && minCount == 1 && maxCount == k - 1) return "YES";

    // Case 3: one char has freq (max = min+1)
    if (max == min + 1 && maxCount == 1) return "YES";

    return "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

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

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}
