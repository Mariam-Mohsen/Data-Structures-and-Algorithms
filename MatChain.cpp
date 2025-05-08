// GROUP:   DS2
// ID:      20227023
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Mariam Mohsen
#include <iostream>
#include <climits>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplications of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top-down version
int MatChain(int a, int b) {
    if (a+1 == b) {
        T[a][b] = 0;
        return 0;
    }
    if (T[a][b] != -1)
        return T[a][b];
    int min_val = INT_MAX, decision;
    for (int k = a+1; k < b; k++) {
        int val =  MatChain(a, k) + MatChain(k , b)+(p[a] * p[k] * p[b]);
        if (val < min_val) {
            min_val = val;
            decision = k;
        }
    }
    T[a][b] = min_val;
    D[a][b] = decision;
    return min_val;
}

void MatChainTopDown(int n) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j <11; j++) {
            T[i][j] = -1;
        }
    }
    MatChain(0, n);
}

// Bottom-up version
void MatChainBottomUp(int n) {
    for (int i = 0; i < n; i++)
        T[i][i] = 0;

    for (int t = 1; t <= n; t++) {
        for (int i = 0; i+t<=n; i++) {
            int j = i + t;
            if (i + 1 == j) {
                T[i][j] = 0;
                continue;
            }
            T[i][j] = INT_MAX;
            for (int k = i+1; k < j; k++) {
                int val = T[i][k] + T[k][j] + p[i] * p[k] * p[j];
                if (val < T[i][j]) {
                    T[i][j] = val;
                    D[i][j] = k;
                }
            }
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b) {
    if (a +1 == b) {
        cout << "A" << a+1;
        return;
    }
    int k = D[a][b];
    cout << "(";
    MatChainSol(a, k);
    cout << " x ";
    MatChainSol(k , b);
    cout << ")";
}

void Compute() {
    int n;
    int case_num = 1;
    while (true) {
        cin >> n;
        if (n == 0)
            break;
        for (int i = 0; i < n; i++) {
            cin >> p[i] >> p[i + 1];
        }
        MatChainTopDown(n);
        //MatChainBottomUp(n);
        cout << "Case " << case_num << ": ";
        MatChainSol(0, n);
        cout << endl;
        case_num++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    Compute();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////