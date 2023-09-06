#include <stdio.h>
#include <stdlib.h>
typedef struct {
        int val;
        int list_index;
        int element_index;
    } HeapNode;

// Function to merge k-sorted lists
int* merge_k_sorted_lists(int** lists, int k, int* sizes, int* merged_size) {
    // Initialize an array to store the merged result
    int* merged_result = NULL;
    *merged_size = 0;

    // Create a min-heap to keep track of the smallest element from each list
    
    HeapNode* min_heap = (HeapNode*)malloc(k * sizeof(HeapNode));
    if (!min_heap) {
        return NULL; // Memory allocation error
    }

    // Initialize the min-heap with the first element from each list along with its list index
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            min_heap[*merged_size].val = lists[i][0];
            min_heap[*merged_size].list_index = i;
            min_heap[*merged_size].element_index = 0;
            (*merged_size)++;
        }
    }

    // Build the min-heap
    for (int i = (*merged_size) / 2 - 1; i >= 0; i--) {
        min_heapify(min_heap, i, *merged_size);
    }

    // Merge the lists
    merged_result = (int*)malloc((*merged_size) * sizeof(int));
    if (!merged_result) {
        free(min_heap);
        return NULL; // Memory allocation error
    }

    int index = 0;

    while (*merged_size > 0) {
        // Get the smallest element and its list index
        int val = min_heap[0].val;
        int list_index = min_heap[0].list_index;
        int element_index = min_heap[0].element_index;

        // Append the smallest element to the merged result
        merged_result[index++] = val;

        // Move to the next element in the list from which the smallest element was taken
        if (element_index + 1 < sizes[list_index]) {
            min_heap[0].val = lists[list_index][element_index + 1];
            min_heap[0].element_index = element_index + 1;
        } else {
            // If the list is exhausted, replace it with the last element in the min-heap
            min_heap[0] = min_heap[*merged_size - 1];
            (*merged_size)--;
        }

        // Heapify to maintain the min-heap property
        min_heapify(min_heap, 0, *merged_size);
    }

    free(min_heap);
    return merged_result;
}

// Function to perform heapify operation on a min-heap
void min_heapify(HeapNode* arr, int i, int n) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].val < arr[smallest].val) {
        smallest = left;
    }

    if (right < n && arr[right].val < arr[smallest].val) {
        smallest = right;
    }

    if (smallest != i) {
        // Swap arr[i] and arr[smallest]
        HeapNode temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        // Recursively heapify the affected subtree
        min_heapify(arr, smallest, n);
    }
}

int main() {
    // Input and output file names
    const char* input_file_name = "input.txt";
    const char* output_file_name = "output.txt";

    // Read input data from the input file
    FILE* input_file = fopen(input_file_name, "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    int k;
    fscanf(input_file, "%d", &k);
    int** k_sorted_lists = (int**)malloc(k * sizeof(int*));
    int* sizes = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        fscanf(input_file, "%d", &sizes[i]);
        k_sorted_lists[i] = (int*)malloc(sizes[i] * sizeof(int));
        for (int j = 0; j < sizes[i]; j++) {
            fscanf(input_file, "%d", &k_sorted_lists[i][j]);
        }
    }

    fclose(input_file);

    // Merge the k-sorted lists
    int merged_size;
    int* merged_list = merge_k_sorted_lists(k_sorted_lists, k, sizes, &merged_size);

    // Write the merged result to the output file
    FILE* output_file = fopen(output_file_name, "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(output_file, "%d\n", merged_size);
    for (int i = 0; i < merged_size; i++) {
        fprintf(output_file, "%d ", merged_list[i]);
    }

    fclose(output_file);

    // Free allocated memory
    for (int i = 0; i < k; i++) {
        free(k_sorted_lists[i]);
    }
    free(k_sorted_lists);
    free(sizes);
    free(merged_list);

    return 0;
}
