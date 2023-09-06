#include<stdio.h>
int maxsum(int arr[],int len){
    int res=arr[0];
    int maxending=arr[0];
    for(int i=1;i<len;i++){
        maxending=((maxending+arr[i])>arr[i])?(arr[i]+maxending):arr[i];
        res=(res>maxending)?res:maxending;

    }
    return res;
}
int main(){
    int arr[]={13,11,-1,23,-4,4,-2,4,-15,1,9,8};
    int max=maxsum(arr,12);
    printf("%d",max);
    return 0;
}