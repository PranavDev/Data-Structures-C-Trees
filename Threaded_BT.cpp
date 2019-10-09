# include<stdio.h>
# include<stdlib.h>
# define MAX 50

struct TBT
{
	int info;
	struct TBT *lchild;
	struct TBT *rchild;
	bool lthread;
	bool rthread;
}*root,*root1,*p,*M,*ptr,*temp,*parent,*P,*Q,*C;

struct TBT *Stack[MAX];
int top;
int Empty();
struct TBT *pop();
struct TBT *push(struct TBT *P);
struct TBT *CreateTree(struct TBT *root1,int data);

struct TBT *InOrder_CreateTree(struct TBT *root,int data);

void InOrder(struct TBT *root);

struct TBT *InOrder_successor(struct TBT *ptr);

void PostOrder(struct TBT *ptr);

int main()
{
	int N,data,i,j,top=-1,k=0,a[50];
	
	printf(">> Threaded Binary Tree >>\n\n\n");
	
	printf("Enter the No. of Nodes : ");
	scanf("%d",&N);
	
	root = (struct TBT *)malloc(sizeof(struct TBT));
	root->lchild = NULL;
	root->rchild = NULL;
	root->lthread = true;
	root->rthread = true;
	
	printf("Enter the data for the root node : ");
	scanf("%d",&data);
	root->info = data;
	a[k] = root->info;
	
	for(i=0;i<N-1;i++)
	{
		printf("Enter the data for the %d node : ",i+1);
		scanf("%d",&data);
		a[++k] = data;
		M = InOrder_CreateTree(root,data);
	}
	
	printf("\n\nThe Created Threaded Binary Tree is (In-Order Traversal): \n\n");
	
	InOrder(M);
	
	printf("\n\n**************************************************************\n\n");
	
	root1 = (struct TBT *)malloc(sizeof(struct TBT));
	root1->info = a[0];
	root1->lchild = NULL;
	root1->rchild = NULL;
	
	for(j=1;j<=k;j++)
	{
		C = CreateTree(root1,a[j]);
	}
	
	printf("\n\nThe Created Threaded Binary Tree is (Post-Order Traversal): \n\n");
	
	PostOrder(C);
	
	printf("\n\n**************************************************************\n\n");
	
	return 0;
}



struct TBT *InOrder_CreateTree(struct TBT *root,int data)
{
	ptr = root;
	p = root;
	parent = NULL;
	
	while(ptr!=NULL)
	{
		parent = ptr;
		
		if(data < ptr->info)
	    {
		    ptr = ptr->lchild;
	    }
	    else if(data > ptr->info)
	    {
		    ptr = ptr->rchild;
	    }
	    else
	    {
		    printf("This Data %d already Exists and Cannot be Added to the Tree!\n\n",data);
		    return root;
	    }
	}
	
	temp = (struct TBT *)malloc(sizeof(struct TBT));
	temp->info = data;
	temp->lchild = NULL;
	temp->rchild = NULL;
	temp->lthread = true;
	temp->rthread = true;
	
	if(parent==NULL)
	{
		root = temp;
	}
	else if(data < parent->info)
	{
		parent->lchild = temp;
		parent->lthread = false;
		temp->rchild = parent;
	}
	else
	{
		temp->rchild = parent->rchild;
		parent->rchild = NULL;
		parent->rchild = temp;
		//temp->rchild = p;
		parent->rthread = false;
	}
	return root;
}


void InOrder(struct TBT *root)
{
	ptr = root;
	int count = 0;
	
	if(root==NULL)
	{
		printf("Empty Tree\n");
	}
	
	while(ptr->lthread==false)
	{
		ptr = ptr->lchild;
	}
	
	while(ptr!=NULL)
	{
		if(ptr==root)
		{
			count++;
			if(count==2)
			{
				break;
			}
		}
		printf("%d ",ptr->info);
		ptr->lthread = true;
		ptr = InOrder_successor(ptr);
	}
}


struct TBT *InOrder_successor(struct TBT *ptr)
{
	if(ptr->rthread==true)
	{
		return ptr->rchild;
	}
	else
	{
		ptr = ptr->rchild;
		
		while(ptr->lthread==false)
		{
			ptr = ptr->lchild;
		}
		return ptr;
	}
}


void PostOrder(struct TBT *ptr)
{
	P = ptr;

	if(P==NULL)
	{
		printf("Empty Tree!\n");
		return;
	}
	while(P!=NULL)
	{
	    while(P->lchild!=NULL)
	    {
		    push(P);
		    P = P->lchild;
	    }
	
	    while(P->rchild==NULL || P->rchild==Q)
	    {
		    printf("%d ",P->info);
		    Q = P;
		
		    if(Empty())
		    {
			    return;
		    }
		
		    P = pop();
	    } 
	    push(P);
	    P = P->rchild;
	}
}//Post_Order() closes

//Push() function 
struct TBT *push(struct TBT *P)
{
	if(top==MAX-1)
	{
		printf("\n\nStack Full!\n");
	}
	else
	{
		top++;
		Stack[top] = P;
	}
}//closing of push()

//Pop() function
struct TBT *pop()
{
	if(top==-1)
	{
		printf("\n\nStack Empty!\n");
	}
	else
	{
		P = Stack[top];
		top--;
		return P;
	}
}//closing of pop()

//Empty Stack checking function
int Empty()
{
	if(top==-1)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}


struct TBT *CreateTree(struct TBT *root1,int data)
{
	ptr = root1;
	parent = NULL;
	
	while(ptr!=NULL)
	{
		parent = ptr;
		
		if(data < ptr->info)
		{
			ptr = ptr->lchild;
		}
		else if(data > ptr->info)
		{
			ptr = ptr->rchild;
		}
		else
		{
			printf("This Data %d already Exists and Cannot be Added!\n\n",data);
			return root1;
		}
	}
	
	temp = (struct TBT *)malloc(sizeof(struct TBT));
	temp->info = data;
	temp->lchild = NULL;
	temp->rchild = NULL;
	if(parent==NULL)
	{
		root1 = temp;
	}
	else if(data < parent->info)
	{
		parent->lchild = temp;
	}
	else
	{
		parent->rchild = temp;
	}
	return root1;
}//Create() closes


