#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid1, int mid2, int right) {
    int len1 = mid1 - left + 1;
    int len2 = mid2 - mid1;
    int len3 = right - mid2;

    int L[len1], M[len2], R[len3];

    for (int i = 0; i < len1; i++) L[i] = arr[left + i];
    for (int i = 0; i < len2; i++) M[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < len3; i++) R[i] = arr[mid2 + 1 + i];

    int i = 0, j = 0, k = 0;
    int idx = left;

    while (i < len1 && j < len2 && k < len3) {
        if (L[i] <= M[j] && L[i] <= R[k]) {
            arr[idx++] = L[i++];
        } else if (M[j] <= L[i] && M[j] <= R[k]) {
            arr[idx++] = M[j++];
        } else {
            arr[idx++] = R[k++];
        }
    }

    while (i < len1) arr[idx++] = L[i++];
    while (j < len2) arr[idx++] = M[j++];
    while (k < len3) arr[idx++] = R[k++];
}

void threeWayMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = left + 2 * (right - left) / 3;

        threeWayMergeSort(arr, left, mid1);
        threeWayMergeSort(arr, mid1 + 1, mid2);
        threeWayMergeSort(arr, mid2 + 1, right);

        merge(arr, left, mid1, mid2, right);
    }
}

void printArrayToFile(int arr[], int size, FILE* file) {
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\n");
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    int n;
    printf("enter length of array:");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }
    fclose(inputFile);

    threeWayMergeSort(arr, 0, n - 1);

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    printArrayToFile(arr, n, outputFile);

    fclose(outputFile);

    return 0;
}
