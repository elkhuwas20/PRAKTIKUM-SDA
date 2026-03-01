#include <iostream>
using namespace std;
int FindMin(int A[]) {
    int min = A[0];
    for (int i = 1; i < 8; i++) {
        if (A[i] < min) {
            min = A[i];
        }
    }
    return min;
}
int main() {
    int fib[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int min = FindMin(fib);
    int index;
    for (int i = 0; i < 8; i++) {
        if (fib[i] == min) {
            index = i;
            break;
        }
    }

    cout << "Nilai minimum array fib: " << min << endl;
    cout << "Indeks nilai minimum: " << index << endl;

    return 0;
}

/*
===========================================================
Analisis Kompleksitas Waktu Algoritma FindMin
===========================================================

Tabel Kompleksitas:

┌─────────────────────────────────────────────────────────┐
│     Pseudocode        │  Cost  │   Tmin    │   Tmax     │
├─────────────────────────────────────────────────────────┤
│ procedure            │   C1    │    1      │    1       │
│ min ← A[0]           │   C2    │    1      │    1       │
│ for i=1 to n-1       │   C3    │    n      │    n       │
│ if A[i] < min        │   C4    │   n-1     │   n-1      │
│ min ← A[i]           │   C5    │    0      │   n-1      │
│ end if               │   C6    │   n-1     │   n-1      │
│ end for              │   C7    │    n      │    n       │
│ return min           │   C8    │    1      │    1       │
│ end procedure        │   C9    │    1      │    1       │
└─────────────────────────────────────────────────────────┘


Best Case:
Tmin(n) = C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8 + C9
        = 4n + 2
Big-O   = O(n)


Worst Case:
Tmax(n) = C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8 + C9
        = 5n + 1
Big-O   = O(n)


Kesimpulan:
Kompleksitas waktu algoritma FindMin pada Best Case dan Worst Case adalah O(n)
karena hanya memiliki satu perulangan tanpa nested loop.
*/