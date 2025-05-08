// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name:    Mariam Mohsen

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
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

struct Edge
{
    int		v;
    double	w;
};

struct Node
{
    int x,y;
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

template<class Elem>
struct Heap
{
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&)){
        a.Initialize();
        IsBefore=_IsBefore;
    }
    void Destroy(){
        a.Destroy();
    }
    int Child(int i){
        return 2*i+1;
    }
    int Parent(int i){
        return (i-1)/2;
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
    void Add(Elem e){
        a.AddLast(e);
        MoveUp(a.n-1);
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
};
struct heap_pair {
    int node;
    double weight;
};
bool IsBefore(heap_pair& a, heap_pair& b) {
    return a.weight < b.weight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Sqrt(double v, int n = 100) {
    double a = 0, b = v;
    for (int i = 0; i < n; i++) {
        double m = (a + b) / 2.0;
        if (m * m > v)
            b = m;
        else
            a = m;
    }
    return (a + b) / 2.0;
}

double Prim(Graph& graph) {
    Array<bool> MST;
    MST.Initialize();
    for (int i = 0; i < graph.n; i++) {
        MST.AddLast(false);
    }
    Heap<heap_pair> heap;
    heap.Initialize(IsBefore);
    MST[0] = true;
    for (int i = 0; i < graph.nodes[0].adj.n; i++) {
        heap.Add({ graph.nodes[0].adj[i].v, graph.nodes[0].adj[i].w });
    }
    double minmax = 0;
    while (heap.a.n > 0) {
        heap_pair first = heap.RetrieveFirst();
        if (MST[first.node])
            continue;
        MST[first.node] = true;

        if (first.node == 1) {
            minmax = max(minmax, first.weight);
            break;
        }
        minmax = max(minmax, first.weight);

        for (int i = 0; i < graph.nodes[first.node].adj.n; i++) {
            if (!MST[graph.nodes[first.node].adj[i].v]) {
                heap.Add({ graph.nodes[first.node].adj[i].v, graph.nodes[first.node].adj[i].w });
            }
        }
    }

    MST.Destroy();
    heap.Destroy();
    return minmax;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n, case_num= 1;
    while (true) {
        cin>>n;
        if(n==0)
            break;
        Graph stones;
        stones.Initialize(n);
        for (int i = 0; i < n; i++) {
            cin >> stones.nodes[i].x >> stones.nodes[i].y;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double x_diff = stones.nodes[i].x - stones.nodes[j].x;
                double y_diff = stones.nodes[i].y - stones.nodes[j].y;
                double distance = Sqrt((x_diff * x_diff )+ (y_diff * y_diff));

                Edge edge_i = { j, distance };
                Edge edge_j= { i, distance };

                stones.nodes[i].adj.AddLast(edge_i);
                stones.nodes[j].adj.AddLast(edge_j);
            }
        }

        double minmax_distance = Prim(stones);
        cout << "Scenario #" << case_num++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << minmax_distance << endl<<endl;

        stones.Destroy();
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
