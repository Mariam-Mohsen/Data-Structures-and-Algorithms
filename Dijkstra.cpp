// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
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
        if(n<sz/4){ //shrink
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

template<class Elem>
struct Heap
{
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n){// n is required to allocate and initialize pos[]
        a.Initialize();
        IsBefore=_IsBefore;
        pos=new int[n];
        for (int i=0;i<n;i++)
            pos[i]=-1;
    }
    void Destroy(){
        a.Destroy();
        delete [] pos;
    }
    void Print(){
        for(int i=0;i<a.n;i++){
            cout<<a[i];
        }
    }
    int Child(int i){
        return 2*i+1;
    }
    int Parent(int i){
        return (i-1)/2;
    }
    Elem GetFirst(){
        return a[0];
    }
    Elem RetrieveFirst(){
        Elem first=a[0];
        a[0]=a[a.n-1];
        a.RemoveLast();
        MoveDown(0);
        return first;
    }
    void Add(Elem e){
        a.AddLast(e);
        MoveUp(a.n-1);
    }
    void MoveUp(int ind){
        if(IsBefore(a[ind],a[Parent(ind)]) && ind>0) {
            swap(a[ind], a[Parent(ind)]);
            MoveUp(Parent(ind));
        }
        else
            return;
    }
    void MoveDown(int ind){
        int l=Child(ind);
        int r=l+1;
        int smallest=ind;
        if(l<a.n && IsBefore(a[l], a[smallest]))
            smallest=l;
        if(r<a.n && IsBefore(a[r], a[smallest]))
            smallest=r;
        if(smallest!=ind){
            swap(a[ind],a[smallest]);
            MoveDown(smallest);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int		v;
    int		w;
};

struct Node
{
    Array<Edge> adj;
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

bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

int dijkstra(Graph graph, int source, int destination) {
    Array<int> distance;
    distance.Initialize();
    for (int i = 0; i < graph.n; i++){
        distance.AddLast(10000000);
    }
    distance[source] = 0;
    Heap<Edge> heap;
    heap.Initialize(IsBefore, graph.n);
    heap.Add({source, 0});

    while (heap.a.n > 0) {
        Edge smallest = heap.RetrieveFirst();
        if (smallest.v == destination) {
            distance.Destroy();
            heap.Destroy();
            return smallest.w;
        }
        for (int i = 0; i < graph.nodes[smallest.v].adj.n; i++) {
            Edge edge = graph.nodes[smallest.v].adj[i];
            if (distance[smallest.v] + edge.w < distance[edge.v]) {
                distance[edge.v] = distance[smallest.v] + edge.w;
                heap.Add({edge.v, distance[edge.v]});
            }
        }
    }
    distance.Destroy();
    heap.Destroy();
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N,casenum=1;
    cin>>N;
    for(int i=0;i<N;i++){
        int n,m,s,t;
        cin>>n>>m>>s>>t;
        if(m==0) {
            cout << "Case #" << casenum++ << ": unreachable"<<endl;
            continue;
        }
        Graph servers;
        servers.Initialize(n);
        for(int j=0;j<m;j++){
            int u,v,w;
            cin>>u>>v>>w;
            servers.nodes[u].adj.AddLast({v,w});
            servers.nodes[v].adj.AddLast({u,w});
        }
        int shortest_time=dijkstra(servers,s,t);
        if(shortest_time>0)
            cout<< "Case #" << casenum++ << ": "<<shortest_time<<endl;
        else
            cout << "Case #" << casenum++ << ": unreachable"<<endl;
        servers.Destroy();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
