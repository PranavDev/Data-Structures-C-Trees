/*Write a Program to create a Binary Search Tree and Display it's Mirror Image with and without disturbing the Original Tree. Also Display
the Height of the Tree using Non-Recursion.*/

# include<stdio.h>
# include<stdlib.h>
# include<math.h>
# define MAX 50

struct BST_node
{
	int data;
	struct BST_node *lchild;
	struct BST_node *rchild;
}*root1,*root2,*P,*temp,*parent,*Q,*ptr,*M,*D,*G,*p; //Structure pointers

struct BST_node *push(struct BST_node *P);
struct BST_node *pop();
struct BST_node *Stack[MAX];
int Empty();
int top;

int count = 0;
int isEven(int count);

struct BST_node *Queue[MAX];
void EnQueue(struct BST_node *ptr);
struct BST_node *DeQueue();
int Queue_Empty();
int front,rear;

struct BST_node *CreateTree(struct BST_node *root1,int data);
struct BST_node *MirrorTree(struct BST_node *root2,int );
struct BST_node *mirror_by_disturbing(struct BST_node *root1);
void HeightTree(struct BST_node *root1);

void InOrder_Display(struct BST_node *ptr);

void PreOrder_Display(struct BST_node *ptr);

void PostOrder_Display(struct BST_node *ptr);

//Driving Main()
int main()
{
	int N,i,j,data,info,a[50],k=0;
	top = -1;
	
	front = -1;
	rear = -1;
	
	printf("Enter the No. of Elements You Wish To Enter : ");
	scanf("%d",&N);
	
	printf("\n\n");
	
	root1 = (struct BST_node *)malloc(sizeof(struct BST_node));
	printf("Enter the data for the Root node : ");
	scanf("%d",&root1->data);
	root1->lchild = NULL;
	root1->rchild = NULL;
	a[k] = root1->data;
	
	for(i=0;i<N-1;i++)
	{
		printf("Enter the data for the Node %d : ",i+1);
		scanf("%d",&data);
		a[++k] = data;
		M = CreateTree(root1,data);
	}

	printf("\n\n");
	printf(">> The Binary Search Tree Display After Creation >>");
	
	printf("\n\nThe Created Binary Search Tree is (In-Order Traversal) : \n\n");
	InOrder_Display(M);
	
	printf("\n\nThe Created Binary Search Tree is (Pre-Order Traversal) : \n\n");
	PreOrder_Display(M);
	
	printf("\n\nThe Created Binary Search Tree is (Post-Order Traversal) : \n\n");
    PostOrder_Display(M);
	
	printf("\n\n***********************************************************************\n");
	
	root2 = (struct BST_node *)malloc(sizeof(struct BST_node));
	root2->data = a[0];
	root2->lchild = NULL;
	root2->rchild = NULL;
	
	for(j=1;j<=k;j++)
	{
		G = MirrorTree(root2,a[j]);
	}
	
	printf("\n\n>> The Mirror Binary Search Tree Without Disturbing >>\n\n");
	
	printf("\n\nThe Created Binary Search Tree is (In-Order Traversal) : \n\n");
	InOrder_Display(G);
	
	printf("\n\nThe Created Binary Search Tree is (Pre-Order Traversal) : \n\n");
	PreOrder_Display(G);
	
	printf("\n\nThe Created Binary Search Tree is (Post-Order Traversal) : \n\n");
    PostOrder_Display(G);
    
    printf("\n\n***********************************************************************\n\n");
    
    printf(">> The Mirror Binary Search Tree After Disturbing (Level-Order Traversal) >>\n\n");
    
    mirror_by_disturbing(root1);
    
    printf("\n\n***********************************************************************\n\n");
    
    printf(">> Height Of The Original Binary Search Tree >>\n\n");
    HeightTree(root1);
    
    printf("\n\n***********************************************************************\n\n");
    return 0;
}//Main() closes


//Create Function to create a BST
struct BST_node *CreateTree(struct BST_node *root1,int data)
{
	ptr = root1;
	parent = NULL;
	
	while(ptr!=NULL)
	{
		parent = ptr;
		
		if(data < ptr->data)
		{
			ptr = ptr->lchild;
		}
		else if(data > ptr->data)
		{
			ptr = ptr->rchild;
		}
		else
		{
			printf("This Data %d already Exists and Cannot be Added to a BST!\n\n",data);
			return root1;
		}
	}
	
	temp = (struct BST_node *)malloc(sizeof(struct BST_node));
	temp->data = data;
	temp->lchild = NULL;
	temp->rchild = NULL;
	if(parent==NULL)
	{
		root1 = temp;
	}
	else if(data < parent->data)
	{
		parent->lchild = temp;
	}
	else
	{
		parent->rchild = temp;
	}
	return root1;
}//Create() closes


