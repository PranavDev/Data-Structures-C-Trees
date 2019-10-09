# include<stdio.h>
# include<stdlib.h>
# include<math.h>
# define MAX 50

struct BST_node
{
	int data;
	struct BST_node *lchild;
	struct BST_node *rchild;
}*root1,*P,*temp,*parent,*Q,*ptr,*M,*D,*p; //Structure pointers

struct BST_node *push(struct BST_node *P);
struct BST_node *pop();
struct BST_node *Stack[MAX];
int Empty();

int top;

struct BST_node *CreateTree(struct BST_node *root1,int data);

struct BST_node *Delete(struct BST_node *root1,int key);

struct BST_node *del_parent_with_two_children(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr);

struct BST_node *del_leaf_node(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr);

struct BST_node *del_parent_with_one_child(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr);

struct BST_node *del_leaf_node(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr);

void InOrder_Display(struct BST_node *ptr);

void PreOrder_Display(struct BST_node *ptr);

void PostOrder_Display(struct BST_node *ptr);

//Driving Main()
int main()
{
	int N,i,j,data,info;
	int key;
	int ch;
	top = -1;
	
	printf("Enter the No. of Elements You Wish To Enter : ");
	scanf("%d",&N);
	
	printf("\n\n");
	
	root1 = (struct BST_node *)malloc(sizeof(struct BST_node));
	printf("Enter the data for the Root node : ");
	scanf("%d",&root1->data);
	root1->lchild = NULL;
	root1->rchild = NULL;
	
	for(i=0;i<N-1;i++)
	{
		printf("Enter the data for the Node %d : ",i+1);
		scanf("%d",&data);
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
	
	printf("\n\n***********************************************************************\n\n");
    
    while(1)
    {
    	printf("1.Deleting Nodes : \n\n");
        printf("2.Exit\n\n");
        printf("Enter your choice : ");
        scanf("%d",&ch);
        
    	switch(ch)
    	{
    		case 1 : printf("\n\n**************************************************************\n\n");
			         printf("You Chose : Deleting nodes\n\n");
    		         printf("Enter a Node you want to Delete : ");
                     scanf("%d",&key);
    
                     D = Delete(root1,key);
    
                     printf("\n\n>> The Binary Search Tree Display After Deletion >>");
	
	                 printf("\n\nThe New Binary Search Tree is (In-Order Traversal) : \n\n");
	                 InOrder_Display(D);
	
	                 printf("\n\nThe New Binary Search Tree is (Pre-Order Traversal) : \n\n");
	                 PreOrder_Display(D);
	
	                 printf("\n\nThe New Binary Search Tree is (Post-Order Traversal) : \n\n");
                     PostOrder_Display(D);
                     printf("\n\n**************************************************************\n\n");
                     break;
                              
            case 2 : exit(1);
                     break;
                     
            default : printf("Wrong Choice\n\n");
                      break;
	    } 
    }
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


struct BST_node *Delete(struct BST_node *root1,int key)
{
	ptr = root1;
	parent = NULL;
	
	while(ptr!=NULL)
	{
		if(ptr->data==key)
		{
			break;
		}
		parent = ptr;
		if(key < ptr->data)
		{
			ptr = ptr->lchild;
		}
		else
		{
			ptr = ptr->rchild;
		}
	}
	
	if(ptr==NULL)
	{
		printf("Key not present in the Tree\n\n");
	}
	else if(ptr->lchild!=NULL && ptr->rchild!=NULL)
	{
		root1 = del_parent_with_two_children(root1,parent,ptr);
	}
	else if(ptr->lchild!=NULL)
	{
		root1 = del_parent_with_one_child(root1,parent,ptr);
	}
	else if(ptr->rchild!=NULL)
	{
		root1 = del_parent_with_one_child(root1,parent,ptr);
	}
	else
	{
		root1 = del_leaf_node(root1,parent,ptr);
	}
	return root1;
}


struct BST_node *del_parent_with_one_child(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr)
{
	struct BST_node *child;

	if(ptr->lchild!=NULL)
	{
		child = ptr->lchild;
	}
	else if(ptr->rchild!=NULL)
	{
		child = ptr->rchild;
	}
	
	if(parent==NULL)
	{
		root1 = child;
	}
	else if(parent->lchild==ptr)
	{
		parent->lchild = child;
	}
	else 
	{
		parent->rchild = child;
	}
	free(ptr);
	return root1;
}


struct BST_node *del_leaf_node(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr)
{
	if(parent==NULL)
	{
		root1 = NULL;
	}
	else if(parent->lchild==ptr)
	{
		parent->lchild = NULL;
	}
	else if(parent->rchild==ptr) 
	{
		parent->rchild = NULL;
	}
	free(ptr);
	return root1;
}

struct BST_node *del_parent_with_two_children(struct BST_node *root1,struct BST_node *parent,struct BST_node *ptr)
{
	struct BST_node *child;
	struct BST_node *succ,*parsucc;
	
	parsucc = ptr;
	succ = ptr->rchild;
	
	while(succ->lchild!=NULL)
	{
		parsucc = succ;
		succ = succ->lchild;
	}
	ptr->data = succ->data;
	
	if(succ->lchild==NULL && succ->rchild==NULL)
	{
		root1 = del_leaf_node(root1,parsucc,succ);
	}
	else
	{
		root1 = del_parent_with_one_child(root1,parsucc,succ);
	}
	return root1;
}


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
