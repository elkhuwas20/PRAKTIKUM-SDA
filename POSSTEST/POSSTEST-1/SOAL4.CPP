#include <iostream>
using namespace std;

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a, b;
    cout << "Masukkan nilai a: ";
    cin >> a;
    cout << "masukan nilai b: ";
    cin >> b;

    cout << "Sebelum swap:" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    Swap(&a, &b);

    cout << "\nSetelah swap:" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    return 0;
}