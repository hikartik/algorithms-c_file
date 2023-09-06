#include<stdio.h>
#include<stdlib.h>
void swap(int a,int b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}
void swap2(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void bubblesort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void selectionsort(int arr[],int len){
    int i,j,key;
    for(i=0;i<len;i++){
        key=i;
        for(j=i+1;j<len;j++){
            if(arr[j]<=arr[key]) key=j;
        }
        swap(arr[i],arr[key]);


    }
}
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
void merge(int arr[],int low,int high){
    int mid=(low+high)/2;
    int n1=mid-low+1;
    int n2=high-mid;
    int arr1[n1],arr2[n2];
     for(int i=0;i<n1;i++) arr1[i]=arr[i+low];
     for(int j=0;j<n2;j++) arr2[j]=arr[j+mid+1];
     int i=0,j=0,k=low;
     while(i<n1 && j<n2){
        if(arr1[i]<=arr2[j]){
            arr[k]=arr1[i];
            i++;
        }
        else{
            arr[k]=arr2[j];
            j++;
        }
        k++;

     }

     while(j<n2){
        arr[k]=arr2[j];
        k++;
        j++;
     }
     while(i<n1){
        arr[k]=arr1[i];
        i++;
        k++;
     }
}  

void mergesort(int arr[],int low,int high){
    if(low>=high) return;
    else{
    int mid=low+(high-low)/2;
    mergesort(arr,low,mid);
    mergesort(arr,mid+1,high);
    merge(arr,low,high);
    }
}
void countsort(int arr[],int len){
    int size=arr[0],i;
    for(i=1;i<len;i++){
        if(arr[i]>size) size=arr[i];
    }
    int countarr[size+1];
    for(i=0;i<size+1;i++) countarr[i]=0;
    for(i=0;i<len;i++) countarr[arr[i]]++;
    for(i=1;i<size+1;i++) countarr[i]+=countarr[i-1];
    int output[len];
    for(i=len-1;i>=0;i--){
        output[countarr[arr[i]]-1]=arr[i];
        countarr[arr[i]]--;
    }
    for(i=0;i<len;i++){
        arr[i]=output[i];
    }
}

void maxheapify(int arr[],int n,int i){
    int largest=i,left=2*i+1,right=2*i+2;
    if(left<n && arr[left]>arr[largest]) largest=left;
    if(right<n &&arr[right]>arr[largest]) largest=right;
    if(largest!=i){
        swap2(&arr[i],&arr[largest]);
        maxheapify(arr,n,largest);
    }
}
void buildheap(int arr[],int n){
    for(int i=(n-2)/2;i>=0;i--) maxheapify(arr,n,i);
}
void heapsort(int arr[],int n){
    buildheap(arr,n);
    for(int i=n-1;i>=1;i--){
        swap2(&arr[0],&arr[i]);
        maxheapify(arr,i,0);
    }
}
typedef struct bucket {
    int data;
    struct bucket* next;
} bucket;

bucket* loadbucket(bucket* node, int data) {
    bucket* newNode = (bucket*)malloc(sizeof(bucket));
    newNode->data = data;
    newNode->next = NULL;

    if (node == NULL || data <= node->data) {
        newNode->next = node;
        return newNode;
    }

    bucket* current = node;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;

    return node;
}

void bucketSort(int arr[], int n, int numBuckets) {
    bucket** buckets = (bucket**)malloc(sizeof(bucket*) * numBuckets);

    // Initialize buckets
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = NULL;
    }
    int max=arr[0];
    for(int i=1;i<n;i++){
        if(arr[i]>max) max=arr[i];
    }
    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = arr[i] * numBuckets /(max+1);
        buckets[bucketIndex] = loadbucket(buckets[bucketIndex], arr[i]);
    }

    // Merge sorted buckets back into the array
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        bucket* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            bucket* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

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
    printf("Enter choice of searching:\n1 -selectionsort 2-bubblesort\n3-insertionsort 4-mergesort\n5-bucketsort 6-countsort\n7-heapsort\n");
    scanf("%d", &choice);


    switch (choice) {
        case 1: {
            selectionsort(arr,len);
            break;
        }
        case 2: {
            bubblesort(arr,len);
            break;
        }
        case 3: {
            insertionsort(arr, len);
            break;
        }
        case 4:{
            mergesort(arr,0,len-1);
            break;
        }
        case 5: {
            int buckets;
            printf("enter number of buckets:");
            scanf("%d",&buckets);
            bucketSort(arr,len,buckets);
            break;
        }
        case 6: {
            countsort(arr,len);
            break;
        }
        case 7:{
            heapsort(arr,len);
            break;
        }
        default: {
            printf("\nInvalid choice: Exiting without search\n");
        }
    }


    // Write the modified array to the output file
FILE *f2;
f2 = fopen("output.txt", "w+");
for(int i=0;i<len;i++) fprintf(f2,"%d ",result);
fclose(f2);

    return 0;
}