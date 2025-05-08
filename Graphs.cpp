// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mariam Mohsen

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize(){
        n=0;
        sz=10;
        arr=new Value[sz];
    }
    void Destroy(){
        delete[] arr;
    }
    void AddLast(Value v){
        if(n<sz){
            arr[n]=v;
            n++;
        }
        else{
            sz*=2;
            Value* new_arr=new Value[sz];
            for(int i=0;i<n;i++)
                new_arr[i]=arr[i];
            arr=new_arr;
            arr[n]=v;
            n++;
        }
    }
    void RemoveLast(){
        if(n>0)
            n--;
        if(n<sz/4){
            sz/=2;
            Value*new_arr=new Value[sz];
            for(int i=0;i<n;i++)
                new_arr[i]=arr[i];
            arr=new_arr;
        }
    }
    Value& operator[](int i){
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<int> adj;

	void Initialize(){
        adj.Initialize();
    }
	void Destroy(){
        adj.Destroy();
    }
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n){
        n=_n;
        nodes=new Node[n];
        for(int i=0;i<n;i++){
            nodes[i].Initialize();
        }
    }
	void Destroy(){
        for(int i=0;i<n;i++){
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
	int f,r,n,sz;
	Type* elems;

	void Initialize(int size){
        sz=size;
        n=0;
        f=0;
        r=-1;
        elems=new Type[sz];
    }
	void Destroy(){
        delete[] elems;
    }
	void Add(Type t){
        if(n<sz){
            r++;
            elems[r]=t;
            n++;
        }
        else{
            sz*=2;
            Type* new_elems=new Type[sz];
            for(int i=0;i<n;i++)
                new_elems[i]=elems[i];
            elems=new_elems;
            r++;
            elems[r]=t;
            n++;
        }
    }
	Type Pop(){
        if(n!=0) {
            Type front = elems[f];
            f++;
            n--;
            return front;
        }
    }
	Type Peek(){
        return elems[f];
    }
	int Num(){
        return n;
    }
};

    int maximum,day;
    void bfs(Graph &g,int v){
        Queue<int> q;
        q.Initialize(g.n);
        bool* visited=new bool[g.n];
        int* count=new int[g.n];
        int level=0;
        for(int i=0;i<g.n;i++){
            visited[i]=false;
            count[i]=0;
        }
        visited[v]=true;
        q.Add(v);
        while(q.Num()>0){
            int level_size=q.Num();
            count[level]=level_size;
            for (int i = 0; i < level_size; i++) {
                int temp=q.Pop();
                for(int j=0;j<g.nodes[temp].adj.n;j++) {
                    if (!visited[g.nodes[temp].adj[j]]) {
                        visited[g.nodes[temp].adj[j]] = true;
                        q.Add(g.nodes[temp].adj[j]);
                    }
                  }
            }
            level++;
        }
        maximum=count[1];
        day=1;
        for(int i=2;i<g.n;i++){
            if(count[i]>maximum){
                maximum=count[i];
                day=i;
            }
        }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    int e;
    cin>>e;
    Graph g;
    g.Initialize(e);
    for(int i=0;i<e;i++){
        int n;
        cin>>n;
        for(int j=0;j<n;j++){
            int colleague;
            cin>>colleague;
            g.nodes[i].adj.AddLast(colleague);
        }
    }
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int source;
        cin>>source;
        bfs(g,source);
        if(maximum==0)
            cout<<0<<endl;
        else{
            cout<<maximum<<" "<<day<<endl;
        }
        maximum=0;
        day=0;
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
