/**
*�Ը�����m������n���ߣ������������ڽӾ�����ȷ��ĳ�����ͼ
*���ڶȵļ������ŷ��ͼ�Ͱ�ŷ��ͼ���ж�
*���������������һ��ŷ����·��ŷ��·
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int b[40];
int c[40];
int x;
void print(int a[][20],int n);
int Matrixmulti(int a[][20],int c[][20],int num,int m);         /**���󲼶��ݳ�*/
int Matrixplus(int a[][20],int b[][20],int c[][20],int num);    /**���󲼶����*/
void Trace1(int v ,int a[][20],int num,int n);
void Trace2(int v ,int a[][20],int num,int n);
int main()
{
    int i,j;
    int m,n;
    int NumofOddDeg=0;
    int Matrix[20][20];                 /**�����ڽӾ���*/
    int book[400]={0};                  /**����������ɵı�*/
    int count=0;
    int temp;
    int c[20][20],result1[20][20],result2[20][20];
    int k;
    int flag=0;
    printf("��������ͼ�Ľڵ����ͱ���:\n");
    scanf("%d%d",&m,&n);

    //int Matrix[20][20];                 /**�����ڽӾ���*/
    //int book[400]={0};                  /**����������ɵı�*/
    //int count=0;
   // int temp;
    for(i=0;i<20;i++)                           /**��ʼ���ڽӾ���*/
        for(j=0;j<20;j++)
            Matrix[i][j]=0;

    srand(time(NULL));
    while(n!=count)                             /**������ɱ��ұߵĸ�����n*/
    {
        temp=rand()%(m*m);
        if(book[temp]==0&&(temp/m!=temp%m))     /**���Խ���Ԫ��Ϊ0*/
        {
            book[temp]=1;
            book[(temp%m)*m+temp/m]=1;          /**����ͼ�ڽӾ���Գ�*/
            Matrix[temp/m][temp%m]=1;
            Matrix[temp%m][temp/m]=1;
            count++;
        }
    }
    printf("����ڽӾ���:\n");
    print(Matrix,m);                            /**��ӡ����*/
    printf("\n");

    /**�ж�ͼ�Ƿ�����ͨͼ������ͼ���ڽӾ���Ĵ��ݱհ������Ƿ���1*/
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
    printf("����հ�����:\n");
    print(result2,m);                               /**�ñհ����� result2   */
    for(i=0;i<m;i++)
    {
        if(result2[0][i]!=1)
            break;
    }
    if(i==m)
    {
        printf("�ڽӾ�������ʾ��ͼΪ��ͨͼ");
        flag=1;
    }
    else
        printf("�ڽӾ�������ʾ��ͼ������ͨͼ,");

    /**���ڶȵļ������ŷ��ͼ�Ͱ�ŷ��ͼ���ж�  ǰ����ͼ����ͨ��*/
    //int NumofOddDeg=0;
    if(flag==1)
    {
        for(i=0;i<m;i++)
        {
            count=0;
            for(j=0;j<m;j++)                        /**�����i�е�1��������i���Ķ�*/
            {
                if(Matrix[i][j]==1)
                    count++;
            }
            if(count%2)                             /**����������������һ*/
                NumofOddDeg++;
        }
        if(NumofOddDeg==0)
            printf("�����Ҹ�ͼ��ŷ��ͼ����ŷ����·\n");
        else if(NumofOddDeg==2)
            printf("�����Ҹ�ͼ�ǰ�ŷ��ͼ����ŷ��·\n");
        else
            printf("������ͼ����ŷ��ͼ\n");
    }
    else
        printf("��ͼ����ŷ��ͼ\n");

/**���������������һ��ŷ����·��ŷ��·*/
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
int Matrixmulti(int a[][20],int c[][20],int num,int m)/**����1���Ը��ϲ���a �������c ���Ȳ���num �Ը�������k*/
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
    if(flag==0) /**��ֹ����: ���еı�ȫ��������*/
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
    if(flag==0&&b[0]==b[n]) /**��ֹ����: ���еı�ȫ��������,���ս��Ϳ�ʼ�ڵ�һ��*/
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






