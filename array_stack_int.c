#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct STACK {
    int *arr;
    int count; //栈占用
    int n; //栈大小
} Stack;

Stack *CreateStack(int num){
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));
    s->arr = (int *)malloc(sizeof(int) *  num);
    s->count = 0;
    s->n = num;
    return s;
}

void DestroyStack( Stack *s)
{
    free(s->arr);
    free(s);
}

//出栈
int pop(Stack *s)
{
    if ( s->count == 0){
        exit(EXIT_FAILURE);
    }
    int num;
    num = s->arr[s->count];
    s->count -= 1;
    return num;

}
//入栈
int push(Stack *s, int num)
{
    int count = s->count;
    if ( count+1 > s->n){
        exit(EXIT_FAILURE);
    }
    s->count += 1;
    s->arr[s->count]  = num;
    return 1;
}

int main(int argc, char *argv[])
{
    int n = 10;
    Stack *s;
    s = CreateStack(n);
    push(s, 10);
    
    int out;
    out = pop(s);
    printf("%d\n", out);

    DestroyStack(s);
}
