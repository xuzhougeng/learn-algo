#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 堆(heap)
 * 满足两个要求:
 *   1. 完全二叉树
 *   2. 父节点的元素大于(或小于)子节点的元素
 */

typedef struct _heap {
	int *heap; //堆
	int n; //堆的大小
	int count; //堆目前的元素
} heap;

// 交换数组的元素arr[idx1]和arr[idx2]
void swap(int *arr, int idx1, int idx2)
{
	int tmp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = tmp;
}

// 打印堆中的元素
void dump(heap *h){
	int n = h->n;
	int count = h->count;
	int *heap = h->heap;
	int i;
	for ( i = 1; i <= count; i++){
		printf("%08d\n", heap[i]);
	}


}

//构建一个大小为n的堆
heap*
createHeap(int n){

	heap *h;
	h = (heap*)malloc( sizeof(heap) );
	h->heap = (int*)malloc( sizeof(int) * (n+1));
	h->n = n;
	h->count = 0;
	return h;
}

//插入元素
void insertElement(heap *h, int e){

	int count = h->count;
	int n = h->n;
	if ( count >= n) return;

	// 在数组最后加入新的元素
	int *heap = h->heap;
	heap[++count] = e;
	h->count = count;

	int i = count;// 数组索引
	//堆化,
	while( (i/2) > 0 && heap[i] > heap[i/2] ){
		swap(heap, i, i/2); //交换父子节点
		i = i / 2;
	}
}

//删除顶部元素
void removeTop(heap *h){

	if (h->count < 1) return ;

	int count = h->count;
	int *heap = h->heap;
	//用最后一个元素替代第一个元素
	heap[1] = heap[count];
	//删除最后一个元素
	h->count = --count;
	// 自上而下堆化
	int i = 1;
	while ( true ){
	    int max_pos = i;
		if ( i*2 <=count && heap[i] < heap[i*2]) max_pos = i*2; //和左子节点比较
		if ( i*2+1<=count && heap[i] < heap[i*2+1]) max_pos = i*2+1; //和右子节点比较
		if (max_pos == i) break; // 不再发生交换, 当前位置就是最大位置
		swap(heap, i, max_pos); //将当前节点和子节点进行交换
		i = max_pos ; //将i设置为子节点的索引
	}

}

int main(int argc, char *argv[])
{
	heap *h;
	h = createHeap(100);
	int arr[] = {2,1,10,21,19,6,5,12,9};
	int i;
	for ( i = 0; i < sizeof(arr)/sizeof(int); i++){
		insertElement(h, arr[i]);
	}
	dump(h);
	printf("--------\n");
	removeTop(h);
	dump(h);


}
