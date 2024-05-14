#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 1000

typedef struct{
    char *ch;
    int length;
    int strsize;
}HString;

//初始化字符串
void init(HString *s){
    s->ch=(char *)malloc(MAX_STRING_SIZE*sizeof(char));
    s->ch[0]='\0';
    s->length=0;
    s->strsize=MAX_STRING_SIZE;
}

//获取字符串
void getmyline(HString *s){
    while(1){
        s->ch[s->length]=getchar();
        if(s->ch[s->length]=='\n')
            break;
        s->length++;
    }
    s->ch[s->length]='\0';
}

//求next[j]
void GetNext(HString *t,int next[]){
    int j,k;
    j=0;
    k=-1;
    next[0]=-1;
    while(j<t->length){
        if(k==-1||t->ch[j]==t->ch[k]){
            j++;k++;
            next[j]=k;
        }else k=next[k];
    }
}

//模式串匹配
int StrDex(HString *s,HString *t){

    int next[MAX_STRING_SIZE];
    GetNext(t,next);
    int i,j;
    i=0;
    j=0;
    while(i<s->length&&j<t->length){
        if(j==-1||s->ch[i]==t->ch[j]){
            i++;
            j++;
        }else{
            j=next[j];
        }
    }

    if (j == t->length)
    {
        printf("匹配成功!\n");
        return i - j + 1; // 返回匹配的起始位置
    }
    else
    {
        printf("匹配失败!\n");
        return -1; // 返回匹配失败的标志
    }

}

int main(){
    HString *s=(HString *)malloc(sizeof(HString));
    HString *t=(HString *)malloc(sizeof(HString));
    init(s);
    init(t);
    printf("请输入母串s\n");
    getmyline(s);
    printf("请输入子串t\n");
    getmyline(t);
    printf("子串首字母在母串中的位置为 %d\n",StrDex(s,t));
    return 0;
}
