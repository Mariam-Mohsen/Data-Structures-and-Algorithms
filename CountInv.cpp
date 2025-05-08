// GROUP:   Data Science-DS2
// ID:      20227023
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Mariam Mohsen

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int n){
    long long* arr = new long long[n];
    int i = 0, j = n/2, k = 0;
    long long count = 0;
    while (i < n/2 && j < n) {
        if (a[i] <= a[j]) {
            arr[k++] = a[i++];
        }
        else {
            arr[k++] = a[j++];
            count += ((n/2) - i);
        }
    }
    while (i < n/2) {
        arr[k++] = a[i++];
    }
    while (j < n) {
        arr[k++] = a[j++];
    }
    for (i = 0; i < n; i++) {
        a[i] = arr[i];
    }

    delete[] arr;
    return count;
}
long long CountInv(long long* a, int n){
    if(n==1)
        return 0;
    long long c1= CountInv(a,n/2);
    long long c2= CountInv(a+n/2,n-n/2);
    long long c3= CountInvMerge(a,n);
    return c1+c2+c3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    while(true){
        cin>>n;
        if(n==0)
            break;
        long long* nums = new long long[n];
        for(int i=0;i<n;i++)
            cin>>nums[i];
        long long count= CountInv(nums,n);
        cout<<count<<endl;

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
