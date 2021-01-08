/*			Name: Sushil kumar
			Assignment :Josephus Problem)
			Platform: To be compiled in Linux Terminal


*/
/*
	Question:	Implement Josephus Problem using circular linked list. Let n be the number
			of persons standing in a circle facing the center, let k be a skip number agreed
			upon in advance and let A be the person who begins the process. On each
			iteration, x will kill kth person on the left, where x begins with A and is reset
			to be the person on the left of the person killed each time. For example if n=10
			(A, B, C, D, E, F, G, H, I, J) and k=3, then A kills D, E kills H, I kills B, C
			kills G, etc.. Your program will accept n and k as input from the user. Output
			the order of execution and the number of links traversed till the program terminates. 
*/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
/*defining a node using structure which holds interger data and a self-referencing pointer "next"*/
struct node{
	int data;
	struct node *next;
	
};

/*
	createNode is a function which takes a value as argument and create a new node and return it's address.
*/

struct node* createNode(int value){
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	/*
		temp will be NULL when the heap memory will be full, as malloc allocate memory space in heap segment.
	*/
	if(temp==NULL){
		printf("Memory full.\nProgram Terminating.......\n");
		exit(1);
	}
	temp->data=value;
	temp->next=temp;
	return temp;
}
/*
	insertEnd() takes takes two argument one value to be inserted and other the pointer to he head element.
	further it calls createNOde() which returns the address of new node created,now insertEnd() will insert 
	new node to the end of the linked list.
*/
struct node* insertEnd(int val,struct node *head){
	struct node *temp=createNode(val);
	if(head==NULL)
		head=temp;
	else{
		struct node *p;
		p=head;
		while(p->next !=head)
			p=p->next;
		p->next=temp;
		temp->next=head;
		//head=temp;
		p=NULL;
	}
	temp=NULL;
	return head;
}

/*
	circularListLen() will count the number of nodes present in the circular linked list and returns the length.
*/
int cicularListLen(struct node *head){
	int count=0;
	if(head==NULL)
		return 0;
	count=1;
	struct node *p;
	p=head;
	while(p->next!=head){
		p=p->next;
		count++;
	}
	return count;
}
/*
	display() will print all the elements value present in the list starting from the head element,which it has received 
	as argument .
*/
void display(struct node *head){
	struct node *p;
	p=head;
	if(head==NULL)
		printf("list empty..");
	else{
	do{
		printf("%d  ",p->data);
		p=p->next;
	}while(p->next!=head);
	printf("%d",p->data);
	}
}

/*
	killPerson() takes two argument , first k(i.e kth person to kill from the current person) and 
	second the pointer to the current/head pointer(in this program head will always be pointing to 
	the person which will kill other).
*/
void killPerson(int k,struct node* head){
	int i,val;
	/*count will store the value of total link travelled.*/
	int count=0;
	/*temp_count is just a temp variable which will only store count value when n<=k and
	 futher add that to count.
	*/
	int temp_count=0;
	/*
		loop till head is not null.
	*/
	while(head!=NULL){
		struct node *p=head;
		struct node *q=head;
		printf("\n %d Kills ",head->data);
		int n=cicularListLen(head);
		/*
				this for loop help in reaching to the kth person from head, which will be killed.
		*/
		for(i=k;i>0;i--){
			p=q;
			q=q->next;
			if(k<n)
				count++;
			/*
				when if condition fails i.e (k>=n) now perform modulo count operation.
			*/
			else
			{
				temp_count++;

			}
		}

		/*
			adding the value fo temp_count%n to the count value(performing modulo count ),and setting temp_count 
			to zero again.
		*/
		if(k>=n){
			count=count+temp_count%n;
			temp_count=0;

		}

		val=q->data;
		p->next=q->next;
		head=p->next;
		/*
			here count value is updated as after killing the kth person the sword will be passed to the 
			(k+1)th person,for the game to be continue.
		*/
		count++;
		free(q);
		q=NULL;
		printf("%d \n",val);
		//printf("count %d.\n",count);
		p=NULL;
		/*this if statement will only execute when only one elements left.*/
		if(cicularListLen(head)==1){
			printf("last man left : %d\n",head->data);
			printf("\n Total link travelled is :%d\n",count);
			return;
		}
		printf("Remaining men: ");
		display(head);
		
		
		
	}
}
int main(){
	int n,k,i;
	printf("\n************Welcome to Josephus problem *********************\n\n");
	int limit=3;
	while(limit){
		limit--;
		printf("Enter number of people present(n>0) :");
		scanf("%d",&n);
		printf("Enter skip number(k>0) :");
		scanf("%d",&k);
		if(k>0 && n >0)
			break;
		else
			printf("invalid entry..\n Try again..\n you have %d chance Remaining.\n",limit);
		if(limit==0)
		{
			printf("Terminating the program..\n");
			return 0;
		}
}
	struct node *head=NULL;
/*
	calling the insertEnd(),n-times using for loop so, that we can insert n elements in circular list.
*/	
	for(i=0;i<n;i++){
		head=insertEnd(i+1,head);
	}
	printf("Persons standing in a circle & facing the center are :\n");
	printf("\t");
	display(head);
/*
	calling the killPerson() which will tell us who kills whome and total link travelled in this process.
*/
	printf("\nGame begins.....\n");
	killPerson(k,head);
	printf("\n**************** Terminating the program ***********************\n");

}


