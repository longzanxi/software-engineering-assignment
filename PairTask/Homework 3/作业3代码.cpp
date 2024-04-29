#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<conio.h>


typedef struct Node{
    int data;
    struct Node *pre,*next;
}Node,*DLinkList;

void InitDLinkList(DLinkList &L)//��ʼ��һ��˫��ѭ������
{
	//��ͷ���������ķ��Ŵ��������ķ���
	//�����ֵ��ʾԪ�ؽ����Ŀ
	L=new Node;
	L->data=0;
	L->next=L;
	L->pre=L;
}

void InsertNode(DLinkList &L,int x)//������β������һ��ֵΪx�Ľ��
{
	DLinkList p=new Node;
	DLinkList q=L->pre;
	p->data=x;
	p->next=L;
	p->pre=q;
	q->next=p;
	L->pre=p;
	if(L->data>=0)L->data++;
	else L->data--;
}

void DeleteNode(DLinkList &L)//ɾȥ����β�ڵ㼴��λ
{
	if(L->data==0)return;
	DLinkList p=L->pre;
	DLinkList q=p->pre;
	q->next=L;
	L->pre=q;
	free(p);
	if(L->data>=0)L->data--;
	else L->data++;
}

void Adjust(DLinkList &L)//��һ��������е���
{
	DLinkList p=L->next;
	while(p!=L)
	{
		while(p->data>9999)//�����λ
		{
			if(p->next==L)InsertNode(L,0);
			p->next->data+=p->data/10000;
			p->data%=10000;
		}
		p=p->next;
	}
	while(L->pre->data==0&&abs(L->data)>1)DeleteNode(L);//����ǰ����
}	

int CompareNum(DLinkList a,DLinkList b)//�Ƚ��������ľ���ֵ��Сa>b����1 a=b����2 a<b����0
{
	if(abs(a->data)!=abs(b->data))
	{
				if(abs(a->data)>abs(b->data))return 1;

		else return 0;
	}
	DLinkList p=a->pre,q=b->pre;
	while(p!=a&&q!=b)
	{
		if(p->data!=q->data)
		{
			if(p->data>q->data)return 1;
			else return 0;
		}
		p=p->pre;
		q=q->pre;
	}
	return 2;
}	

void BigAdd(DLinkList a,DLinkList b,DLinkList &c)//a+b=c
{
	if(a->data*b->data>0)//abͬ��
	{
		DLinkList p=a->next,q=b->next;
		while(p!=a&&q!=b)
		{
			InsertNode(c,p->data+q->data);
			p=p->next;
			q=q->next;
		}
		while(p!=a)
		{
			InsertNode(c,p->data);
			p=p->next;
		}
		while(q!=b)
		{
			InsertNode(c,q->data);
			q=q->next;
		}
		if(a->data<0)c->data=-c->data;
	}
	else
	{
		switch(CompareNum(a,b))
		{
			case 2://a==b abs
				InsertNode(c,0);
				return;
			case 1://a>b
			{
				DLinkList p=a->next,q=b->next;
				while(p!=a&&q!=b)
				{
					if(p->data<q->data)//�����������Ͻ�λ
					{
						p->next->data--;
						p->data+=10000;
					}
					InsertNode(c,p->data-q->data);
					p=p->next;
					q=q->next;
				}
				while(p!=a)
				{
					InsertNode(c,p->data);
					p=p->next;
				}
				if(a->data<0)c->data=-c->data;//����ֵ�ϴ���ȷ������
				break;				
			}

			case 0://a<b
			{
				DLinkList p=a->next,q=b->next;
				while(p!=a&&q!=b)
				{
					if(q->data<p->data)//�����������Ͻ�λ
					{
						q->next->data--;
						q->data+=10000;
					}
					InsertNode(c,q->data-p->data);
					p=p->next;
					q=q->next;
				}
				while(q!=b)
				{
					InsertNode(c,q->data);
					q=q->next;
				}
				if(b->data<0)c->data=-c->data;
				break;	
			}
		}
	}
	Adjust(c);//�����λ
}

void BigSub(DLinkList a,DLinkList b,DLinkList &c)//a-b=a+(-b)=c
{
	b->data=-b->data;
	BigAdd(a,b,c);
	b->data=-b->data;
}




int GetBigNum(DLinkList &L)//��ȡһ����
{
	char nnn[100005];
	int sum=0;
	scanf("%[^\n]",nnn);
	getchar();
	for(int i=0;i<strlen(nnn);i++)//������ַ����ֲ�����λ����������
		if(!(i==0&&(nnn[0]=='-'||nnn[0]=='+'))&&(!(nnn[i]>='0'&&nnn[i]<='9')))
			return 0;
	int j=0;
	for(int i=strlen(nnn)-1;i>=0;i--)//����������������ÿ��λΪһ����λ��������ڵ����������
	
	{
		if(nnn[i]>='0'&&nnn[i]<='9')
		{
			j++;
			if(j==4||i==0||(i==1)&&nnn[0]=='-')
			{
				int sum=0;
				for(int k=i;k<i+j;k++)sum=10*sum+(nnn[k]-'0');
				InsertNode(L,sum);
				j=0;
			}
		}
	}
	if(nnn[0]=='-')
		L->data=-L->data;//���Ϊ����,�������������ȡ��
	if(L->data==0)return 0;
	Adjust(L);
	return 1;
}
void PrintResult(DLinkList &L)//���
{
	DLinkList p=L->pre;
	if(L->data<0)printf("-");
	while(p!=L)
	{
		if(p->next!=L)printf("%04d",p->data);
		else printf("%d",p->data);
		if(p->pre!=L)printf(",");
		p=p->pre;
	}
	printf("\n");
}






int main()
{
    DLinkList a,b,c;
    InitDLinkList(a);
    InitDLinkList(b);
    InitDLinkList(c);
    printf("�����һ����������Ĵ�����A,�Իس�����\n");
    if(!GetBigNum(a)){printf("�����\n");return 0;}
	//debug(a);
	//PrintResult(a);
    printf("����ڶ�����������Ĵ�����B,�Իس�����\n");
    if(!GetBigNum(b)){printf("�����\n");return 0;}
    printf("ѡ�����㷽ʽ\n");
	printf("�ӷ�������'+'\n");
	printf("����������'-'\n");
	char op=getch();
	if(op=='+')
{printf("A + B = ");
			BigAdd(a,b,c);
			PrintResult(c);
			}
else
	if(op=='-')
	{printf("A - B = ");
			BigSub(a,b,c);
			PrintResult(c);
			}
	else
		{printf("�����\n");return 0;}

	system("pause");
	return 0;
	
}





