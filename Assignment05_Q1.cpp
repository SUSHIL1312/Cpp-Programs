/*				
					Name:SUSHIL KUMAR
					To be compiled in :LINUX g++
*/
/*
	Question: Write C/C++ program to compute the k closest elements from a key value x
				that belongs to the array A[n] of n data items.

 Hint:
1. PARTITION (described in QUICKSORT) the array A[n] around x as the
pivot.
2. For all elements to the left of x construct a max heap.
3. For all elements to the right of x construct a min heap. 

	
*/

#include<iostream>
using namespace std;
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#define INF 999999
/*
	swap_fns() helps in swapping two values.
*/
void swap_fns(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
//printArray() helps in printing eleents present in list.
void printArray(vector<int> array){
	for(int i=0;i<array.size();i++)
		cout<<array[i]<<" ";
}

/*
	partition() takes  array/vector elements and arrange the elements such that pivot elment goes
	at its correct position as it would have been in a shorted list.This partition function considers
	first element as the pivot elements. finally, it will return the index of the pivot element. 
*/
int partition(vector<int>&array,int low,int high){
	int i=low;
	int j=high+1;
	/*adding large value(i.e infinity) at the end of the array.this will help in preventing array index-out
		of bound error when pivot element bigger than all elements*/
	array.push_back(INF);
	int pivot=array[low];
	do{
		/*
			increment i till  pivot is bigger than array[i].
		*/
		do{
			i++;
		}while(array[i]<pivot);
		do{
			/*
				decrement j till pivot is lesser than elements.
			*/
			j=j-1;
		}while(array[j]>pivot);
		if(i<j){
			
			swap_fns(&array[i],&array[j]);
		}
	}while(i<j);
	
	swap_fns(&array[low],&array[j]);
	//removing the extra added value from the list.
	array.pop_back();
	return(j);

}

/*
	adjust_fns_max() is utility function used during arranging the elements in max heap.It is 
	called by buildMaxHeap().It will arrange the ith node in max heap.
*/
void adjust_fns_max(vector<int> &arr,int i,int n){
	/*getting the left child of the ith node.*/
	int j=2*i+1;
	int item=arr[i];
	/*
		with the help of while loop, will traverse till leaf node from the ith-node and see where max heap 
		property is violated.
	*/
	while(j<=n-1){
		/*
			if j is less than n-1 and compare both the child of ith-node, now make the j pointing to
			that child which has more value.
		*/
		if(j<n-1 && arr[j]<arr[j+1]){
			j++;
		}
		if(arr[j]<=item) break;
		//performing the shift-up operation.
		arr[(j-1)/2]=arr[j];
		j=2*j+1;
	}
	arr[(j-1)/2]=item;
}
/*
		buildMaxHeap() is arranging the array in max heap.It is using the bottom-up construction in forming 
		max heap.As in bottom-up approach we consider all the leaf elements already arranged in max heap
		so it will start heapify process from n/2th index and call adjust_fns_max() for each node till the 
		root node,and all the nodes one by one gets arranged in max-heap. This constuction takes O(n) time-complexity.
*/
int  buildMaxHeap(vector <int> &arr){
	int n=arr.size();
	for(int i=n/2;i>=0;i--){
		adjust_fns_max(arr,i,n);
	}

	return arr[0];	//returning the max-element.
}
/*
	adjust_fns_min() is utility function used during arranging the elements in min heap.It is 
	called by buildMinHeap().It will arrange the ith node in min heap.
*/
void adjust_fns_min(vector<int> &arr,int i,int n){
	/*getting the left child of the ith node.*/
	int j=2*i+1;

	int item=arr[i];
	/*
		with the help of while loop, will traverse till leaf node from the ith-node and see where min heap 
		property is violated.
	*/
	while(j<=n-1){
		/*
			if j is less than n-1 and compare both the child of ith-node, now make the j pointing to
			that child which has lesser value.
		*/
		if(j<n-1 && arr[j]>arr[j+1]){
			j++;
		}
		if(arr[j]>=item) break;
		//performing the shift-up operation.
		arr[(j-1)/2]=arr[j];
		j=2*j+1;
	}
	arr[(j-1)/2]=item;
}

/*
		buildMinHeap() is arranging the array in min heap.It is using the bottom-up construction in forming 
		min heap.As in bottom-up approach we consider all the leaf elements already arranged in min heap
		so it will start heapify process from n/2th index and call adjust_fns_min() for each node till the 
		root node,and all the nodes one by one gets arranged in min-heap. This constuction takes O(n) time-complexity.
*/
int buildMinHeap(vector <int> &arr){
	int n=arr.size();
	for(int i=n/2;i>=0;i--){
		adjust_fns_min(arr,i,n);
	}
	return arr[0];
}

int main(){
	cout<<"\n********** Welcome to K-Nearest Neighbour Program *************\n\n";
	int n;
	cout<<"Enter the size of the array: ";
	cin>>n;
	cout<<"Enter Array elements : ";
	vector<int> arr(n,0);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	int x;
	cout<<"Enter the value of x (key value) :";
	cin>>x;
	int j;
	for(j=0;j<n;j++){
		if(arr[j]==x)
			break;
	}
	/*
		As my partition fns is considering first element as pivot,so swapping the x-value from the
		first element of the array.
	*/
	swap_fns(&arr[j],&arr[0]);
	/*
		partition() will return the index of x(key value).
	*/
	int part_ind=partition(arr,0,n-1);
	/*
		creating two vector i.e left_arr and right_arr and all the elements left of 
		partition index in left_arr and all the elents in right of the partion index in 
		right_arr.
	*/
	vector<int> left_arr,right_arr;

	for(int i=0;i<part_ind;i++)
		left_arr.push_back(arr[i]);
	for(int j=part_ind+1;j<n;j++)
		right_arr.push_back(arr[j]);
	cout<<endl;
	
	int max,min;
	//calling buildMaxHeap() on left_arr if it is not empty.
	if(left_arr.size()){
		max=buildMaxHeap(left_arr);
		
	}
	//calling buildMinHeap() on right_arr if it is not empty.
	if(right_arr.size()){
		min=buildMinHeap(right_arr);
	}

	vector<int> k_closest_elem;
	int k;
	cout<<"Enter value of k :";
	cin>>k;

	if(k>=n){
		cout<<"Please enter value of k<n.."<<endl;
		cout<<"Enter value of k :";
		cin>>k;
	}
	
	
	/*
		below part of the program helps in deciding the k-nearest neighbour of x.
	*/
	
	for(int i=0;i<k;i++){
		//checking whether any of  left_arr or right_arr vector is empty.
		if(left_arr.size()==0 || right_arr.size()==0){
		
			/*
				if left_arr is empty and right_arr is not empty, then we only need to look 
				right_arr for deciding the remaining nearest neihbours from x.
				call buildMinHeap() on right_arr which will arrange the right_arr elements in min heap 
				and add min element in k-closest element vector.finally deleting the min element from the
				vector.
			*/
			if(left_arr.size()==0 && right_arr.size()!=0){
				min=buildMinHeap(right_arr);
				k_closest_elem.push_back(min);
				right_arr.erase(right_arr.begin());
			}
			/*
				if right_arr is empty and left_arr is not empty, then we only need to look 
				left_arr for deciding the remaining nearest neihbours from x.
				call buildManHeap() on left_arr which will arrange the left_arr elements in max heap 
				and add max element in k-closest element vector.finally deleting the max element from the
				vector.
			*/
			if(right_arr.size()==0 && left_arr.size()!=0){
				max=buildMaxHeap(left_arr);
				k_closest_elem.push_back(max);
				left_arr.erase(left_arr.begin());
			}
		}
		/*
			else part of code will only execute when both left_arr and right_arr are non-empty
		*/
		else{
			/*
				Now,let us see what is happening in below if-else part.The element having minium absolute 
				difference with x(key value) gets added into the k-nearest vector. using the buildMaxHeap() and
				buildMinHeap() for getting the max(from left_arr) and min elements(from right_arr) and comparing
				those max and min value w.r.t x.
			*/
			if(abs(x-max)<=abs(x-min))
			{	
				k_closest_elem.push_back(max);
			
				left_arr.erase(left_arr.begin());
				max=buildMaxHeap(left_arr);
				

			}else{
				k_closest_elem.push_back(min);
				
				right_arr.erase(right_arr.begin());
				
				min=buildMinHeap(right_arr);
				
			}
		}
	}
	cout<<endl;

	cout<<"K-closest elements from "<<x<<" are: ";
	printArray(k_closest_elem);
	cout<<endl;
	cout<<"\n**************************Terminating Program************************"<<endl;
	return 0;
	


}
