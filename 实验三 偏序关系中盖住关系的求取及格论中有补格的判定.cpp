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
	int flag=0;//�Ƿ����в���ı�־
	Order order[100],orde[100];
	scanf("%d",&n);
	//����n����������������array��
	for(i=1;i<=n;i++)
	{
		if(n%i==0)
		{
			array[j]=i;
			j++;
		}
	}
	//�ж��Ƿ񴢴�ɹ�
	printf("������ݵ�:");
	for(i=0;i<j;i++)
		printf("%d ",array[i]);
	printf("\n");
	//��array����������ƫ���ϵ
	limit=j;//��¼�¹�˹ͼ��Ӧ�ô��ڵ����ݵ�ĸ���
	for(i=0;i<limit;i++)
	{
		order[k].left=array[i];//��С�����ƫ���ϵ����ż��Ԫ�ظ�ֵ
		for(j=i+1;j<limit;j++)//ѭ������ż����Ԫ����ֵ
		{
			if(array[j]%array[i]==0)//����������ϵ
			{
				order[k].right=array[j];
				k++;
				order[k].left=array[i];
			}

		}
	}
	//�ж�������ż�Ƿ�ɹ�
	printf("���ȫ��������ϵ:\n");
	for(i=0;i<k;i++)
		printf("(%d,%d) ",order[i].left,order[i].right);
	printf("\n");
	//���ƹ�ϵ����
	for(i=0;i<k;i++)
		orde[i]=order[i];
	//�����ɵ�����ƫ���ϵ����ɸѡ��Ѱ�����յĸ�ס��ϵ
	ordernum=k;
	for(i=0;i<ordernum;i++)
	{
		for(j=0;j<ordernum;j++)
		{
			if(order[i].right==order[j].left)//�ҵ���x,y��(y,z)
			{
				for(h=0;h<ordernum;h++)//Ѱ��(x,z)
				{
					if(order[h].left==order[i].left&&order[h].right==order[j].right)//�ж��Ƿ���(x,z)
					{
						order[h].left=0;//���Ҫ��������ż
					}
				}
			}
		}
	}
	//�ж��Ƿ����ɳɹ�
	printf("���ɸѡ��ĸ�ס��ϵ��\n");
	for(i=0;i<ordernum;i++)
	{
        if(order[i].left!=0)//�жϱ�������ż
            printf("(%d,%d)",order[i].left,order[i].right);
	}
	printf("\n");
	//����ż��������ݼ�
	for(i=0;i<ordernum;i++)
	{
		if(order[i].left==0)//ͨ�����������ż
		{
		    count++;
			for(j=i;j<ordernum-1;j++)
				order[j]=order[j+1];
		}
	}
	//�ж��Ƿ�򻯳ɹ�
	printf("�򻯺�ĸ�ס��ϵ���飺\n");
	for(i=0;i<ordernum-count;i++)
	{
        if(order[i].left!=0)
            printf("(%d,%d)",order[i].left,order[i].right);
	}
	printf("\n");
	//�ж��Ƿ�Ϊ�в���
	for(i=0;i<limit;i++)
	{
		for(j=0;j<limit;j++)//�������������ݵ�x,y
		{
			if((judgebing(array[i],array[j],orde,ordernum)==n)&&(judgejiao(array[i],array[j],orde,ordernum)==1))//�ж�(x/\y==0,x\/y==1)
			{
				//printf("\n%d %d \n",judgebing(1,6,orde,ordernum),judgejiao(1,6,orde,ordernum));
				//printf("%d�Ĳ�Ԫ��%d\n",array[i],array[j]);
				flag=1;//˵��x���ڲ�Ԫ
				break;
			}

		}
		if(flag==0)//x�����ڲ�Ԫ�����
        {
            printf("%d�����ڲ�Ԫ,�����������в���!\n",array[i]);
            x=1;
            break;
        }
		if(flag==1)//x���ڲ�Ԫ����ʼ��flag���ж���һ��x
			flag=0;
	}
	if(!x)
        printf("�����в�Ԫ!\n");
	return 0;
}
int judgebing(int x,int y,Order a[],int n)
{
	int i,j;
	if(x!=y){
		for(i=0;i<n;i++)
		{
			if((a[i].left==x&&a[i].right==y)||(a[i].left==y&&a[i].right==x))//���x,y����ƫ���ϵ
			{
				return a[i].right;//���ؽ�С�����ݵ�
			}
		}
		for(i=0;i<n;i++)
		{
			if(a[i].left==x)//�ҵ���xΪ��Ԫ�ص���ż
			{
				for(j=0;j<n;j++)
				{
					if(a[j].left==y)//�ҵ���yΪ��Ԫ�ص���ż
					{
						if(a[i].right==a[j].right)//Ѱ���ܸ�סx,y�����ݵ�
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
			if((a[i].left==x&&a[i].right==y)||(a[i].left==y&&a[i].right==x))//���x,y����ƫ���ϵ
			{
				return a[i].left;//���ؽϴ�����ݵ�
			}
		}
		for(i=0;i<n;i++)
		{
			if(a[i].right==x)//�ҵ���xΪ��Ԫ�ص���ż
			{
				for(j=0;j<n;j++)
				{
					if(a[j].right==y)//�ҵ���yΪ��Ԫ�ص���ż
					{
						if(a[i].left==a[j].left)//Ѱ����x,y����ס�����ݵ�
							return a[i].left;
					}
				}
			}
		}
	}
	return 0;
}
