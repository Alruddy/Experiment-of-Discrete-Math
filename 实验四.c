/**
*对给定的m个结点和n条边，随机生成相关邻接矩阵以确定某无向简单图
*基于度的计算进行欧拉图和半欧拉图的判定
*若符合则给出至少一条欧拉回路或欧拉路
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int b[40];
int c[40];
int x;
void print(int a[][20],int n);
int Matrixmulti(int a[][20],int c[][20],int num,int m);         /**矩阵布尔幂乘*/
int Matrixplus(int a[][20],int b[][20],int c[][20],int num);    /**矩阵布尔相加*/
void Trace1(int v ,int a[][20],int num,int n);
void Trace2(int v ,int a[][20],int num,int n);
int main()
{
    int i,j;
    int m,n;
    int NumofOddDeg=0;
    int Matrix[20][20];                 /**储存邻接矩阵*/
    int book[400]={0};                  /**储存随机生成的边*/
    int count=0;
    int temp;
    int c[20][20],result1[20][20],result2[20][20];
    int k;
    int flag=0;
    printf("输入生成图的节点数和边数:\n");
    scanf("%d%d",&m,&n);

    //int Matrix[20][20];                 /**储存邻接矩阵*/
    //int book[400]={0};                  /**储存随机生成的边*/
    //int count=0;
   // int temp;
    for(i=0;i<20;i++)                           /**初始化邻接矩阵*/
        for(j=0;j<20;j++)
            Matrix[i][j]=0;

    srand(time(NULL));
    while(n!=count)                             /**随机生成边且边的个数是n*/
    {
        temp=rand()%(m*m);
        if(book[temp]==0&&(temp/m!=temp%m))     /**主对角线元素为0*/
        {
            book[temp]=1;
            book[(temp%m)*m+temp/m]=1;          /**无向图邻接矩阵对称*/
            Matrix[temp/m][temp%m]=1;
            Matrix[temp%m][temp/m]=1;
            count++;
        }
    }
    printf("输出邻接矩阵:\n");
    print(Matrix,m);                            /**打印矩阵*/
    printf("\n");

    /**判断图是否是连通图，即该图的邻接矩阵的传递闭包矩阵是否都是1*/
    //int c[20][20],result1[20][20],result2[20][20];
    //int k;
    //int flag=0;
    for(i=0;i<m;i++)
        for(j=0;j<m;j++)
            result1[i][j]=Matrix[i][j];             /** result1= matrix^1   */
    for(k=2;k<=m;k++)
    {
        Matrixmulti(Matrix,c,m,k);                  /** c= matrix^k         */
        Matrixplus(result1,c,result2,m);            /** result2=result1+c   */
        for(i=0;i<m;i++)                            /** result1=result2     */
            for(j=0;j<m;j++)
            result1[i][j]=result2[i][j];
    }
    printf("输出闭包矩阵:\n");
    print(result2,m);                               /**得闭包矩阵 result2   */
    for(i=0;i<m;i++)
    {
        if(result2[0][i]!=1)
            break;
    }
    if(i==m)
    {
        printf("邻接矩阵所表示的图为连通图");
        flag=1;
    }
    else
        printf("邻接矩阵所表示的图不是连通图,");

    /**基于度的计算进行欧拉图和半欧拉图的判定  前提是图是连通的*/
    //int NumofOddDeg=0;
    if(flag==1)
    {
        for(i=0;i<m;i++)
        {
            count=0;
            for(j=0;j<m;j++)                        /**计算第i行的1，即计算i结点的度*/
            {
                if(Matrix[i][j]==1)
                    count++;
            }
            if(count%2)                             /**度是奇数，计数加一*/
                NumofOddDeg++;
        }
        if(NumofOddDeg==0)
            printf("，而且该图是欧拉图，有欧拉回路\n");
        else if(NumofOddDeg==2)
            printf("，而且该图是半欧拉图，有欧拉路\n");
        else
            printf("，但该图不是欧拉图\n");
    }
    else
        printf("该图不是欧拉图\n");

/**若符合则给出至少一条欧拉回路或欧拉路*/
    if(NumofOddDeg==2)
    {
        for(i=0;i<m;i++)
        {
            count=0;
            for(j=0;j<m;j++)
            {
                if(Matrix[i][j]==1)
                    count++;
            }
            if(count%2)
               {
                   temp=i;
                   break;
               }
        }
        Trace1(temp,Matrix,m,0);

    }
    if(NumofOddDeg==0)
    {
        for(i=0;i<m;i++)
        {
            Trace1(i,Matrix,m,0);
        }
    }

    return 0;
}
void print(int a[][20],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}
int Matrixmulti(int a[][20],int c[][20],int num,int m)/**参数1：自复合参数a 结果参数c 长度参数num 自复合幂数k*/
{
    int i,j;
    int b[20][20];
    int k;
    m=m-1;
    for(i=0;i<num;i++)
        for(j=0;j<num;j++)
            {
                b[i][j]=a[i][j];
                c[i][j]=0;
            }
    do
    {
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                for(k=0;k<num;k++)
                    c[i][j]=c[i][j]||(b[i][k]&&a[k][j]);
            }
        }
        for(i=0;i<num;i++)
            for(j=0;j<num;j++)
                b[i][j]=c[i][j];
                m--;
    }while(m);
    return 1;
}
int Matrixplus(int a[][20],int b[][20],int c[][20],int num)
{
    int i,j;
    for(i=0;i<num;i++)
        for(j=0;j<num;j++)
            c[i][j]=a[i][j]||b[i][j];
    return 1;
}
void Trace1(int v ,int a[][20],int num,int n)
{
    int flag=0;
    int i,j;

    for(i=0;i<num;i++)
        for(j=0;j<num;j++)
        {
            if(a[i][j]==1)
                flag=1;
        }
    if(flag==0) /**终止条件: 所有的边全部遍历完*/
    {
        if(x==0)
        {
            for(i=0;i<=n;i++)
                printf("%d ",b[i]);
            printf("\n");
            x=1;
        }
        return;
    }
    for(i=0;i<num;i++)
    {
        if(a[v][i]==1)
        {
            b[n]=v;
            b[n+1]=i;
            a[v][i]=0;
            a[i][v]=0;
            Trace1(i,a,num,n+1);

            a[v][i]=1;
            a[i][v]=1;

        }
    }
    return ;
}
void Trace2(int v ,int a[][20],int num,int n)
{
    int flag=0;
    int i,j;

    for(i=0;i<num;i++)
        for(j=0;j<num;j++)
        {
            if(a[i][j]==1)
                flag=1;
        }
    if(flag==0&&b[0]==b[n]) /**终止条件: 所有的边全部遍历完,最终结点和开始节点一样*/
    {
        if(x==0)
        {
            for(i=0;i<=n;i++)
                printf("%d ",b[i]);
            printf("\n");
            x=1;
        }
        return;
    }
    for(i=0;i<num;i++)
    {
        if(a[v][i]==1)
        {
            b[n]=v;
            b[n+1]=i;
            a[v][i]=0;
            a[i][v]=0;
            Trace2(i,a,num,n+1);

            a[v][i]=1;
            a[i][v]=1;

        }
    }
    return;
}






