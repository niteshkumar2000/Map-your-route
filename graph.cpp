#include<iostream>
#include <limits.h>
using namespace std;

int dup[9][9] = {
                        {0, 4, 0, 0, 0, 0, 0, 8, 0},
                        {4, 0, 8, 0, 0, 0, 0, 11, 0},
                        {0, 8, 0, 7, 0, 4, 0, 0, 2},
                        {0, 0, 7, 0, 9, 14, 0, 0, 0},
                        {0, 0, 0, 9, 0, 10, 0, 0, 0},
                        {0, 0, 4, 0, 10, 0, 2, 0, 0},
                        {0, 0, 0, 14, 0, 2, 0, 1, 6},
                        {8, 11, 0, 0, 0, 0, 1, 0, 7},
                        {0, 0, 2, 0, 0, 0, 6, 7, 0}
                    };

class Graph{
	//data members
	int V;
	int src;
	int **graph;
	int *dist;
    bool *sptSet;
    int *parent;
    //member functoins
    int minDistance();
    void printPath(int);
    void printSolution();
    void dijkstra();
    void init_graph();

public:

	Graph();
	Graph(int);
	void interface();
	
};

Graph :: Graph(){
	
	V = 9;
	src = 0;

	graph = new int*[9];
	dist = new int[9];
	parent = new int[9];
	sptSet = new bool[9];

	for(int i=0;i<9;i++){
		graph[i] = new int[9];
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			graph[i][j] = dup[i][j];
		}
	}

}

Graph :: Graph(int n){
	
	V = n;
	src = 0;

	graph = new int*[n];
	dist = new int[n];
	parent = new int[n];
	sptSet = new bool[n];

	for(int i=0;i<n;i++){
		graph[i] = new int[n];
	}

	init_graph();

}

void Graph :: init_graph(){
	
	int a,b,m,i;
	int weight;

    m=V*(V-1);

    for(i=1;i<=m;i++){

        cout<<"Enter the source and destination \t"<<endl;
        cin>>a>>b;

        if(a==-1 && b==-1)
            break;

        if((a<0) || (b<0) || (a>V) || b>V){
  	         i--;
            cout<<"Enter a proper input"<<endl;
        }
        else{
        	cout<<"Enter the distance from "<<a<<" to "<<b<<endl;
        	cin>>weight;
            graph[a][b]=weight;
            graph[b][a]=weight;
        }
    }
}

int Graph :: minDistance()
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void Graph :: printPath(int j)
{

    if (parent[j] == - 1)
        return;

    printPath(parent[j]);

    cout<<j<<" ";
}

void Graph :: printSolution()
{
    cout<<"Vertex\t\tDistance\tPath"<<endl;

    for (int i = 0; i < V; i++)
    {
        cout<<'\n'<<src<<" -> "<<i<<"\t\t"<<dist[i]<<"\t\t"<<src<<" ";
        printPath(i);
    }
}

void Graph :: dijkstra()
{

    for (int i = 0; i < V; i++)
    {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {

        int u = minDistance();

        sptSet[u] = true;

        for (int v = 0; v < V; v++){

            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution();
}

void Graph :: interface(){

	cout<<"Enter the source"<<endl;
	cin>>src;

	cout<<"Locating shortest route..."<<endl;
	dijkstra();


}

// Entry point
int main(){
	Graph g;
	g.interface();
	return 0;		
}
