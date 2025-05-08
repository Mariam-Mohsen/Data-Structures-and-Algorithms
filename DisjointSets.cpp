// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
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

int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,m;
        cin>>n>>m;
        DisjointSets friends;
        friends.Initialize(n);
        for(int j=0;j<m;j++){
            int a,b;
            cin>>a>>b;
            friends.Union(a-1,b-1);
        }
        int max=friends.num_nodes[0];
        for(int j=0;j<n;j++){
            if(friends.num_nodes[j]>max)
                max=friends.num_nodes[j];
        }
        cout<<max<<endl;
        friends.Destroy();
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////


