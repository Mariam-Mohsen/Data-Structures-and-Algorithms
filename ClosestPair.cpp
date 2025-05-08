// GROUP:   DS2
// ID:      20227023
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name:    Mariam Mohsen

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

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
    if(n<=1)
        return;
    MergeSort(a,n/2,IsBefore);
    MergeSort(a+(n/2),n-(n/2),IsBefore);
    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b){
    return a.x<b.x;
}
bool IsBeforeY(Point& a, Point& b){
    return a.y<b.y;
}

double dist(Point& a, Point& b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n){
    if (n == 1){
        return 10000;
    }
    double d1 = ClosestPair(p, n/2);
    double d2 = ClosestPair(p + n/2, n - n/2);
    double d = min(d1, d2);

    Point* window = new Point[n];
    int size = 0;
    double mid = p[n/2].x;
    for (int i = 0; i < n; i++) {
        if (fabs(p[i].x - mid) < d) {
            window[size] = p[i];
            size++;
        }
    }
    MergeSort(window, size, IsBeforeY);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (window[j].y - window[i].y)<d; j++) {
            d = min(d, dist(window[i], window[j]));
        }
    }

    delete[] window;
    return d;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    while(true){
        cin>>n;
        if(n==0)
            break;
        Point* points=new Point[n];
        for(int i=0;i<n;i++){
            double x,y;
            cin>>x>>y;
            points[i].x=x;
            points[i].y=y;
        }
        MergeSort(points,n,IsBeforeX);
        double output= ClosestPair(points,n);
        if(output>=10000)
            cout<<"INFINITY"<<endl;
        else
            cout << fixed << setprecision(4) << output << endl;
        delete[] points;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
