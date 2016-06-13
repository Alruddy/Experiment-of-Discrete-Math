#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Order
{
    int left,right;
}Order;
int Ordersort(Order *,int ,Order *,int *,int );
int Reflejudge(int a[][6],int );
int Symmejudge(int a[][6],int );
int FReflejudge(int a[][6],int );
int FSymmejudge(int a[][6],int );
int Transmjudge(int a[][6],int );
int Matrixmulti(int a[][6],int c[][6],int ,int );//关系矩阵的复合运算
int Matrixplus(int a[][6],int b[][6],int c[][6],int );
int Transmjudge2(Order *a,int n);
int main()
{
    int num;
    int n,i,j,count,m=0;
    int x[25];
    Order O[25],b[25],c[25];
    int matrix[6][6];
    printf("输入集合X的元素个数：\n");
    scanf("%d",&num);
    for(i=0;i<25;i++)
        x[i]=0;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
        matrix[i][j]=0;
    srand(time(NULL));
    n=rand()%(num*num)+1;
    for(i=0;i<n;i++)
    {
        O[i].left=rand()%num+1;
        O[i].right=rand()%num+1;
    }
    for(i=0;i<n;i++)
    {
        matrix[O[i].left][O[i].right]=1;
    }
    /*这里插入一个函数：
    功能：对重复的序偶进行消除，并进行排序
    */
    count=Ordersort(O,n,b,x,num);
    printf("输出自动生成的关系：\n{");
    for(i=0;i<num*num;i++)
    {
        if(x[i]==1)
        {
            m++;
            printf("<%d,%d>",b[i].left,b[i].right);
			c[m].left=b[i].left;
			c[m].right=b[i].right;
            if(m!=count)
                putchar(',');
        }
    }
    putchar('}');
	/*putchar('\n');
	for(i=1;i<=m;i++)
	{
		printf("<%d,%d> ",c[i].left,c[i].right);
	}
	putchar('\n');*/
    printf("\n输出关系矩阵：\n");
    for(i=1;i<=num;i++)
    {
        for(j=1;j<=num;j++)
        {
            printf("%d ",matrix[i][j]);
        }
        putchar('\n');
    }
    /*判断性质*/
    Reflejudge(matrix,num);
    Symmejudge(matrix,num);
    FReflejudge(matrix,num);
    FSymmejudge(matrix,num);
    //Transmjudge(matrix,num);
	Transmjudge2(c,m);
    return 0;
}
int Ordersort(Order *a,int n,Order *b,int *x,int num)
{
    int i,j;
    int count=0;
    for(i=0;i<num;i++)
        for(j=0;j<num;j++)
        {
            b[i*num+j].left=i+1;
            b[i*num+j].right=j+1;
        }
    for(i=0;i<n;i++)
    {
        for(j=0;j<num*num;j++)
        {
            if(a[i].left==b[j].left&&a[i].right==b[j].right)
            {
                x[j]=1;
            }
        }
    }
    for(i=0;i<num*num;i++)
    {
        if(x[i]==1)
            count++;
    }
    return count;
}
int Reflejudge(int a[][6],int num)
{
    int i;
    for(i=1;i<=num;i++)
    {
        if(a[i][i]==0)
        {
            printf("序偶<%d,%d>不存在，故该关系不是自反的。\n",i,i);
            return 0;
        }
    }
    printf("该关系是自反的。\n");
    return 1;
}
int Symmejudge(int a[][6],int num)
{
    int i,j;
    for(i=1;i<=num;i++)
    {
        for(j=num;j>i;j--)
        {
            if(a[i][j]!=a[j][i])
            {
                printf("序偶<%d,%d>与序偶<%d,%d>并不同时在该关系中，故不满足对称性。\n",i,j,j,i);
                return 0;
            }
        }
    }
    printf("该关系是对称的。\n");
    return 1;
}
int FReflejudge(int a[][6],int num)
{
    int i;
    for(i=1;i<=num;i++)
    {
        if(a[i][i]==1)
        {
            printf("序偶<%d,%d>存在，故该关系不是反自反的。\n",i,i);
            return 0;
        }
    }
    printf("该关系是反自反的。\n");
    return 1;
}
int FSymmejudge(int a[][6],int num)
{
    int i,j;
    for(i=1;i<=num;i++)
    {
        for(j=num;j>i;j--)
        {
            if(a[i][j]==a[j][i]&&(a[i][j]==1||a[j][i]==1))
            {
                printf("序偶<%d,%d>与序偶<%d,%d>同时在该关系中，故不满足反对称性。\n",i,j,j,i);
                return 0;
            }
        }
    }
    printf("该关系是反对称的。\n");
    return 1;
}
int Matrixmulti(int a[][6],int c[][6],int num,int m)//参数1：自复合参数a 结果参数c 长度参数num 自复合幂数k
{
    int i,j;
    int b[6][6];
    int k;
    m=m-1;
    for(i=1;i<=num;i++)
        for(j=1;j<=num;j++)
            {
                b[i][j]=a[i][j];
                c[i][j]=0;
            }
    do
    {
        for(i=1;i<=num;i++)
        {
            for(j=1;j<=num;j++)
            {
                for(k=1;k<=num;k++)
                    c[i][j]=c[i][j]||(b[i][k]&&a[k][j]);
            }
        }
        for(i=1;i<=num;i++)
            for(j=1;j<=num;j++)
                b[i][j]=c[i][j];
                m--;
    }while(m);
    return 1;
}
int Matrixplus(int a[][6],int b[][6],int c[][6],int num)
{
    int i,j;
    for(i=1;i<=num;i++)
        for(j=1;j<=num;j++)
            c[i][j]=a[i][j]||b[i][j];
    return 1;
}
int Transmjudge(int a[][6],int num)
{
    int c[6][6],result1[6][6],result2[6][6];
    int k;
    int i,j;
    for(i=1;i<=num;i++)
        for(j=1;j<=num;j++)
            result1[i][j]=a[i][j];
    for(k=2;k<=num;k++)
    {
        Matrixmulti(a,c,num,k);
        Matrixplus(result1,c,result2,num);
        for(i=1;i<=num;i++)
            for(j=1;j<=num;j++)
            result1[i][j]=result2[i][j];
    }
    for(i=1;i<=num;i++)
        for(j=1;j<=num;j++)
        {
            if(a[i][j]!=result2[i][j])
            {
                printf("输出传递闭包关系矩阵：\n");
                for(i=1;i<=num;i++)
                {
                    for(j=1;j<=num;j++)
                        printf("%d ",result2[i][j]);
                    putchar('\n');
                }
                printf("因为传递闭包不是本身，所以不满足传递性\n");
                return 0;
            }
        }
    printf("满足传递性\n");
    return 1;
}
int Transmjudge2(Order *a,int m)
{
int i,j,k;
int x,y,z;
int flag=0;
for(i=1;i<=m;i++)
{
	for(j=1;j<=m;j++)
	{
		if(a[i].right==a[j].left)
		{
			for(k=1;k<=m;k++)
			{
				if(a[k].left==a[i].left&&a[k].right==a[j].right)
				{
					break;
				}
			}
			if(k==m+1)
			{
			x=i;y=j;
			flag=1;
			}
		}
		if(flag==1)
			break;
	}
	if(flag==1)
		break;
}
	if(flag)
	{
	printf("不满足传递性，<%d,%d><%d,%d>传递不出<%d,%d> \n",a[x].left,a[x].right,a[y].left,a[y].right,a[x].left,a[y].right);
	}
	else
	{
	printf("满足传递性\n");
	}

return 1;
}
















