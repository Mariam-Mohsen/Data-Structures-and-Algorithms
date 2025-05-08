// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
    return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    while(true){
        cin>>n;
        if(n==0){
            break;
        }
        else{
            int total=0,cost=0;
            Heap<int> numbers;
            numbers.Initialize(IsBeforeInt);
            for(int i=0;i<n;i++){
                int num;
                cin>>num;
                numbers.Add(num);
            }
            while(numbers.a.n>1){
                cost=numbers.RetrieveFirst()+numbers.RetrieveFirst();
                total+=cost;
                numbers.Add(cost);
            }
            cout<<total<<endl;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
