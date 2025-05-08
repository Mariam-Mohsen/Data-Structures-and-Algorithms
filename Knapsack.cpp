// GROUP:   DS2
// ID:      20227023
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Mariam Mohsen

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w){
    if (n == 0)
        return 0;
    if (T1[n][w] != -1)
        return T1[n][w];
    if (a[n - 1].w > w)
        return T1[n][w] = Knapsack1(n - 1, w);
    int v1= a[n - 1].v + Knapsack1(n - 1, w - a[n - 1].w);
    int v2=Knapsack1(n - 1, w);
    int v=max(v1,v2);
    T1[n][w] = v;
    return v;
}
int ComputeKnapsack1(int N, int W){// Recursive - memoization - initialize T then call Knapsack1(N,W);
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= W; j++) {
            T1[i][j] = -1;
        }
    }
    return Knapsack1(N, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W){ // Bottom-up, do not save space
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= W; j++) {
            T2[i][j] = 0;
        }
    }

    for (int n = 1; n <= N; n++) {
        for (int w = 1; w <= W; w++) {
            if (a[n - 1].w > w)
                T2[n][w] = T2[n - 1][w];
            else{
                int v1=a[n - 1].v + T2[n - 1][w - a[n - 1].w];
                int v2=T2[n - 1][w];
                int v=max(v1,v2);
                T2[n][w] = v;
            }
        }
    }
    return T2[N][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W){ // Bottom-up, use two rows only
    for(int w=0;w<=W;w++){
        T3[0][w]=0;
    }
    int curr = 0;
    for (int n = 1; n <= N; n++) {
        curr = 1 - curr;
        for (int w = 0; w <= W; w++) {
            if (a[n - 1].w > w) {
                T3[curr][w] = T3[1 - curr][w];
            }
            else{
                int v1 = T3[1 - curr][w];
                int v2 = a[n - 1].v + T3[1 - curr][w - a[n - 1].w];
                int v=max(v1, v2);
                T3[curr][w] = v;
            }
        }
    }

    return T3[curr][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W){// Bottom-up, save maximum space
    for (int i = 0; i <= W; i++) {
        T4[i] = 0;
    }

    for (int n= 1; n <= N; n++) {
        for (int w = W; w >= 0; w--) {
            if(w>=a[n-1].w) {
                int v1 = a[n - 1].v + T4[w - a[n - 1].w];
                int v2 = T4[w];
                int v = max(v1, v2);
                T4[w] = v;
            }
        }
    }
    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
    return ComputeKnapsack1(N,W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    //return ComputeKnapsack4(N,W);
}

void Compute(){ // Get input and call ComputeKnapsack() whenever needed
    int t;
    cin >> t;
    for (int i=0;i<t;i++) {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> a[j].v >> a[j].w;
        }
        int g;
        cin >> g;
        int max_value = 0;
        for (int j = 0; j < g; j++) {
            int max_weight;
            cin >> max_weight;

            max_value += ComputeKnapsack(n, max_weight);
        }

        cout << max_value << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign09_10130.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////