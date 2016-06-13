#include<stdio.h>
struct Order
{
	int right;
	int left;
};
int judgejiao(int x,int y,Order a[],int n);
int judgebing(int x,int y,Order a[],int n);
int main()
{
	int	n;
	int array[30];
	int h,i,j=0;
	int k=0;
	int count=0;
	int x=0;
	int limit;
	int ordernum;
	int flag=0;//是否是有补格的标志
	Order order[100],orde[100];
	scanf("%d",&n);
	//生成n的因数，并储存在array中
	for(i=1;i<=n;i++)
	{
		if(n%i==0)
		{
			array[j]=i;
			j++;
		}
	}
	//判断是否储存成功
	printf("输出数据点:");
	for(i=0;i<j;i++)
		printf("%d ",array[i]);
	printf("\n");
	//用array的数据生成偏序关系
	limit=j;//记录下哈斯图中应该存在的数据点的个数
	for(i=0;i<limit;i++)
	{
		order[k].left=array[i];//从小到大给偏序关系的序偶左元素赋值
		for(j=i+1;j<limit;j++)//循环给序偶的右元素找值
		{
			if(array[j]%array[i]==0)//满足整除关系
			{
				order[k].right=array[j];
				k++;
				order[k].left=array[i];
			}

		}
	}
	//判断生成序偶是否成功
	printf("输出全部整除关系:\n");
	for(i=0;i<k;i++)
		printf("(%d,%d) ",order[i].left,order[i].right);
	printf("\n");
	//复制关系待用
	for(i=0;i<k;i++)
		orde[i]=order[i];
	//对生成的所有偏序关系进行筛选，寻找最终的盖住关系
	ordernum=k;
	for(i=0;i<ordernum;i++)
	{
		for(j=0;j<ordernum;j++)
		{
			if(order[i].right==order[j].left)//找到（x,y）(y,z)
			{
				for(h=0;h<ordernum;h++)//寻找(x,z)
				{
					if(order[h].left==order[i].left&&order[h].right==order[j].right)//判断是否有(x,z)
					{
						order[h].left=0;//标记要消除的序偶
					}
				}
			}
		}
	}
	//判断是否生成成功
	printf("输出筛选后的盖住关系：\n");
	for(i=0;i<ordernum;i++)
	{
        if(order[i].left!=0)//判断标记输出序偶
            printf("(%d,%d)",order[i].left,order[i].right);
	}
	printf("\n");
	//将序偶数组的内容简化
	for(i=0;i<ordernum;i++)
	{
		if(order[i].left==0)//通过标记消除序偶
		{
		    count++;
			for(j=i;j<ordernum-1;j++)
				order[j]=order[j+1];
		}
	}
	//判断是否简化成功
	printf("简化后的盖住关系数组：\n");
	for(i=0;i<ordernum-count;i++)
	{
        if(order[i].left!=0)
            printf("(%d,%d)",order[i].left,order[i].right);
	}
	printf("\n");
	//判断是否为有补格
	for(i=0;i<limit;i++)
	{
		for(j=0;j<limit;j++)//找任意两个数据点x,y
		{
			if((judgebing(array[i],array[j],orde,ordernum)==n)&&(judgejiao(array[i],array[j],orde,ordernum)==1))//判断(x/\y==0,x\/y==1)
			{
				//printf("\n%d %d \n",judgebing(1,6,orde,ordernum),judgejiao(1,6,orde,ordernum));
				//printf("%d的补元是%d\n",array[i],array[j]);
				flag=1;//说明x存在补元
				break;
			}

		}
		if(flag==0)//x不存在补元，输出
        {
            printf("%d不存在补元,所以它不是有补格!\n",array[i]);
            x=1;
            break;
        }
		if(flag==1)//x存在补元，初始化flag，判断下一个x
			flag=0;
	}
	if(!x)
        printf("它是有补元!\n");
	return 0;
}
int judgebing(int x,int y,Order a[],int n)
{
	int i,j;
	if(x!=y){
		for(i=0;i<n;i++)
		{
			if((a[i].left==x&&a[i].right==y)||(a[i].left==y&&a[i].right==x))//如果x,y存在偏序关系
			{
				return a[i].right;//返回较小的数据点
			}
		}
		for(i=0;i<n;i++)
		{
			if(a[i].left==x)//找到以x为左元素的序偶
			{
				for(j=0;j<n;j++)
				{
					if(a[j].left==y)//找到以y为左元素的序偶
					{
						if(a[i].right==a[j].right)//寻找能盖住x,y的数据点
							return a[i].right;
					}
				}
			}
		}
	}
	return 0;
}
int judgejiao(int x,int y,Order a[],int n)
{

	int i,j;
	if(x!=y){
		for(i=0;i<n;i++)
		{
			if((a[i].left==x&&a[i].right==y)||(a[i].left==y&&a[i].right==x))//如果x,y存在偏序关系
			{
				return a[i].left;//返回较大的数据点
			}
		}
		for(i=0;i<n;i++)
		{
			if(a[i].right==x)//找到以x为右元素的序偶
			{
				for(j=0;j<n;j++)
				{
					if(a[j].right==y)//找到以y为右元素的序偶
					{
						if(a[i].left==a[j].left)//寻找能x,y被盖住的数据点
							return a[i].left;
					}
				}
			}
		}
	}
	return 0;
}
