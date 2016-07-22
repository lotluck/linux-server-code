/*==========================================================
     > File Name: common_insert_sort.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Tue 19 Jul 2016 07:31:51 PM CST
===========================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//函数指针隔离变化
typedef int (*Cmp_number)(void *a,void *b);
typedef void (*Print)(void *value);


// int类型的数据从小到大
int int_cmp(void *a,void *b)
{
    return *(int *)a - *(int *)b;

}
// int类型的数据从打到小
int int_reverse_cmp(void *a,void *b)
{
    return *(int *)b - *(int *)a;
}
//打印int类型的数据
void print_int(void *value)
{
   printf("%d ",*(int *)value);
}


// 关于double的
int  double_cmp(void *a,void *b)
{
    return (int)(*(double *)a - *(double*)b);
}
int  double_reverse_cmp(void *a,void *b)
{
    return (int)(*(double *)b - *(double*)a);
}
void print_double(void *value)
{
   printf("%.2f ",*(double *)value);
}

//关于char的
int char_cmp(void *a,void *b)
{
    return (int)(*(char  *)a - *(char *)b);
}
int  char_reverse_cmp(void *a,void *b)
{
    return (int)(*(char *)b - *(char *)a);
}
void  print_char(void *value)
{
   printf("%c ",*(char *)value);
}


// 选择排序
void select_sort(void **array,int n,Cmp_number cmp)
{
    int i = 0;
    int j = 0;
    int k = 0;
    void *data = NULL;

    if(array == NULL || n <= 1){
        return ;
    }
    for(i = 0; i < n -1; i++){
        k =i;
       for(j = i+1; j < n; j++){
           if(cmp(array[k],array[j]) > 0){
              k = j;
           }
       }
       data = array[i];
       array[i] = array[k];
       array[k] = data;
    }

}

//输出
void print_sort(void **array,int n,Print print_int)
{
    int i = 0;

    for(i = 0; i < n; i++){
      // printf("%d ",*(int**)array[i]);
      print_int(array[i]);
    }
    printf("\n");
}



int main(int argc,char *argv[])
{
    int i = 0;
    void   **array = NULL;
    int     a[10] = {5,2,1,1,2,5,125,521,2,2};
    double  b[10] = {2.5,5.2,1.1,5.21,2.5,5.21,2.51,1.0,9.1,5.21};
    char    c[10] = {'r','y','g','d','a','c','h','a','x','g'};

    array = malloc(sizeof(void *) *10);

    for(i = 0; i < 10; i++){
        array[i] = a + i;
    }
    select_sort(array,10,int_reverse_cmp);
    print_sort(array,10,print_int);


    memset(array,0x00,sizeof(array));
    for(i = 0; i < 10; i++){
        array[i] = b + i;
    }
    select_sort(array,10,double_cmp);
    print_sort(array,10,print_double);



    memset(array,0x00,sizeof(array));
    for(i = 0; i < 10; i++){
        array[i] = c + i;
    }
    select_sort(array,10,char_cmp);
    print_sort(array,10,print_char);
    return 0;
}


















































