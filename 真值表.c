#include<stdio.h>
#include<string.h>
typedef struct Stack
{
    char data[20];
    int top;
}Stack;
void transfer(char *str)
{
    int i,j;
    char ch;
    for(i=0,j=strlen(str)-1;i<j;i++,j--)
    {
        ch=str[i];
        str[i]=str[j];
        str[j]=ch;
    }
}
int main()
{
    char str[20];
    char acc[20];
    char s1,s2,s3;
    int cur;
    int d2[5],d3[9];
    int a1,a2,a3;
    a1=a2=a3=1;
    Stack sign;
    Stack var;
    Stack temp;
    int k,m,n;
    sign.top=var.top=-1;
    int count=0;
    gets(str);
    strcpy(acc,str);
    transfer(str);
    int i,len,j;
    len=strlen(str);
    for(i=0;i<len;i++)
    {
        switch(str[i])
        {
        case '!':
        case '&':
        case '|':
        case '>':
            sign.data[sign.top+1]=str[i];
            sign.top++;
            break;
        default:
            break;
        }
        if(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')
        {
            var.data[var.top+1]=str[i];
            var.top++;
            for(j=0;j<=var.top;j++)
            {
                if(var.data[j]==str[i])
                    break;
            }
            if(j==var.top)
                count++;//计算变量个数
            if(a1&&count==1)
            {
                s1=str[i];
                a1=0;
            }
            if(a2&&count==2)
            {
                s2=str[i];
                a2=0;
            }
            if(a3&&count==3)
            {
                s3=str[i];
                a3=0;
            }
        }
    }
    printf("变元个数：%d\n",count);
    temp=var;
    cur=1;
    printf("真值表如下：\n");
    switch(count)
    {
    case 1://只有一个变量
        printf("%c\t%s\n",s1,acc);
        for(k=1;k>=0;k--)
        {
            var=temp;
            for(j=0;j<=var.top;j++)
            {
                var.data[j]=k;
            }
            for(i=sign.top;i>=0;i--)
            {
                switch(sign.data[i])
                {
                case '!':
                    var.data[var.top]=!var.data[var.top];
                    break;
                case '&':
                    var.data[var.top-1]=var.data[var.top]&&var.data[var.top-1];
                    var.top--;
                    break;
                case '|':
                    var.data[var.top-1]=var.data[var.top]||var.data[var.top-1];
                    var.top--;
                    break;
                case '>':
                    var.data[var.top-1]=!var.data[var.top]||var.data[var.top-1];
                    var.top--;
                    break;
                default:
                    break;
                }
            }
            printf("%d\t%d\n",k,var.data[var.top]);
        }
        break;
    case 2://两个变量
        printf("%c\t%c\t%s\n",s2,s1,acc);
        for(k=1;k>=0;k--)
            for(m=1;m>=0;m--)
            {
                var=temp;
                for(j=0;j<=var.top;j++)
                {
                    if(s2==var.data[j])
                        var.data[j]=k;
                    if(s1==var.data[j])
                        var.data[j]=m;
                }
                for(i=sign.top;i>=0;i--)
                {
                    switch(sign.data[i])
                    {
                    case '!':
                        var.data[var.top]=!var.data[var.top];
                        break;
                    case '&':
                        var.data[var.top-1]=var.data[var.top]&&var.data[var.top-1];
                        var.top--;
                        break;
                    case '|':
                        var.data[var.top-1]=var.data[var.top]||var.data[var.top-1];
                        var.top--;
                        break;
                    case '>':
                        var.data[var.top-1]=!var.data[var.top]||var.data[var.top-1];
                        var.top--;
                        break;
                    default:
                        break;
                    }
                }
                d2[cur++]=var.data[var.top];
                printf("%d\t%d\t%d\n",k,m,var.data[var.top]);
            }
            break;
        case 3:
            printf("%c\t%c\t%c\t%s\n",s3,s2,s1,acc);
            for(k=1;k>=0;k--)
                for(m=1;m>=0;m--)
                    for(n=1;n>=0;n--)
                    {
                        var=temp;
                        for(j=0;j<=var.top;j++)
                        {
                            if(s3==var.data[j])
                                var.data[j]=k;
                            if(s2==var.data[j])
                                var.data[j]=m;
                            if(s1==var.data[j])
                                var.data[j]=n;
                        }
                        for(i=sign.top;i>=0;i--)
                        {
                            switch(sign.data[i])
                            {
                            case '!':
                                var.data[var.top]=!var.data[var.top];
                                break;
                            case '&':
                                var.data[var.top-1]=var.data[var.top]&&var.data[var.top-1];
                                var.top--;
                                break;
                            case '|':
                                var.data[var.top-1]=var.data[var.top]||var.data[var.top-1];
                                var.top--;
                                break;
                            case '>':
                                var.data[var.top-1]=!var.data[var.top]||var.data[var.top-1];
                                var.top--;
                                break;
                            default:
                                break;
                            }
                        }
                        d3[cur++]=var.data[var.top];
                        printf("%d\t%d\t%d\t%d\n",k,m,n,var.data[var.top]);
                    }
            break;
        default:
            break;
    }
    if(count==1)
        printf("不存在主合取和主析取范式\n");
    if(count==2)
    {
        j=0;
        printf("主合取范式：\n");
        for(i=1;i<=4;i++)
        {
            if(!d2[i])
            {
                if(j++!=0)
                   printf("/\\");
                printf("M(%d)",i-1);
            }
        }
        putchar('\n');
        j=0;
        printf("主析取范式：\n");
        for(i=4;i>=1;i--)
        {
            if(d2[i])
            {
                if(j++!=0)
                   printf("\\/");
                printf("m(%d)",4-i);
            }
        }
        putchar('\n');
    }
    if(count==3)
    {
        j=0;
        printf("主合取范式：\n");
        for(i=1;i<=8;i++)
        {
            if(!d3[i])
            {
                if(j++!=0)
                   printf("/\\");
                printf("M(%d)",i-1);
            }
        }
        putchar('\n');
        j=0;
        printf("主析取范式：\n");
        for(i=8;i>=1;i--)
        {
            if(d3[i])
            {
                if(j++!=0)
                   printf("\\/");
                printf("m(%d)",8-i);
            }
        }
        putchar('\n');
    }
    return 0;
}






















