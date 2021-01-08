/*					
				
					Name:SUSHIL KUMAR
					To be compiled in :LINUX g++
*/
/*
		Q.  Write an efficient C/C++ program that inputs a DAG (directed acyclic graph)
            G = (V, E) and an ordering a of the vertices of G. The program returns TRUE
			if a is a topological sort of G or FALSE if a is not a topological sort of G.
				(Assume vertices are numbered from 1..n where |V| = n) 
*/
/*
		Given a DAG graph and a linear order, Verify is given order in Topological sorted order.
*/
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
#include<vector>

struct adjListNode 
{ 
    int dest; 
    struct adjListNode* next; 
}; 
  
// A structure to represent an directory of adjacency list 
struct AdjList 
{ 
    struct adjListNode *head;  
}; 
  
// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices  
// in graph) 
struct Graph 
{ 
    int V; 
    struct AdjList* node_array; 
}; 
  
// A utility function to create a new adjacency list node 
struct adjListNode* newAdjListNode(int dest) 
{ 
    //struct adjListNode* newNode = (struct adjListNode*) malloc(sizeof(struct adjListNode)); 
    struct adjListNode* newNode= new struct adjListNode;
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
} 
  
// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
    //struct Graph* graph =  (struct Graph*) malloc(sizeof(struct Graph)); 
    struct Graph* graph =  new struct Graph;
    graph->V = V; 
  
    /* Create an array of adjacency lists.  Size of  
    array will be V.
    graph->array = put a AdjList array of V size.*/
  	graph->node_array=new struct AdjList[V];

    /* Initialize each adjacency list as empty by  
        making head as NULL */
    int i=0; 
  
    while(i<V){
    	graph->node_array[i].head = NULL;
    	i++;
    }
  
    return graph; 
} 
  
// Adds an edge to an directed graph 
void addEdge(struct Graph* graph, int src, int dest) 
{ 
    /* Add an edge from src to dest.  A new node is  
      added to the adjacency list of src.  The node 
     is added at the beginning */
    struct adjListNode* newNode = newAdjListNode(dest); 
    newNode->next = graph->node_array[src].head; 
    graph->node_array[src].head = newNode; 
  
   
} 
  
/*
	isTopologicalOrder() function will help in detecting whether the given order is a topological sorting order or not.
	ord vector will contain a order which needs to be verified.
	created a visited vector, for keeping track which nodes have been visited.
	Concept used:-
		A topological sort of a DAG gr. G(V,E) is a linear ordering of all its vertices such 
		that if G contains an edge (u,v), then u appears before v in the ordering .
*/

bool isToplogicalOrder(vector<int> ord, struct Graph* graph){
	
	  vector <int> visited;
	  //for each node 'v' in ord list.
	  for(int i=0;i<ord.size();i++){

	  	int v=ord[i];
	  	//adding node 'v' to the visited list.
	  	visited.push_back(v);
	  	struct adjListNode* pCrawl = graph->node_array[v].head; 

       
        while (pCrawl) 
        { 	/*
        		for each node 'm' reachable from node 'v'.check if 'm' is present in visited list or not.
        	 */
            int m=pCrawl->dest;
            for(int j=0;j<visited.size();j++){
            	//if m present in visited list
            	if(m==visited[j])
            	{
            		return false;
            	}
            } 
            pCrawl = pCrawl->next; 
        } 
        

	  }

	  return true;

}

int main() 
{ 	
	cout<<"\n******* Welcome to Topological Sorting order Verification Program. ********\n"<<endl;
	cout<<"*****************************************************************\n";
	cout<<"\tNOTE: edge will be : src->dest "<<endl;
    cout<<"\t      Press: 0 for No.\n\t      Press: non-zero value for Yes.\n"<<endl;
    cout<<"*****************************************************************\n";
    int V;
    cout<<"Enter the number of nodes in Graph: ";
    cin>>V;
    struct Graph* graph = createGraph(V); 
    int e;
    cout<<"Enter number of edges in Graph: ";
    cin>>e;
    int src,dest;
    int choice;
    int t=1;
    while(t<=e)
   	{
   		cout<<"\nEnter edge (src  dest) pair :";
   		cin>>src;
   		
   		cin>>dest;
   		addEdge(graph,src-1,dest-1);
   		t++;
   		
  	 }
  
    
    vector<int> ord;
   
    int ch;
    while(1){
    cout<<"\nEnter the Topol. order :";
    for(int i=0;i<V;i++){
    	int val;
    	cin>>val;
    	ord.push_back(val-1);
    }
     cout<<"\nVerifying for Topological Sorting..\n Result : ";
	    if(isToplogicalOrder(ord,graph)){
	    	cout<<"TRUE "<<endl;
	    }
	    else
	    	cout<<"FALSE "<<endl;
	    cout<<"\nTest on other Order (Press: Non-zero for 'yes')  :";

    cin>>ch;
    if(ch==0)
    	break;
    ord.clear();
  }
  cout<<"\n****************** Terminating Program ******************\n";
    return 0; 
} 