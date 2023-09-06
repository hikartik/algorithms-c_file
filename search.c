#include <stdio.h>

// Function prototypes
void insertionsort(int arr[],int len){
    int i,j,key;
    for(i=1;i<len;i++){
        key=arr[i];
        j=i-1;
        while(arr[j]>key && j>=0){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;

    }    
}
int lsearch(int arr[], int len, int num);
int bsearch(int arr[], int low, int high, int n);
int tsearch(int *array, int low, int high, int key);

int main() {
    FILE *file;
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Not able to load input.txt\n");
        return 1;
    }

    int len;
    printf("Enter number of elements to be entered in array: ");
    scanf("%d", &len);

    int arr[len];
    for (int i = 0; i < len; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    int choice, ele,result;
    printf("Enter choice of searching:\n1 - Linear Search\n2 - Binary Search\n3 - Ternary Search\n");
    scanf("%d", &choice);

    printf("Enter element to be searched: ");
    scanf("%d", &ele);

    switch (choice) {
        case 1: {
            // Call the lsearch function
            result = lsearch(arr, len, ele);
            if (result != -1) {
                printf("Element found at index: %d\n", result);
            } else {
                printf("Element not found.\n");
            }
            break;
        }
        case 2: {
            // Call the bsearch function
            insertionsort(arr, len);
            result = bsearch(arr, 0, len - 1, ele);
            if (result != -1) {
                printf("Element found at index: %d\n", result);
            }
            else {
                printf("Element not found.\n");
            }
            break;
        }
        case 3: {
            insertionsort(arr, len);
            // Call the tsearch function
            result = tsearch(arr, 0, len - 1, ele);
            if (result != -1) {
                printf("Element found at index: %d\n", result);
            }
            else {
                printf("Element not found.\n");
            }
            break;
        }
        default: {
            printf("\nInvalid choice: Exiting without search\n");
        }
    }


    // Write the modified array to the output file
    file = fopen("output.txt", "w+");
  fprintf(file,"%d ",result);
    fclose(file);

    return 0;
}

// Implement the search functions lsearch, bsearch, and tsearch here...

int lsearch(int arr[],int len,int num){
    int i=0;
    for(i=0;i<len;i++){
        if(arr[i]==num) return i;
    }
    return -1;
}
int bsearch(int arr[], int low, int high, int n) {
    if (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == n) {
            return mid;
        }
        else if (arr[mid] < n) {
            return bsearch(arr, mid + 1, high, n);
        }
        else {
            return bsearch(arr, low, mid - 1, n);
        }
    }
    return -1;
}

int tsearch(int array[], int low, int high, int key) {
    if (high >= low) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if (array[mid1] == key) {
            return mid1;
        }
        if (array[mid2] == key) {
            return mid2;
        }

        if (key < array[mid1]) {
            return tsearch(array, low, mid1 - 1, key);
        } else if (key > array[mid2]) {
            return tsearch(array, mid2 + 1, high, key);
        } else {
            return tsearch(array, mid1 + 1, mid2 - 1, key);
        }
    }
    return -1;
}
