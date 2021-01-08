/*					
					Name:SUSHIL KUMAR
					To be compiled in :LINUX g++
*/

/*
	Q2. Program for "Tower of Hanoi" using Non-recursive approach with the help of STACK.
		Firstly,I have made STACK class which takes size of stack by the user.This stack size will be
		equal to the number of disk to be transfered.
		I have made 3 instance of class STACK i.e src,dest,aux which can we thought as 3 rod, for this program.

*/


#include<iostream>
using namespace std;
#include<math.h>



/* making STACK class*/
class STACK{
public:
	/*size is a static member variable*/
	static int size;
	int top;
	int *arr=new int[size];
	/*constructor for STACK class*/
	STACK(){
		top=-1;
		
	}
	/*	
		Push function of stack, takes an element and put it  at the 
		top of the STACK;
	*/
	void push(int val){
		if(top==size-1){
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
/*
	pop() helps in removing the top element from the STACK.
*/
	}
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

int STACK::size;
/*
	making 3 object of STACK class. 
*/
STACK src;
STACK aux;
STACK dest;

/*
	diskMovement()  implements  movement between two poles,it takes the refernce of stack 'src' and stack 'dest'. 
*/ 
void  diskMovement(STACK &src,STACK &dest, char s, char d)
{
	int topPole1 = src.pop();
	int topPole2 = dest.pop();
	/*
		When pole 1 is empty
	*/ 
	if (topPole1 == -1)
	{
		src.push(topPole2);
		cout<<"\tTransfer the disk "<< topPole2 <<" from "<< d <<" to "<< s <<endl;
	}
	/*
	 	When pole2  is empty
	 */
	else if (topPole2 == -1)
	{
		dest.push(topPole1);
		cout<<"\tTransfer the disk "<< topPole1 <<" from "<< s <<" to "<< d <<endl;
	}
	/*
		 When top disk of pole1 > top disk of pole2.
	*/
	else if (topPole1 > topPole2)
	{
		src.push(topPole1);
		src.push(topPole2);
		cout<<"\tTransfer the disk "<<topPole2<<" from "<< d <<" to "<< s <<endl;
	}
	/*
		 When top disk of pole1 < top disk of pole2
	*/
	else
	{
		dest.push(topPole2);
		dest.push(topPole1);
		cout<<"\tTransfer the disk "<< topPole1 <<" from "<< s <<" to "<< d <<endl;
	}
}




/*
	This Function is to implement TOH puzzle,It takes 4 parameter (i.e. src,aux,dest and diskNum).
*/
void toh(STACK &src, STACK &aux, STACK &dest,int diskNum)
{
	int totMove;
	/*
		the name of poles are "S"(sourse);"D"(destination);"A"(auxiliary).
	*/
	char s = 'S', d = 'D', a = 'A';
	/*
		If number of disks is even, then interchange
		destination pole and auxiliary pole.
	*/

	/*
		totMove will containg the maximum possible moves in toh i.e 2^n-1 moves.
	*/
	totMove = pow(2, diskNum) - 1;
	
	if (diskNum % 2 == 0)
	{

		char temp = a;
		a = d;
		d = temp;
	}
	
	/*
		Larger disks will be pushed first.
	*/
	int j=diskNum;
	while(j>=1){
		src.push(j);
		j--;
	}
	int i=1;
	while(i <= totMove)
	{	
		int choice=i%3;
		switch(choice){
			case 1:{
				//moving disk from src pole to dest pole.
				diskMovement(src, dest, s, d);
				break;
			}
			case 2:{
				//moving disk from src pole to aux pole.
				diskMovement(src, aux, s, a);
				break;
			}
			case 0:{
				//moving disk from aux pole to dest pole.
				diskMovement(aux, dest, a, d);
				break;
			}
		}
		i++;
		
	}
}

int main(){
	int diskNum,totalMov;
	cout<<"*********************** Welcome to TOH program ************************"<<endl;
	cout<<"Enter number of disks :";
	cin>>diskNum;
	STACK::size=diskNum;
	totalMov=pow(2,diskNum)-1;
	cout<<"\nTotal number of disk Movement will be :"<<totalMov<<endl;
	//calling toh().
	toh(src,aux,dest,diskNum);
	cout<<"\n********************** Have a Good Day!! ******************************"<<endl;
	return 0;

}