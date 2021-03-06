/*					
					Name:SUSHIL KUMAR
					To be compiled in :LINUX g++
*/
/*
				Question:Write a C/C++ program to create a binary tree having preorder threads. Write
						another program to traverse the tree in preorder using those threads. 
*/
/*
		Creating the preOrder Threaded Binery Tree and Traversing that.
*/
/*
	Instruction for inputing data to the terminal:
		while inserting the input,you will we asked two values for each node.One the data to insert in the node
		and other is the who is the parent of that node.
		If you are inserting value in the Root node, then it's Parent is "-1"
		To any node kindly insert both it's child one by one.
		Insert "-1" for the missing nodes within the tree.
		Note: Kindly donot use "-1" as actual node value as it is being used for representing missing node,while forming 
		tree(-1 will not printed in preOrder and postOrder, it will simply be ignored by the program).
	I am providing some image of tree along with the input sequence,kindly refer to that for more clearity.
		
	*/

#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include<vector>
#include<limits>
using namespace std;
#include <unordered_map>
#include<list>

struct Node{
	int data;
	struct Node *left;
	struct Node *right;
	bool rThread;
};
list<struct Node*> vec;


class STACK{
public:
	static int size;
	//top variable as stack pointer which always points to the top of stack.
	int top;
	//declaring a storage space dynamically for storing the tree node pointers as stack elements.
	struct Node** arr=new struct Node*[size];

	//constructor for class stack.
	STACK(){
		//initializing the top to -1 .
		top=-1;
	}
/*
	myPush() of stack,takes an element and put it  at the 
		top of the STACK.
*/
	void myPush(struct Node *node){
		if(top==size-1){
			//cout<<"Stack overflow"<<endl;
			return;
		}
		else{
		
				arr[++top]=node;
		}
	}
/*
	myPop() helps in removing the top element from the STACK.
*/
	
	struct Node* myPop(){
		struct Node *node;
		if(top==-1){
			return NULL;
		}
		else{
			node=arr[top];
			top--;
			return node;
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
	struct Node* myPeek(){
		struct Node *node;
		if(top==-1){
			return NULL;
		}
		else{
			node=arr[top];
			
			return node;
		}
	}


};

int STACK ::size=1000;


void traverse_preOrder(struct Node *root)
{
    //To traverse_preOrder we need to use threads and normal links....I do  not have used recursion or stack to print the tree.
   

     
  if(root==NULL)
  	return;
  else{
  	 //set a pointer 'current' on the root to traverse the tree
	   Node *current = root; 
	    
	    do{
	    	cout<<" "<<current->data;
	    	//if right thread is not present.
	    	if(!current->rThread){
	    		//if left child is present and right thread is not present.
	    		if(current->left)
	    			current=current->left;
	    		else{
	    			//if there is no right thread and no left child then traverse the right child.
	    			current=current->right;
	    		}
	    	}
	    	else{
	    		//if right thread is present then traverse to the right thread.
	    		current=current->right;
	    		//[Th] will show that traversed threaded link.
	    		cout<<" [Th] ";
	    	}
	    }while(current!=NULL);

	}
}

/*
	newNode() is a function which takes the node value and insert that value after making a new node
	and finally return the address of new node.
*/
struct Node* newNode(int key){
		struct Node *temp=new Node;
		temp->data=key;
		temp->left=NULL;
		temp->right=NULL;
		temp->rThread=false;
		return temp;

}

/*
		createTree() is used for making the Binery Tree.I accepts two vector as arguments i.e arr and parent.
		arr-vector contains the node value and parent-vector contains the index/the parent node's of the  values
		present in arr-vector.All the -1 values present in arr-vector is ignored while adding node to the tree,at that
		place NULL is added to the node.
		while adding the node this function firstly add the left child node then it add the right node.
		I have taken help of map-dataStructue so that, I can have for (index,arr) pair,which is used 
		while adding nodes to the tree.When the parent contains the -1, then the corresponding arr's -vector
		stored in map is added to the root of tree.Similarly other nodes are added.
*/



struct Node* createTree(vector<int> arr,vector<int> parent){
		unordered_map<int,struct Node*> map;
		int n=arr.size();
		for(int i=0;i<n;i++){
			if(arr[i]==-1)
				map[i]=NULL;
			else
				map[i]=newNode(arr[i]);
		}
		struct Node *root=NULL;
		for(int i=0;i<n;i++){
			if(parent[i]==-1){
				root=map[i];
			}else{
				struct Node* ptr=map[parent[i]];
				if(ptr->left){
					ptr->right=map[i];
				}
				else{
					ptr->left=map[i];
				}

			}
		}
		return root;

}
/*
		This funcion helps basically travese the tree in preOrder sequence and insert the pre-order traversal of 
		node into a list named vec.
*/


void put_preOrder(struct Node* root){


	if (root == NULL) 
        return; 
  
    STACK stack;
  
    // start from root node (set current node to root node) 
    struct Node* current = root; 
  
    // run till stack is not empty or current is 
    // not NULL 
    while (stack.isEmpty()==false || current != NULL) { 
        // Print left children while exist 
        // and keep pushing right into the 
        // stack. 
        while (current != NULL) { 
        	//pushing node to the list,in preorder
            	vec.push_back(current); 
  
            if (current->right) 
                stack.myPush(current->right); 
  
            current = current->left; 
        } 
  
        // We reach where current is NULL, so We 
        // take out a right child from stack 
        if (stack.isEmpty() == false) { 
            current = stack.myPop(); 
           
        } 
    } 
}

struct Node* convertToPre_Thread(struct Node* root){

	bool flag=false;
	struct Node *curr;
	put_preOrder(root);
	

	while(!flag){
		curr=vec.front();
		if(vec.empty()){
			flag=true;
		}else{
			vec.pop_front();
			if(!curr->right && !curr->left){
				if(vec.empty()){
					curr->right=NULL;
				}
				else{
					curr->right=vec.front();
					curr->rThread=true;
				}	
			}
		}
	}
	return root;
}

int main(){

	
	vector<int> arr;
	vector<int>parent;
	cout<<"\n*************Welcome to PreOrder Threaded Binery Tree Program.********\n";
	cout<<"  Instuctions:\n -> For all the missing node, insert -1\n";
	cout<<" ->Parent of root node is -1.\n";
	cout<<"\n************************************************************************\n";
	int j=0;
	while(1){
		int choice;
		int val,par;
		if(j>0){
			if(j%2==0){
				cout<<"\nEnter node "<<j<<" value(will be added as right child) : " ;
				cin>>val;
			}
			else{
				cout<<"\nEnter node "<<j<<" value(will be added as left child) : " ;
				cin>>val;
			}

		}
		else{
			cout<<"\nEnter node "<<j<<" (i.e root) value : " ;
			cin>>val;
		}
		cout<<"Which node is Parent of node-"<<j<<" :";
		cin>>par;
		arr.push_back(val);
		parent.push_back(par);
		j++;
		cout<<"\nDo you have more node to insert(press 0 for No & non-zero for Yes):";
		cin>>choice;
		while(cin.fail()) {
		    cin.clear();
		    cin.ignore(numeric_limits<streamsize>::max(),'\n');
		    cout << "Bad entry.\nEnter choice again: ";
		    cin >> choice;
		}
		if(choice==0)
			break;
	}

	struct Node *bTree=createTree(arr,parent);

	bTree=convertToPre_Thread(bTree);
	cout<<"\nTraverasal of PreOrdered B.Tree is :\n";
	traverse_preOrder(bTree);
	cout<<endl;
	cout<<"\n*************Terminating the Program*********************"<<endl;
	
	return 0;

}

