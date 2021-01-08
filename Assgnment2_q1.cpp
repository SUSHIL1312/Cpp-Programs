/*					
					Name:SUSHIL KUMAR
					To be compiled in :LINUX g++
*/

/*
		Q1. Implementation of Queue with the help of two stack.
			In this program I am accepting size of stacks to be used by the user.

*/

#include<iostream>
#include<limits>
using namespace std;
/*
	making STACK class which contains size,arr[]and top as member variable and 
	push(),pop(),isEmpty(),isFull()and display() as its' member function.
*/
class STACK{
public:
	static int size;
	//top variable as stack pointer which always points to the top of stack.
	int top;
	//declaring a storage space dynamically for storing the stack elements.
	int *arr=new int[size];

	//constructor for class stack.
	STACK(){
		//initializing the top to -1 .
		top=-1;
	}
/*
	Push() of stack,takes an element and put it  at the 
		top of the STACK.
*/
	void push(int val){
		if(top==size-1){
			//cout<<"Stack overflow"<<endl;
			return;
		}
		else{
		
				arr[++top]=val;
		}
	}
/*
	display() helps in viewing the current elements in the stack(from top to bottom);
*/
	void display(){
		int i;
		if(top==-1)
			return;
		else{
			for(i=top;i>=0;i--)
				cout<<arr[i]<<" ";
			
		}
	}
/*
	pop() helps in removing the top element from the STACK.
*/
	int pop(){
		int val;
		if(top==-1){
			return -1;
		}
		else{
			val=arr[top];
			top--;
			return val;
		}
	}
/*
	isEmpty() helps in checking whether the stack is empty or not.
*/
	bool isEmpty(){
		if(top==-1)
			return true;
		else
			return false;
	}
/*
	isFull() helps in checking whether the stack is ful or not.
*/
	bool isFull(){
		if(top==size-1)
			return true;
		else
			return false;
	}


};

int STACK ::size;
/*
	making two object of class STACK i.e stack1 and stack2 which will be used in implemention of Queue.
*/
STACK stack1;
STACK stack2;

/*
	insert()basically helps in inserting elements in the Queue.
	All the insertion have taken place in stack1.If stack1 is empty then directly insert element to stack1,
	but if stack1 is full then check stack2 is empty or not.
	If stack2 is empty then transferred all the stack1 elements to stack2 and then inseted element ot stack1,
	but if stack2 is also not empty,then insetion has been blocked.
*/
void insert(STACK &stack1,STACK &stack2,int num){
	//checking whether stack1 is full.
	 	if(stack1.isFull()){
	 		//checking whether stack2 is empty.
	 		if(stack2.isEmpty()){
	 			//transferring stack1 elements to stack2.
	 			while(!stack1.isEmpty()){
	 				stack2.push(stack1.pop());
	 			}
	 		}
	 		else{
	 			cout<<"Queue is Full....\nInsertion Blocked.."<<endl;
	 			return;
	 		}
	 
	 	stack1.push(num);
	 	}
	 	
	 	else
	 	stack1.push(num);
 }

 /*
	deletes() basically helps in removing the elements from the queue.
	All the removal of elements occured form stack2.If stack2 is not empty then direcly remove 
	elements from the stack2,but if stack2 is empty then transfer all elements from stack1 to 
	stack2 and then perform deletion.But if stack1 is also empty then deletion blocked. 
 */

 int deletes(STACK &stack1,STACK &stack2){
 	//checking stack2 is empty or not.
 	if(stack2.isEmpty()){
 		//checking stack1 is empty or not.
 			if(stack1.isEmpty()){
 				return -1;
 			}else{
 				//transferring stack1 elements to stack2.
 				while(!stack1.isEmpty()){
 					stack2.push(stack1.pop());
 				}
 				return(stack2.pop());
 			}

 		}
 		else{
 			return(stack2.pop());
 		}
 }

int main(){
	int length;
	cout<<"Enter the size of Stack to be used :";
	cin>>length;
	STACK::size=length;
	cout<<"\n************Welcome to the Queue Program******************"<<endl;
	cout<<"\nChoose your desired option from the list     :"<<endl;
	cout<<"For entering elements in Queue:..................... 1"<<endl;
	cout<<"For deleting elements from the Queue:............... 2"<<endl;
	cout<<"For displaying the current elements in the Queue:... 3"<<endl;
	cout<<"For terminating the program:........................ 4"<<endl;
	cout<<"\n************************************************************"<<endl;
	while(1){
		cout<<"Choose your option from the list :";
		int choice;
		cin>>choice;
		while(cin.fail()) {
		    cin.clear();
		    cin.ignore(numeric_limits<streamsize>::max(),'\n');
		    cout << "Bad entry.\nEnter choice again: ";
		    cin >> choice;
		}
		switch(choice){
			case 1:
			{	
				/*for calling insert function of queue.*/
				int data;
				cout<<"Enter the element: ";
				cin>>data;
				insert(stack1,stack2,data);
				break;
			}
			case 2:
			{	
				/*for calling deletes() of queue.*/
				int data;
				if(stack1.isEmpty() && stack2.isEmpty()){
					cout<<"Cannot remove items.\nQueue is already Empty..."<<endl;
					break;
				}else{
					data=deletes(stack1,stack2);
					cout<<"Element removed from Queue is :"<<data<<endl;
				break;
				}	
			}
			case 3:
			{
				/*for displaying the elements in the stacks of the queue.*/
				cout<<"elements in the Queue are :"<<endl;
				if(!stack1.isEmpty() && !stack2.isEmpty())
				{	cout<<"\tin Stack2 :";
					stack2.display();
					cout<<"\n\tin Stack1 :";
					stack1.display();
				}
				else if(!stack1.isEmpty()){
						cout<<"\tin Stack1 :";
						stack1.display();}
					else if(!stack2.isEmpty()){
						cout<<"\tin Stack2 :";
						stack2.display();
					}
					else
						cout<<"Queue is Empty."<<endl;
				cout<<endl;
				break;
			}
			case 4:
			{	/*for termination of program.*/
				cout<<"\t\tterminating the program.\n\t\t******Good Bye!!!******"<<endl;
				exit(0);
			}
			default:{
				cout<<"Choose correct option from the list"<<endl;
			}

		}
	}

	
	return 0;
}
