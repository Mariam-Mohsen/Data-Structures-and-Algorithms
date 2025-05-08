#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value* new_arr = new Value[sz];
            for (int i = 0; i < n; ++i)
                new_arr[i] = arr[i];
            delete[] arr;
            arr = new_arr;
        }
        arr[n++] = v;
    }

    void RemoveLast() {
        if (n == 0) return;
        n--;
    }

    Value& operator[](int i) {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node() : character('\0'), frequency(0), left(NULL), right(NULL) {}
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap {
    int* pos;
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) {
        IsBefore = _IsBefore;
        a.Initialize();
        pos = new int[n];
        for (int i = 0; i < n; i++) {
            pos[i] = -1;
        }
    }

    void Destroy() {
        delete[] pos;
        a.Destroy();
    }

    int Child(int i) {
        return 2 * i + 1;
    }

    int Parent(int i) {
        return (i - 1) / 2;
    }

    Elem GetFirst() {
        return a[0];
    }

    Elem RetrieveFirst() {
        Elem f = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return f;
    }

    void Add(Elem e) {
        a.AddLast(e);
        MoveUp(a.n - 1);
    }

    void MoveUp(int ind) {
        if (ind == 0) return;
        int parent = Parent(ind);
        if (IsBefore(a[ind], a[parent])) {
            Elem temp = a[ind];
            a[ind] = a[parent];
            a[parent] = temp;
            MoveUp(parent);
        }
    }

    void MoveDown(int ind) {
        int l = Child(ind);
        int r = l + 1;
        int small = ind;
        if (l < a.n && IsBefore(a[l], a[small])){
            small = l;
        }
        if (r < a.n && IsBefore(a[r], a[small])){
            small = r;
        }
        if (small != ind) {
            Elem x = a[ind];
            a[ind] = a[small];
            a[small] = x;
            MoveDown(small);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool compare_freq(Node& a, Node& b) {
    return a.frequency < b.frequency;
}
void print(Node* root, string code = "") {
    if (!root){
        return;
    }


    if (!root->left && !root->right) {
        cout << root->character << ": " << code << endl;
    }

    print(root->left, code + "0");
    print(root->right, code + "1");
}

void huffman_coding(char characters[], int frequencies[], int n) {
    Heap<Node> heap;
    heap.Initialize(compare_freq, n);
    for (int i = 0; i < n; i++) {
        Node node;
        node.character = characters[i];
        node.frequency = frequencies[i];
        heap.Add(node);
    }


    while (heap.a.n > 1) {
        Node left = heap.RetrieveFirst();
        Node right = heap.RetrieveFirst();

        Node merged;
        merged.character = '\0';
        merged.frequency = left.frequency + right.frequency;
        merged.left = new Node(left);
        merged.right = new Node(right);

        heap.Add(merged);
    }
    Node* root = new Node(heap.RetrieveFirst());

    print(root);

    heap.Destroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n;
    cout << "enter num of characters: ";
    cin >> n;

    char* characters = new char[n];
    int* frequencies = new int[n];

    cout << "enter characters and freq:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> characters[i] >> frequencies[i];
    }

    huffman_coding(characters, frequencies, n);

    delete[] characters;
    delete[] frequencies;

    return 0;
}

