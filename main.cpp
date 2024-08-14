#include <iostream>
using namespace std;

//edge node structure for adjacency list (directed graph)
struct edge{
  int adj_vtx;	//index of adjacent vertex
  edge* next;		//link to next node in the list
};

//custom queue class implementation (for BFS)
class Queue{
  private:
		//queue node structure
    struct node{
      int data;		//node data value
      node* next;	//next node pointer
    };
    node* head;		//points to first element in queue
    node* tail;		//points to last element in queue
  public:
		//constructor
    Queue(){
    	head = nullptr;		//initialize head pointer
      tail = nullptr;		//initialize tail pointer
    }
		//function to add a node to the queue
    void enqueue(int val){
			//make a new node pointer
      node* newNode = new node;
      newNode->data = val;
      newNode->next = nullptr;
			//if queue is empty: new node becomes head & tail becomes head
      if(head == nullptr){
        head = newNode;
				tail = head;
			//if not empty: insert new node to next node of tail
      }else{
        tail->next = newNode;
        tail = newNode;
      }
    }
		//function to remove a node from the queue
    int dequeue(){
			//if empty: do nothing
      if(head == nullptr){
        cout << "Queue is empty" << endl;
        return -1;
      }
			//if not empty: delete head node & replace with next node
      node* temp = head;
      int tmp = temp->data;
      head = head->next;
      delete temp;
      return tmp;
    }
		//function to check if queue is empty
    bool isEmpty(){
      return head == nullptr;
    }
};

//custom list class implementation (for adjacency list)
class List{
  private:
    edge* head;		//pointer to list front
		edge* tail;		//pointer to list back
  public:
		//constructor
    List(){
      head = nullptr;		//initialize head & tail
			tail = nullptr;
    }
		//create new node for adjacency list
    void insert(int val){
      edge* newNode = new edge;
      newNode->adj_vtx = val;
			newNode->next = nullptr;
			//if list empty: set head & tail to new edge value
			if(head == nullptr){
				head = newNode;
				tail = head;
			//if not empty: set to the back of list
			}else{
				tail->next = newNode;
				tail = newNode;
			}
    }
		//get the value of the list front node
    edge* getHead(){
      return head;
    }
};

//graph class initializing the class requirements
class Graph{
  private:
    int V;	//number of vertices
    List* adj;	//pointer to array with adjacency lists
    void DFSUtil(int v, bool visited[]);	//recursive function for DFS 
  public:
    Graph(int V);	//constructor
    void addEdge(int v, int w);	//function to add an edge (from v to w) to graph
    void BFS(int s);	//BFS traversal of the vertices reachable from s
    void DFS(int v);	//DFS traversal of the vertices reachable from v
};

//constructor
Graph::Graph(int V){
  this->V = V;
  adj = new List[V];
}

//function to add an edge (from v to w) to graph
void Graph::addEdge(int v, int w){
  adj[v].insert(w);
}

//BFS traversal of the vertices reachable from vertex s
void Graph::BFS(int s){
	//make visited array
  bool* visited = new bool[V];
  for(int i = 0; i < V; i++){
    visited[i] = false;
  }
	//make queue for BFS
  Queue q;
	//mark current node visited & enqueue it
	visited[s] = true;
  q.enqueue(s);
  while(!q.isEmpty()){
		//dequeue a vertex from queue & print it
    int v = q.dequeue();
    cout << v << " ";
		//get all adjacent vertices of dequeued vertex s
    for(edge* i = adj[v].getHead(); i != nullptr; i = i->next){
			//if adjacent vertex is not visited, mark it visited & enqueue it
      int a_vtx = i->adj_vtx;
      if(!visited[a_vtx]){
        visited[a_vtx] = true;
        q.enqueue(a_vtx);
      }
    }
  }
  cout << endl;
}

//recursive function for DFS traversing
void Graph::DFSUtil(int v, bool visited[]){
  visited[v] = true;		//mark current vertex visited & print it
  cout << v << " ";
	//traverse adjacent vertices
  for(edge* i = adj[v].getHead(); i != nullptr; i = i->next){
    int a_vtx = i->adj_vtx;
		//go to next adjacent vertex if not visited yet
    if(!visited[a_vtx]){
      DFSUtil(a_vtx, visited);
    }
  }
}

//DFS traversal of vertices reachable from vertex v
void Graph::DFS(int v){
	//make visited array
  bool* visited = new bool[V];
  for(int i = 0; i < V; i++){
    visited[i] = false;
  }
	//call helper function to print the DFS list
  DFSUtil(v, visited);
  cout << endl;
}

//test the functions
int main(){
  Graph g(5);					//number of vertices in graph
  g.addEdge(0, 1);		//add an edge from v to w (v, w)
  g.addEdge(0, 2);
  g.addEdge(1, 2);
	g.addEdge(1, 4);
  g.addEdge(2, 0);
  g.addEdge(2, 3);
  g.addEdge(3, 1);
	g.addEdge(3, 4);
  g.addEdge(4, 1);
	g.addEdge(4, 2);

  cout << "Depth First Traversal: ";
  g.DFS(2);					//starting from vertex (#)
  cout << endl;

  cout << "Breadth First Traversal: ";
  g.BFS(2);					//starting from vertex (#)
  cout << endl;

	return 0;
}