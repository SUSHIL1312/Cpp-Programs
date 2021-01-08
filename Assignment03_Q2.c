/*
			Assignment : Merge Sort using linked list
			Name :Sushil Kumar
			
			Platform: To be compiled in Linux Terminal(gcc 204101057_Assign03_Q2_XXX.c followed by ./a.out)


*/
/*
		Question: In your study material I had given you a O(nlogn) merge-sort program in
				which I had used three intermediate arrays P[ ], Q[ ] and R[ ] for the merging
				operation. In this assignment you are supposed to rewrite both merge and
				merge-sort functions without using additional intermediate storage.
				(Hint: Use ordered linked representation of the data elements) 
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
	addNode() takes the reference to te head node of the list and create a new node & add that node 
	at the end of the linked list.
*/
void addNode(struct node ** head_ref,int value){
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL){
		printf("Memory full...");
		return;
	}
	temp->data=value;
	temp->next=NULL;
	/*
		when the list is empty, then simply add new node to the head of the list.
	*/
	if(*head_ref==NULL){
		*head_ref=temp;

	}
	else{
		/*
			when the list is not empty then traversing to the end of the list and adding the new node there.
		*/
	struct node *p=*head_ref;
	while(p->next!=NULL)
		p=p->next;
	p->next=temp;
	}
}
/*
	display() will help in viewing all the elements present in the list starting from the head of the list.
*/
void display(struct node *head_ref){
	
	if(head_ref==NULL){
		printf("list is empty..\n");
		return;
	}
	struct node *p=head_ref;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	return;

}
/*
		midElementDivision() is a very important utility function in implementing merge sort.
		It is called by myMergeSort().This function basically finds the  middle element in the 
		list and divide the big list into two list of almost equal size(may differ by one element size)
		 whose starting address are stored in first_list and second_list reference variable. 
*/
void midElementDivision(struct node* head,struct node **first_list,struct node **second_list){
	struct node* fast=head;
	struct node* slow=head;
/*
	for finding the middle node,I have taken two pointer of struct node type namely
	fast and slow both initially pointing to head node.Now in each iteration increment
	fast pointer by 2 node and slow pointer by 1 node.At last when the while loop 
	condition fails slow will be pointing to the middle element of the list.
*/
	while(fast!=NULL && fast->next!=NULL&&fast->next->next!=NULL){
		slow=slow->next;
		fast=fast->next->next;
		
	}

	*first_list=head;
	*second_list=slow->next;
	slow->next=NULL;
}
/*
	myMerge() takes the address of the starting node of the two sorted linked list,this function is called 
	by myMergeSort() which recursively arrange all the links of the list so that the elements gets 
	sorted in ascending order.
*/

struct node* myMerge(struct node *p,struct node *q){
	/*will contain the resulant node.*/
	struct node* result_list;
	/*
		This is the base condition of the recursion.
	if first half is empty then simply return second half(i.e pointed by q here) and vice versa*/
	if(p==NULL)
		return(q);
	else if(q==NULL)
				return(p);
	/*
		when both p and q are not NULL, in this case compare the elements value and
		add the smaller node to the resultant node,this will occurs recursively and
		at last we will get the sorted list.
	*/
	if(p->data>=q->data){
		/*
			as q is smaller or equal so add this node to the result_lst and  
			again call myMerge() with q->next and p as argument.
		*/
		result_list=q;
		result_list->next=myMerge(q->next,p);
	}
	else{
		/*
			as p is smaller so add this node to the result_lst and  again call 
			myMerge() with p->next and q as argument.
		*/
		result_list=p;
		result_list->next=myMerge(p->next,q);
	}
	/*finally return the result_list.*/
	return (result_list);
}
/*
		myMergeSort() is the function which implement the Merge Sort ,it does not takes any
		extra memory for storing 2 equal (halves of element as was taken in the Array implementation of merge sort).
		This program basically takes help of two utility fuction i.e. midElementDivision() which helps us in 
		knowing the middle element of the list and knowning the start node of the two halves of the 
		list depending on mid element.myMergeSort() is now called on both halves recusively 
		 and myMerge() which combine two sorted link list halves.
		 This program keep on dividing the whole list till single elements (single element is considered as a sorted list)
		 and then start recursively arranging the links b/w the node and merging the list in sorted order.
*/
void myMergeSort(struct node** head_ref){
	if((*head_ref)->next==NULL|| *head_ref==NULL)
		return;
	else{
		
		struct node *start=*head_ref;
		struct node *list1;
		struct node *list2;
		/*passing the address of list1 and list2 pointer in midElementDivision() which will get 
		  updated by the starting address of 2 halves of the list.
		*/
		midElementDivision(start,&list1,&list2);
		/*
			calling myMergeSort() recursively on list1.
		*/
		myMergeSort(&list1);
		/*
			calling myMergeSort() recursively on list2.
		*/
		myMergeSort(&list2);

		*head_ref=myMerge(list1,list2);
	}

}

int main(){

	/*
		head is a pointer of struct node type which will store the address 
		of the starting node of the linked list.
	*/
	struct node *head=NULL;
	
	int inp_value,n,i;
	printf("*******Welcome to Merge Sort Program *****************\n\n");
	printf("Enter number of elements in list(n>0) :");
	scanf("%d",&n);
	if(n<=0)
	{
		printf("invalid entry of n\nTerminating the program...\n");
		return 0;
	}
	printf("Enter the elements in the list : ");
	for(i=0;i<n;i++){
		scanf("%d",&inp_value);
		addNode(&head,inp_value);
	}
	printf("You have Entered : ");
	display(head);
	/*
		calling the myMergeSort() for sorting the list by passing the address of head pointer as argument.
	*/
	myMergeSort(&head);
	
	printf("Elements after sorting are: ");
	display(head);
	printf("\n****************Terminating the Program***************\n");
}
