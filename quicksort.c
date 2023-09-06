#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Swap two elements in an array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition the array using the first element as the pivot
int partition_first(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (1) {
        while (i <= j && arr[i] <= pivot)
            i++;
        while (arr[j] >= pivot && j >= i)
            j--;

        if (j < i)
            break;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

// Partition the array using a random element as the pivot
int partition_random(int arr[], int low, int high) {
    srand(time(NULL));
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition_first(arr, low, high);
}

// Quicksort algorithm with different pivot choices
void quicksort(int arr[], int low, int high, char* pivot_choice) {
    if (low < high) {
        int pivot;
        if (strcmp(pivot_choice, "first") == 0)
            pivot = partition_first(arr, low, high);
        else if (strcmp(pivot_choice, "random") == 0)
            pivot = partition_random(arr, low, high);

        quicksort(arr, low, pivot - 1, pivot_choice);
        quicksort(arr, pivot + 1, high, pivot_choice);
    }
}

int main() {
    // Input and output file names
    const char* input_file_name = "input.txt";
    const char* output_file_name = "output.txt";

    // Open the input file for reading
    FILE* input_file = fopen(input_file_name, "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    // Read the input array size from the file
    int n;
    fscanf(input_file, "%d", &n);

    int arr[n];

    // Read the array elements from the file
    for (int i = 0; i < n; i++) {
        fscanf(input_file, "%d", &arr[i]);
    }

    fclose(input_file);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char* pivot_choice = "first"; // Choose "first" or "random" as the pivot choice

    quicksort(arr, 0, n - 1, pivot_choice);

    // Open the output file for writing
    FILE* output_file = fopen(output_file_name, "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }

    // Write the sorted array to the output file
    fprintf(output_file, "Sorted array (using %s pivot): ", pivot_choice);
    for (int i = 0; i < n; i++) {
        fprintf(output_file, "%d ", arr[i]);
    }
    fprintf(output_file, "\n");

    fclose(output_file);

    return 0;
}
