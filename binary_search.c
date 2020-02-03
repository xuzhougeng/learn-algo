#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int bSearch(int *arr, int n, int value)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high){
        mid = low + ((high-low) >> 1);
        if (arr[mid] == value){
            return mid;
        } else if(arr[mid] < value){
            low = mid + 1;
        } else{
            high = high - 1;
        }
    }
    return -1;
}

int bSearchFirstEqual(int *arr, int n, int value)
{
    int low = 0;
    int high = n-1;
    int mid;
    while (low <= high){
        mid = low + ( (high-low) >> 1);
        // 如果中间的数字比给的值大
        // 数据应该在low-mid里
        if (arr[mid] > value){
            high = mid - 1;
        // 如果中间的数字比给的值小
        // 数据应该在mid-high里
        } else if( arr[mid] < value){
            low = mid + 1;
        } else{
            //如果相等, 先看这个位置是不是第一个, 或者它的前面值是否和它相等
            //如果mid是第一个或者是前面值不等, 当前值就是所找的值
            if ( mid == 0 || arr[mid-1] != value) return mid;
            //否则应该在mid-high中
            else high = mid - 1;
        }
        
    }
    return -1;

}

int bSearchLastEqual(int *arr, int n, int value)
{
    int low = 0;
    int high = n - 1;
    int mid ;
    while ( low <= high){
        mid = low + ( (high-low) >> 1);
        if (arr[mid] > value ){
            high = mid - 1;
        } else if ( arr[mid] < value){
            low = mid + 1 ;
        } else {
            if ( mid == n -1 || arr[mid+1] != value) return mid;
            else low =  mid + 1;
        }
    }
    return -1;
}

int bSearchFirstLarge(int *arr, int n, int value)
{
    int low = 0;
    int high = n -1;
    int mid;
    while (low <= high){
        mid = low + ((high-low) >>  1);
        if (arr[mid] >= value){
            if ( mid == 0 || arr[mid-1] < value ) return mid;
            else high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return -1;
}

int bSearchLastLess(int *arr, int n, int value)
{
    int low = 0;
    int high = n -1;
    int mid;
    while (low <= high){
        mid = low + ((high-low) >>  1);
        if (arr[mid] > value){
            high = mid - 1;
        } else{
            if ( mid == n-1 ||  arr[mid+1] > value) return mid;
            else low = mid + 1;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{

    int arr[] = {1,2,3,10,11,19,21};
    printf("%d\n", bSearch(arr, sizeof(arr) / sizeof(int), 3));
    int arr2[] = {1,2,3,3,3,10,11,19,21};
    printf("%d\n", bSearchFirstEqual(arr2, sizeof(arr2) / sizeof(int), 3));
    printf("%d\n", bSearchLastEqual(arr2, sizeof(arr2) / sizeof(int), 3));
    printf("%d\n", bSearchFirstLarge(arr2, sizeof(arr2) / sizeof(int), 2));
    printf("%d\n", bSearchLastLess(arr2, sizeof(arr2) / sizeof(int), 3));
    return 0;
}
