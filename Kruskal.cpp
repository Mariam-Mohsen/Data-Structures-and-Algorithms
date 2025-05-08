// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mariam Mohsen

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n){
        n=_n;
        parent=new int[n];
        num_nodes=new int[n];
        for(int i=0;i<n;i++){
            parent[i]=-1;
            num_nodes[i]=1;
        }
    }
    void Destroy(){
        delete [] parent;
        delete [] num_nodes;
    }
    int Find(int i){
        if(parent[i]==-1)
            return i;
        else{
            parent[i]= Find(parent[i]);
            return parent[i];
        }
    }
    bool Union(int i, int j){
        int parent_i= Find(i);
        int parent_j= Find(j);
        if(parent_i!=parent_j){
            if(num_nodes[parent_i]>num_nodes[parent_j]){
                parent[parent_j]=parent_i;
                num_nodes[parent_i]+=num_nodes[parent_j];
            }
            else{
                parent[parent_i]=parent_j;
                num_nodes[parent_j]+=num_nodes[parent_i];
            }
            return true;
        }
        return false;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    Type* arr = new Type[n];
    int i = 0, j = n/2, k = 0;
    while (i < n/2 && j < n) {
        if (IsBefore(a[i], a[j]))
            arr[k++] = a[i++];
        else
            arr[k++] = a[j++];
    }
    while (i < n/2){
        arr[k++] = a[i++];
    }
    while (j < n){
        arr[k++] = a[j++];
    }
    for (i = 0; i < n; i++){
        a[i] = arr[i];
    }
    delete[] arr;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    if(n==1)
        return;
    MergeSort(a,n/2,IsBefore);
    MergeSort(a+(n/2),n-(n/2),IsBefore);
    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int m,n;
    while (true) {
        cin >> m >> n;
        if(m==0 && n==0)
            break;
        int cost=0;
        Edge* roads=new Edge[n];
        for(int i=0;i<n;i++){
            cin>>roads[i].u>>roads[i].v>>roads[i].w;
            cost+=roads[i].w;
        }
        int actual_cost=0;
        MergeSort(roads,n,IsBeforeEdge);
        DisjointSets junctions;
        junctions.Initialize(m);
        for(int i=0;i<n;i++){
            if(junctions.Union(roads[i].u,roads[i].v)){
                actual_cost+=roads[i].w;
            }
        }
        cout<<cost-actual_cost<<endl;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
