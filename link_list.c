#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//定义节点
struct _Node;
typedef struct _Node Node;

struct _Node{
    int data;
    Node *next;
};

//定义列表
typedef struct _List {
    Node *head;  //记录头地址
    Node *tail;  //记录尾巴地址
    int num;
} List;

// 创建链表
List *CreateList()
{
    List *list;
    list = (List*)malloc( sizeof(List) );
    list->num = 0;
    return list;
}
// 删除链表
void DestroyList(List *list)
{
    Node *current;
    Node *next;
    current = list->head;
    while (current->next != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}
// 清空列表
void CleatList(List *list)
{
    Node *node;
    node = list->head;
    while (node->next != NULL){
        node->data = 0;
        node = node->next;
    }
    node->data = 0;
}

// 查找元素
// situ=true时, 返回当前位置, false, 则返回上一个位置
Node *Search(List *list, int data, bool situ)
{
    Node *node;
    node = list->head;
    if ( situ ){
        while ( node->next != NULL ){
            if ( node->data == data)
                return node;
            node = node->next;
        }
    } else {
        while ( node->next->next != NULL) {
            if (node->next->data == data)
                return node;
            node = node->next;
        }
    }
    return NULL;
}

//删除节点
bool DeleteNode( List* list, int data){

    Node *node;
    Node *tmp;
    node = list->head;
    // 判断这个节点是否是首节点
    if ( node->data == data ){
        free(list->head);
        list->head = NULL;
        list->tail = list->head;
        list->num = 0;
        return true;
    }
    // 查找给定节点的前一个节点
    node = Search(list, data, false);
    // 找不到节点
    if (  node  == NULL){
        return false;
    }
    //删除
    tmp = node->next->next;
    free(node->next);
    node->next = tmp;
    return true;
}

//在给定元素前加节点
bool InsertNode( List* list, int query, int data){

    Node *node;
    Node *new_node;

    // 为新节点分配内存
    new_node = (Node *)malloc( sizeof(Node) );
    if ( new_node == NULL) return false;
    new_node->data = data;

    node = list->head;
    // 判断这个节点是否是首节点
    if ( node->data == query ){
        new_node->next = node->next ;
        node->next = new_node;
        return true;
    }

    // 查找给定节点的前一个节点
    node = Search(list, query, false);
    // 找不到节点
    if (  node  == NULL){
        return false;
    }
    new_node->next = node->next ;
    node->next = new_node;

    return true;

}

//在给定元素后加
bool AppendNode( List* list, int query, int data){

    Node *node;
    Node *new_node;

    // 为新节点分配内存
    new_node = (Node *)malloc( sizeof(Node) );
    if ( new_node == NULL) return false;
    new_node->data = data;

    // 查找给定节点的位置
    node = Search(list, query, true);
    // 找不到节点
    if (  node  == NULL){
        return false;
    }
    new_node->next = node->next;
    node->next = new_node;

    return true;

}


// 加入元素到末尾
bool AddNode(List *list, int data)
{
    Node *node;
    Node *new_node;

    new_node = (Node *)malloc( sizeof(Node) );
    if ( new_node == NULL) return false;
    new_node->data = data;
    new_node->next = NULL;

    //获取链表head
    node = list->head ;
    //如果head指向NULL, 则直接插入到下一个
    if ( node == NULL){
        list->head = new_node;
        list->tail = new_node;
        list->num = 1;
        return true;
    }
    // 否则在尾部插入节点
    node = list->tail ;
    node->next = new_node;
    list->tail = new_node;
    list->num+=1;

    return true;

}

//打印整个链表
void dump(List *list){
    Node *node;
    node = list->head;
    printf("Linked List\n");
    printf("---------\n");
    while (node != NULL){
        printf("%08d\n", node->data);
        node = node->next;
    }
}

//反转链表
List* reverseList(List* list){

    Node *curr, *res;
    res = NULL;
    curr = list->head;
    //尾巴是之前的开头
    list->tail = list->head;
    while ( curr ){
        //移动head
        list->head = list->head->next;
        //将当前位置指向前一个位置
        curr->next = res;
        //依次向后移动res和curr
        res = curr;
        curr = list->head;
    }
    list->head = res;
    return list;
}

//寻找中间值
Node *FindMidlle(List *list)
{
    if (list->num == 0) return NULL;
    Node *fast = list->head;
    Node *slow = list->head;
    while ( fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;

}

bool RemoveLastN(List *list, int n)
{
    //删除第一个
    if ( list->num == n){
        list->head = list->head->next;
        return true;
    }
    Node *fast = list->head;
    Node *slow = list->head;
    Node *tmp;
    while (n-- > 0){
        fast = fast->next;
    }
    while (fast->next != NULL){
        fast = fast->next;
        slow = slow->next;
    }
    tmp = slow->next;
    slow->next = slow->next->next;
    free(tmp);
    return true;
}

//合并两个链表
List *MergeSortedList(List *list_a, List *list_b)
{
    List *list_c;
    list_c = CreateList();
    Node *node_a, *node_b, *node_c;
    node_a = list_a->head;
    node_b = list_b->head;

    //确定新列表的head
    if ( node_a->data < node_b->data ){
        list_c->head = node_a;
        node_a = node_a->next;
    } else {
        list_c->head = node_b;
        node_b = node_b->next;

    }
    node_c = list_c->head;
    while( true ){
        if  (node_a == NULL || node_b == NULL ) break;

        if (node_a->data < node_b->data){
            node_c->next = node_a;
            node_a = node_a->next;
        } else{
            node_c->next = node_b;
            node_b = node_b->next;
        }
            node_c = node_c->next;
    }
    while ( node_a != NULL){
        node_c->next = node_a;
        node_a = node_a->next;
        node_c = node_c->next;

    }
    while ( node_b != NULL){
        node_c->next = node_b;
        node_b = node_b->next;
        node_c = node_c->next;
    }
    return list_c;
}

int MergeTest( const char *file1, const char *file2){
    FILE *f1;
    FILE *f2;

    int data;
    f1 = fopen(file1, "r");

    List *list1;
    list1 = CreateList();
    //读取数据
    while (fscanf(f1, "%d", &data) != EOF){
        AddNode(list1, data);
    }
    dump(list1);
    fclose(f1);

    f2 = fopen(file2, "r");
    if (f2 == NULL){
        perror(file2);
        exit(EXIT_FAILURE);
    }
    List *list2;
    list2 = CreateList();

    //读取数据
    while (fscanf(f2, "%d", &data) != EOF){
        AddNode(list2, data);
    }
    dump(list2);
    fclose(f2);

    List *res;
    res = MergeSortedList(list1, list2);
    dump(res);
    return 0;

}

int main(int argc, char const *argv[])
{
    /* code */
    if (argc == 1) exit(EXIT_FAILURE);
    MergeTest(argv[2], argv[3]);
    int data;

    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    List *list;
    list = CreateList();
    //读取数据
    while (fscanf(fp, "%d", &data) != EOF){
        AddNode(list, data);
    }
    printf("current data ");
    dump(list);
    fclose(fp);
    //寻找中间值
    printf("Middle:%d \n", FindMidlle(list)->data);
    // 删除最后值
    printf("remove last value ");
    RemoveLastN(list, 1);
    dump(list);
    //反转链表
    printf("reverse list ");
    list = reverseList(list);
    dump(list);

    // 搜素节点=5
    Node *node;
    node = Search(list, 5, true);
    printf("%d\n", node->data);

    // 删除节点=5
    printf("Delete data ");
    DeleteNode(list, 5);
    dump(list);
    //在5前面加入元素7
    printf("Add 7 before 5 ");
    InsertNode(list, 6, 5);
    dump(list);
    //在6后面加入元素8
    printf("Add 8 After 6 ");
    AppendNode(list, 6,8);
    dump(list);
    // 删除链表
    DestroyList(list);

    return 0;
}
