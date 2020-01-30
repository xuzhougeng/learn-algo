#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// 队伍是先进先出的(First in First out, FIFO)
// 栈是先进后出(First in Last out, FiLO)

typedef char* String;

typedef struct {
    int *arr; //数据存放位置
    int n;    //队列大小
    int head; //头
    int tail; //尾
} Queue;

// 创建队列
Queue *CreateQueue(int size)
{
    Queue *queue;
    queue = (Queue *)malloc( sizeof(Queue) );
    queue->arr = (int *)malloc( sizeof(int) * size);
    queue->head = 0;
    queue->tail = 0;
    queue->n = size;
    return queue;
    
}

// 删除队列
void DestroyQueue( Queue *queue )
{
    free(queue->arr);
    free(queue);
}

//入队
// 队伍后面进入
void enqueue( Queue *queue, int item)
{
    // 如果队伍到尾了
    if ( queue-> tail == queue->n){
        //队伍满了
        if(queue->head == 0){
            fprintf(stderr, "queue is full: %d / %d\n", queue->tail - queue->head , queue->n);
            return ;
        }
        //队伍没有满, 整体向前移动队伍
        int i;
        int j = 0;
        for (i = queue->head; i < queue->tail; i++){
            queue->arr[j] = queue->arr[i];
            j++;
        }
        queue->head = 0;
        queue->tail = j;

    }

    queue->arr[queue->tail] = item;
    queue->tail+=1;

}

// 出队
// 移除头部元素
int dequeue( Queue *queue)
{
    //没有元素, 直接返回
    if (queue->head == queue->tail) {
        fprintf(stderr, "no more element in queue\n");
        exit(EXIT_FAILURE);
    }
    int item;
    item = queue->arr[queue->head];
    queue->head+=1;
    return item;
}

int main(int argc, char *argv[])
{
    Queue *queue;
    queue = CreateQueue( 5 );

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    enqueue(queue, 6);
    enqueue(queue, 7);
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));

}
