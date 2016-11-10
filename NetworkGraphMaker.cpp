/****************************************/
/*                Notes:                */
/*    We use - to represent a -1 in     */
/*         the distance matrix          */
/****************************************/

#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;

class Graph{
  private:
    int n; // Number of nodes
    int **edges; // Stores the edges between 2 nodes
    int *dist;
    vector<vector<int>> components;

    int **adj;
    int **distmatrix;

    void display(int **matrix);
    
  public:
    Graph(int n);
    bool connected(int pair_a, int pair_b);
    void add_edge(int pair_a, int pair_b);
    int* bfs(int vertex);
    void distancematrix();
    void display();
    int diameter();
    void connectedcomponents();
    
};

/************************************************
       Adjacency Matrix (Graph Contructor)
************************************************/
Graph::Graph(int n){
  this->n = n;
  adj = new int* [n]; // make an array called adj

  for(int i = 0; i < n; i++){
    adj[i] = new int [n]; // make an array of size n (rows)
    for(int j = 0; j < n; j++){
      adj[i][j] = 0; // make an array of size n (columns)
    }
  }
}

/************************************************
               Add edge to graph
************************************************/
void Graph::add_edge(int pair_a, int pair_b){
  if(pair_a > n || pair_b > n || pair_a < 0 || pair_b < 0){
    cout << "Invalid edge!" << endl;
    cout << "This edge is not calculated in graph!" << endl;
  }
  else{
    adj[pair_a][pair_b] = 1; // add pair to the graph
  }
}

/************************************************
                        BFS
************************************************/
int* Graph::bfs(int vertex){
  queue<int> cue; // create a queue that is empty
  int* dist = new int[n]; // create an array size n

  for(int i = 0; i < n; i++){ // check visited nodes
    dist[i] = -1; // setting the array to -1
  }

  cue.push(vertex); // push the initial vertex to the queue
  dist[vertex] = 0;
    
  while(!cue.empty()){ // check to see if the queue is empty
    int v = cue.front(); // set v to the first value in the queue
    cue.pop(); // pop the first value

    for(int w = 0; w < n; w++){
      if(connected(v, w) && dist[w] == -1){ // check to see if 2 nodes are connected and w is set to -1 or not visited
        dist[w] = dist[v] + 1; // add 1 to the parent node
        cue.push(w); // push w to the front of the queue
      }
    }
  }
  return dist; // return the array
}

/************************************************
                   Connected
************************************************/
bool Graph::connected(int pair_a, int pair_b){
  return (adj[pair_a][pair_b] == 1);
}

/************************************************
                Distance Matrix
************************************************/
void Graph::distancematrix(){
  distmatrix = new int* [n]; // make an array called distmatrix
  for(int i = 0; i < n; i++){
    distmatrix[i] = bfs(i); // call bfs into the array
  }
}

/************************************************
                    Diameter
************************************************/
int Graph::diameter(){
  int d = -1;
  for(int i = 0; i < n; i++){
    if(*distmatrix[i] == -1){
      d = -1; // when the graph is disconnected output -1
      return d;
    }
    else if(d < *distmatrix[i]){
      d = *distmatrix[i]; // when graph is connected output value
    }
  }
  return d;
}

/************************************************
                Connected Component
************************************************/
void Graph::connectedcomponents(){
  bool *visited = new bool[n]();
  for(int i = 0; i < n; i++){
    if(visited[i]){
      continue; // continue if the node has been visited
    }
    vector<int> connect_comp;
    for(int j = 0; j < n; j++){
      if(distmatrix[i][j] != -1){
        visited[j] = true; // mark the value true so then we know it is visited
        connect_comp.push_back(j); // push back values that are not -1 to a new vector
      }
    }
    components.push_back(connect_comp); // take those values and put them in the original vector
  }
}

/************************************************
               Display the Graph
************************************************/
void Graph::display(int **matrix){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(matrix[i][j] == -1){
        cout << " - "; // make the -1 a - so then graph is pretty looking
      }
      else{
        cout << " " << matrix[i][j] << " ";
      }
    }
    cout << endl;
  }
}

void Graph::display(){
  cout << "--- Adjacency Matrix ---" << endl;
  display(adj); // display adjacency matrix from display function
  cout << endl;

  cout << "--- Distance Matrix ---" << endl;
  display(distmatrix); // display distance matrix from display function
  cout << endl;

  if(diameter() == -1){ // display for disconnected graphs
    cout << "--- Diameter ---" << endl;
    cout << diameter() << endl << endl; // display diameter
    cout << "--- Connected Components ---" << endl;
    for (int i = 0; i < components.size(); i++) { // display components
      for (int j = 0; j < components[i].size(); j++) {
        cout << components[i][j] << " ";
      }
      cout << endl;
    }
  }
  else{ // display for connected graphs
    cout << "--- Diameter ---" << endl;
    cout << diameter() << endl << endl; // display diameter
  }
}

/************************************************
                   Main Function
                  Get information
************************************************/
int main(){
  int NumNodes;
  int pair_a = -1;
  int pair_b = 0;

  cout << "Enter number of nodes: " << endl;
  cin >> NumNodes;
  
  // end program if numnodes is negative
  if(NumNodes < 0){
    cout << "Incorrect Usage: Please use a positive value for number of nodes!" << endl;
    return 0;
  }
  // anything other than an integer end program
  else if(!cin){
    cout << "Incorrect Usage: Please use a integer value for number of nodes!" << endl;
    return 0;
  }

  Graph n(NumNodes);
  cout << "Enter the pairs: " << endl;
    
  while(true){
    cin >> pair_b;
    if(!cin){
      cout << "Incorrect Usage: One of you pair values is not an integer!" << endl;
      return 0;
    }
    else if(pair_b == NumNodes){
      cout << "Incorrect Usgae: A pair value is equal to the number of nodes!" << endl;
      return 0;
    }
    // anything other than an integer end program
    if(pair_b < 0){
      break; // We need to break if a pair value is less than 0
    }
    else if(pair_a == -1){
      pair_a = pair_b; // We need to assign pair_b to pair_a to get a pair
    }
    else{
      n.add_edge(pair_a, pair_b);
      n.add_edge(pair_b, pair_a);
      pair_a = -1; // reassign pair_a to -1 to restart while loop
    }
  }

  cout << endl;
  n.distancematrix();
  n.connectedcomponents();
  n.display();

  return 0;
}
