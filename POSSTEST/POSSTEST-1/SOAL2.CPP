#include <iostream>
#include <string>
#include <limits>
#include <cmath>
using namespace std;
struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int jumlah = 5;
    Mahasiswa mhs[jumlah];

    cout << "===== INPUT DATA MAHASISWA =====" << endl;

    for (int i = 0; i < jumlah; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << endl;

        cout << "Nama : ";
        getline(cin, mhs[i].nama);

        cout << "NIM  : ";
        getline(cin, mhs[i].nim);

        while (true) {
            cout << "IPK (0 - 4, max 2 desimal): ";
            cin >> mhs[i].ipk;
            if (cin.fail()) {
                cout << "Input tidak valid! Harus angka.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (mhs[i].ipk < 0 || mhs[i].ipk > 4) {
                cout << "IPK harus antara 0 - 4!\n";
                continue;
            }

            if (floor(mhs[i].ipk * 100) != mhs[i].ipk * 100) {
                cout << "IPK maksimal 2 angka di belakang koma!\n";
                continue;
            }

            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int indeks_tertinggi = 0;
    for (int i = 1; i < jumlah; i++) {
        if (mhs[i].ipk > mhs[indeks_tertinggi].ipk) {
            indeks_tertinggi = i;
        }
    }

    cout << "\n===== MAHASISWA DENGAN IPK TERTINGGI =====" << endl;
    cout << "Nama : " << mhs[indeks_tertinggi].nama << endl;
    cout << "NIM  : " << mhs[indeks_tertinggi].nim << endl;
    cout << "IPK  : " << mhs[indeks_tertinggi].ipk << endl;

    return 0;
}