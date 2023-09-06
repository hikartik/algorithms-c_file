#include<stdio.h>
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
int swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
int partition(int arr[],int l,int h){
    int pivot=arr[l];
    int i=l-1;
    int j=h+1;
    while(1){
        do{
            i++;
        }while(arr[i]<pivot);
        do{
            j--;
        }while(arr[j]>pivot);
        if(i>=j) return j;
        swap(&arr[i],&arr[j]);
    }
}
int kthsmallest(int arr[],int n,int k){
    int l=0,hi=n-1;
    while(l<=hi){
        int p=partition(arr,l,hi);
        if(p==k-1) return arr[p];
        else if(p>k-1) hi=p-1;
        else l=p+1;
    }
    return -1;
}

int main(){
    int arr[]={3,4,6,2,1,34,56,21,32,13,15,11};
    int ans=kthsmallest(arr,12,1);
    printf("%d\n",ans);
    bubblesort(arr,12);
    for(int i=0;i<12;i++) printf("%d ",arr[i]);
    return 0;
}