#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid_number(const char *input);
int input_number();
int* allocate_and_input_array(int *size);
int calculate_sum(int *arr, int size);
void calculate_min_max(int *arr, int size, int *min, int *max);
void calculate_even_odd(int *arr, int size, int *evenCount, int *oddCount);
void sort_array(int *arr, int size);
void print_results(int sum, float avg, int min, int max, int evenCount, int oddCount, int *sortedArr, int size);

int main() {
    int n;
    int *numbers = allocate_and_input_array(&n);
    int sum = calculate_sum(numbers, n);
    float avg = (float)sum / n;
    int min, max;
    calculate_min_max(numbers, n, &min, &max);
    int evenCount, oddCount;
    calculate_even_odd(numbers, n, &evenCount, &oddCount);
    sort_array(numbers, n);
    print_results(sum, avg, min, max, evenCount, oddCount, numbers, n);
    free(numbers);
    return 0;
}

int is_valid_number(const char *input) {
    int i = 0;
    if (input[0] == '-') {
        i = 1;
    }
    for (; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0;
        }
    }
    if (i == 0 || (i == 1 && input[0] == '-')) {
        return 0;
    }
    return 1;
}

int input_number() {
    char *input = NULL;
    size_t size = 0;
    while (1) {
        printf("Enter a number: ");
        getline(&input, &size, stdin);
        input[strcspn(input, "\n")] = '\0';
        if (is_valid_number(input)) {
            int number = atoi(input);
            free(input);
            return number;
        } else {
            printf("Invalid input. Please enter a valid number.\n");
        }
    }
}

int* allocate_and_input_array(int *size) {
    printf("Enter the number of elements: ");
    *size = input_number();
    int *arr = (int *)malloc((*size) * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    printf("Enter the numbers:\n");
    for (int i = 0; i < *size; i++) {
        printf("Number %d: ", i + 1);
        arr[i] = input_number();
    }
    return arr;
}

int calculate_sum(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

void calculate_min_max(int *arr, int size, int *min, int *max) {
    *min = *max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

void calculate_even_odd(int *arr, int size, int *evenCount, int *oddCount) {
    *evenCount = *oddCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            (*evenCount)++;
        } else {
            (*oddCount)++;
        }
    }
}

void sort_array(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_results(int sum, float avg, int min, int max, int evenCount, int oddCount, int *sortedArr, int size) {
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", avg);
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
    printf("Even numbers: %d\n", evenCount);
    printf("Odd numbers: %d\n", oddCount);
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", sortedArr[i]);
    }
    printf("\n");
}