//Height Function()
void HeightTree(struct BST_node *root1)
{
	double h;
	double NodeCount = 0;
	
	P = ptr;
	P = root1;
	
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
		    printf("%d ",P->data);
		    NodeCount++;
		    Q = P;
		
		    if(Empty())
		    {
			    printf("\n\nThe No. of Nodes in the BST are : %lf\n\n",NodeCount);
			    h = ceil((NodeCount-1)/2.0);
			    printf("Height of the BST : %lf",h);
		    }
		    if(!Empty())
		    {
		    	P = pop();
			}
			else
			{
				return;
			}
	    } 
	    push(P);
	    P = P->rchild;
    }
}
//Height() closes

//Mirror by Disturbing the Tree
struct BST_node *mirror_by_disturbing(struct BST_node* root1) 
{ 
  ptr = root1;
  
  if(ptr==NULL)
  {
  	printf("Tree Empty\n");
  	return 0;
  }
  
  EnQueue(ptr);
  
  while(!Queue_Empty())
  {
  	ptr = DeQueue();
  	
  	printf("%d ",ptr->data);
  	
  	if(ptr->lchild!=NULL)
  	{
  		EnQueue(ptr->lchild);
	}
	if(ptr->rchild!=NULL)
	{
		EnQueue(ptr->rchild);
	}
  }
} //function closes


//EnQueue() function
void EnQueue(struct BST_node *ptr)
{
	if(rear==MAX-1)
	{
		printf("Queue Full\n");
		return;
	}
	else if(front==-1 && rear==-1)
	{
		front++;
		rear++;
		count++;
		Queue[rear] = ptr;
	}
	else
	{
		count++;
		rear = rear + 1;
	    Queue[rear] = ptr;
	}
}//EnQueue() closes

//DeQueue Function()
struct BST_node *DeQueue()
{
	if(front==rear+1 || front==-1)
	{
		printf("Queue Empty\n");
		return 0;
	}
	else
	{
		if(Queue[front]!=NULL && Queue[front+1]!=NULL && isEven(count))
		{
			temp = Queue[front];
			Queue[front] = Queue[front+1];
			Queue[front+1] = temp;
			ptr = Queue[front];
			front = front + 1;
			count--;
		}
		else
		{
			ptr = Queue[front];
			front = front + 1;
			count--;
		}
		if(front==rear+1)
		{
			front = -1;
			rear = -1;
		}
		return ptr;
	}
}//DeQueue() closes


int Queue_Empty()
{
	if(front==-1 || front==rear+1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int isEven(int count)
{
	if(count%2==0  && count!=0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//Mirror Without Disturbing Function()
struct BST_node *MirrorTree(struct BST_node *root2,int info)
{
	ptr = root2;
	parent = NULL;
	
	while(ptr!=NULL)
	{
		parent = ptr;
		
		if(info < ptr->data)
		{
			ptr = ptr->rchild;
		}
		else if(info > ptr->data)
		{
			ptr = ptr->lchild;
		}
		else
		{
			printf("This Data %d Already Exists and Cannot be Added to a BST!\n\n",info);
			return root2;
		}
	}
	
	temp = (struct BST_node *)malloc(sizeof(struct BST_node));
	temp->data = info;
	temp->lchild = NULL;
	temp->rchild = NULL;
	if(parent==NULL)
	{
		root2 = temp;
	}
	else if(info < parent->data)
	{
		parent->rchild = temp;
	}
	else
	{
		parent->lchild = temp;
	}
	return root2;
}//Mirror Without Disturbing Function() closes


//Function to Display the Tree in In-Order
void InOrder_Display(struct BST_node *ptr)
{
	P = ptr;
	
	if(P==NULL)
	{
		printf("Tree is Empty\n");
		return;
	}
	
	while(P!=NULL)
	{
		while(P->lchild!=NULL)
		{
			push(P);
			P = P->lchild;
		}
		
		while(P->rchild==NULL)
		{
			printf("%d ",P->data);
			if(!Empty())
			{
				P = pop();
			}
			else
			{
				return;
			}
		}
		printf("%d ",P->data);
		P = P->rchild;
	}
}//InOrder() closes


//Function to display the Tree in Pre-Order
void PreOrder_Display(struct BST_node *ptr)
{
	P = ptr;
	
	if(P==NULL)
	{
		printf("Empty Tree!\n");
		return;
	}
	
	push(P);
	
	while(!Empty())
	{
		P = pop();
		printf("%d ",P->data);
		
		if(P->rchild!=NULL)
		{
			push(P->rchild);
		}
		
		if(P->lchild!=NULL)
		{
			push(P->lchild);
		}
	}
}//Pre-Order closes


//Function to display the Tree in Post-Order
void PostOrder_Display(struct BST_node *ptr)
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
		    printf("%d ",P->data);
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
struct BST_node *push(struct BST_node *P)
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
struct BST_node *pop()
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
