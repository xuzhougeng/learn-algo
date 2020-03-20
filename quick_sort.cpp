#include <vector>
#include <iostream>
using namespace std;

/*
快速排序: 核心函数partition
*/

int partition(vector<int>& arr, int p, int r);
void quick_sort_c(vector<int>& arr, int p, int r);

void quick_sort(vector<int>&arr){
    quick_sort_c(arr, 0, arr.size()-1);
    return ;
}

void quick_sort_c(vector<int>& arr, int p, int r){

    if ( p < r ){
        int q = partition(arr, p, r);
        quick_sort_c(arr, p, q-1);
        quick_sort_c(arr, q+1, r);
    }

    return ;
}

/*
从p到r, 以此比较当前位置和最后一位


*/
int partition(vector<int>& arr, int p, int r){

    int x = arr[r]; 
    int i = p ;
    for ( int j = p; j < r ; j++){
        if (arr[j] < x){
            if ( i != j) std::swap(arr[i], arr[j]); // if用于避免重复的交换
            i++;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}

int main(int argc, char const *argv[])
{
    vector<int> arr{3,1,2,4,6};
    quick_sort(arr);
    for(int i = 0; i < arr.size(); i++) cout << arr[i] << ' ';
    cout << endl;
    /* code */
    return 0;
}
