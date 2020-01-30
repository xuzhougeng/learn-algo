#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct STACK {
    char **strings;
    int count; //栈占用
    int n; //栈大小
} Stack;

Stack *CreateStack(int num){
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));
    s->strings = (char **)malloc(sizeof(char*) *  num);
    s->count = 0;
    s->n = num;
    return s;
}

void DestroyStack( Stack *s)
{
    int i;
    for (i = 0; i < s->count; i++){
        free( (char *)s->strings[i] );
    }
    free(s->strings);
    free(s);
}

//出栈
char *pop(Stack *s)
{
    if ( s->count == 0){
        exit(EXIT_FAILURE);
    }
    char *string;
    int pos = s->count;
    string = s->strings[pos]; //获取字符串
    free(s->strings[pos]); //释放对应的内存
    s->count -= 1;
    return string;

}
//入栈
int push(Stack *s, char *string)
{
    int count = s->count;
    if ( count+1 > s->n){
        exit(EXIT_FAILURE);
    }
    s->count += 1;
    s->strings[s->count]  = strdup(string);
    return 1;
}

int main(int argc, char *argv[])
{
    int n = 10;
    Stack *s;
    s = CreateStack(n);
    push(s, "ab");
    push(s, "cd");
    push(s, "ef");
    push(s, "xzg");
    
    printf("%s\n", pop(s));
    printf("%s\n", pop(s));
    printf("%s\n", pop(s));
    printf("%s\n", pop(s));

    DestroyStack(s);
}
