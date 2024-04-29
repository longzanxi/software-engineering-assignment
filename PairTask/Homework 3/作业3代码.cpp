#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<conio.h>


typedef struct Node{
    int data;
    struct Node *pre,*next;
}Node,*DLinkList;

void InitDLinkList(DLinkList &L)//初始化一个双向循环链表
{
	//表头结点数据域的符号代表长整数的符号
	//其绝对值表示元素结点数目
	L=new Node;
	L->data=0;
	L->next=L;
	L->pre=L;
}

void InsertNode(DLinkList &L,int x)//在链表尾部插入一个值为x的结点
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

void DeleteNode(DLinkList &L)//删去链表尾节点即高位
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

void Adjust(DLinkList &L)//对一个链表进行调整
{
	DLinkList p=L->next;
	while(p!=L)
	{
		while(p->data>9999)//处理进位
		{
			if(p->next==L)InsertNode(L,0);
			p->next->data+=p->data/10000;
			p->data%=10000;
		}
		p=p->next;
	}
	while(L->pre->data==0&&abs(L->data)>1)DeleteNode(L);//处理前导零
}	

int CompareNum(DLinkList a,DLinkList b)//比较两个数的绝对值大小a>b返回1 a=b返回2 a<b返回0
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
	if(a->data*b->data>0)//ab同号
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
					if(p->data<q->data)//不够减则向上借位
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
				if(a->data<0)c->data=-c->data;//绝对值较大者确定符号
				break;				
			}

			case 0://a<b
			{
				DLinkList p=a->next,q=b->next;
				while(p!=a&&q!=b)
				{
					if(q->data<p->data)//不够减则向上借位
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
	Adjust(c);//处理进位
}

void BigSub(DLinkList a,DLinkList b,DLinkList &c)//a-b=a+(-b)=c
{
	b->data=-b->data;
	BigAdd(a,b,c);
	b->data=-b->data;
}




int GetBigNum(DLinkList &L)//读取一个数
{
	char nnn[100005];
	int sum=0;
	scanf("%[^\n]",nnn);
	getchar();
	for(int i=0;i<strlen(nnn);i++)//如果出现非数字并且首位不是正负号
		if(!(i==0&&(nnn[0]=='-'||nnn[0]=='+'))&&(!(nnn[i]>='0'&&nnn[i]<='9')))
			return 0;
	int j=0;
	for(int i=strlen(nnn)-1;i>=0;i--)//将符合条件的数以每四位为一个单位存入链表节点的数据域中
	
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
		L->data=-L->data;//如果为负号,给链表的数据域取反
	if(L->data==0)return 0;
	Adjust(L);
	return 1;
}
void PrintResult(DLinkList &L)//输出
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
    printf("输入第一个参与运算的大整数A,以回车结束\n");
    if(!GetBigNum(a)){printf("输错啦\n");return 0;}
	//debug(a);
	//PrintResult(a);
    printf("输入第二个参与运算的大整数B,以回车结束\n");
    if(!GetBigNum(b)){printf("输错啦\n");return 0;}
    printf("选择运算方式\n");
	printf("加法请输入'+'\n");
	printf("减法请输入'-'\n");
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
		{printf("输错啦\n");return 0;}

	system("pause");
	return 0;
	
}





