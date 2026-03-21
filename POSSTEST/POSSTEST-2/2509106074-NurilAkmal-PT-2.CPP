#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct Kereta {
    int nomorKereta;
    char namaKereta[50];
    char asal[30];
    char tujuan[30];
    char jamBerangkat[10];
    char jamTiba[10];
    double hargaTiket;
    int kursiTersedia;
};

const int MAX_KERETA = 100;
Kereta daftarKereta[MAX_KERETA];
int jumlahKereta = 0;

void garisHorizontal(int lebar = 80) {
    for (int i = 0; i < lebar; i++) cout << '=';
    cout << '\n';
}

void garisTipis(int lebar = 80) {
    for (int i = 0; i < lebar; i++) cout << '-';
    cout << '\n';
}

void headerTabel() {
    garisHorizontal();
    cout << left
         << setw(5) << "No"
         << setw(8) << "Nomor"
         << setw(22) << "Nama Kereta"
         << setw(14) << "Asal"
         << setw(14) << "Tujuan"
         << setw(8) << "Brgkt"
         << setw(8) << "Tiba"
         << setw(12) << "Harga (Rp)"
         << setw(7) << "Kursi"
         << '\n';
    garisTipis();
}

void cetakBaris(int idx, const Kereta* p) {
    cout << left
         << setw(5) << (idx + 1)
         << setw(8) << p->nomorKereta
         << setw(22) << p->namaKereta
         << setw(14) << p->asal
         << setw(14) << p->tujuan
         << setw(8) << p->jamBerangkat
         << setw(8) << p->jamTiba
         << setw(12) << fixed << setprecision(0) << p->hargaTiket
         << setw(7) << p->kursiTersedia
         << '\n';
}

void tampilSemuaKereta(Kereta* arr, int n) {
    if (n == 0) {
        cout << "\n  [!] Belum ada data kereta.\n";
        return;
    }
    cout << "\n  *** DAFTAR SEMUA KERETA ***\n";
    headerTabel();
    for (int i = 0; i < n; i++) {
        cetakBaris(i, arr + i);
    }
    garisHorizontal();
    cout << "  Total: " << n << " kereta terdaftar.\n";
}

void tambahKereta() {
    if (jumlahKereta >= MAX_KERETA) {
        cout << "\n  [!] Data penuh!\n";
        return;
    }

    Kereta* k = daftarKereta + jumlahKereta;

    cout << "\n  === TAMBAH DATA KERETA BARU ===\n";
    cout << "  Nomor Kereta    : ";
    cin >> k->nomorKereta;
    cin.ignore();
    cout << "  Nama Kereta     : ";
    cin.getline(k->namaKereta, 50);
    cout << "  Kota Asal       : ";
    cin.getline(k->asal, 30);
    cout << "  Kota Tujuan     : ";
    cin.getline(k->tujuan, 30);
    cout << "  Jam Berangkat   : ";
    cin.getline(k->jamBerangkat, 10);
    cout << "  Jam Tiba        : ";
    cin.getline(k->jamTiba, 10);
    cout << "  Harga Tiket (Rp): ";
    cin >> k->hargaTiket;
    cout << "  Kursi Tersedia  : ";
    cin >> k->kursiTersedia;
    cin.ignore();

    jumlahKereta++;
    cout << "\n  [v] Data kereta berhasil ditambahkan!\n";
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void linearSearchRute(Kereta* arr, int n) {
    if (n == 0) {
        cout << "\n  [!] Data kosong.\n";
        return;
    }

    char cariAsal[30], cariTujuan[30];
    cin.ignore();
    cout << "\n  === LINEAR SEARCH (RUTE) ===\n";
    cout << "  Kota Asal   : ";
    cin.getline(cariAsal, 30);
    cout << "  Kota Tujuan : ";
    cin.getline(cariTujuan, 30);

    cout << "\n  Proses pencarian (periksa satu per satu dari awal):\n";
    garisTipis(70);

    bool ditemukan = false;
    int jumlahHasil = 0;

    // i = indeks elemen yang sedang diperiksa, dimulai dari 0
    // setiap putaran loop = 1 iterasi pencarian
    for (int i = 0; i < n; i++) {

        // Langkah 1: arahkan pointer p ke elemen indeks i
        // (arr + i) = alamat elemen ke-i dalam array
        Kereta* p = arr + i;

        // Langkah 2: tampilkan posisi dan isi elemen yang sedang dicek
        cout << "  Iterasi " << setw(3) << (i + 1)
             << " | indeks[" << i << "]"
             << " | " << setw(22) << p->namaKereta
             << " | " << setw(13) << p->asal
             << "-> " << p->tujuan;

        // Langkah 3: bandingkan field asal dan tujuan dengan input pencarian
        // strcasecmp: perbandingan tidak peka huruf besar/kecil
        bool cocokAsal = (strcasecmp(p->asal, cariAsal) == 0);
        bool cocokTujuan = (strcasecmp(p->tujuan, cariTujuan) == 0);

        // Langkah 4: evaluasi hasil perbandingan
        if (cocokAsal && cocokTujuan) {
            // kedua field cocok -> elemen ini adalah hasil pencarian
            cout << "  <<< COCOK!\n";
            if (!ditemukan) {
                cout << "\n  --- HASIL DITEMUKAN ---\n";
                headerTabel();
            }
            cetakBaris(jumlahHasil++, p);
            ditemukan = true;
            // tidak break -> terus cek sisa elemen (mungkin ada rute sama)
        } else {
            // salah satu atau keduanya tidak cocok -> lewati, lanjut ke i+1
            cout << "  (tidak cocok)\n";
        }
        // Langkah 5: i++ -> pindah ke elemen berikutnya (otomatis oleh for)
    }

    garisTipis(70);
    if (!ditemukan) {
        cout << "\n  [!] Tidak ditemukan kereta dengan rute "
             << cariAsal << " -> " << cariTujuan << ".\n";
    } else {
        garisHorizontal();
        cout << "  Total ditemukan: " << jumlahHasil << " kereta"
             << " (diperiksa " << n << " elemen).\n";
    }
}

void sortByNomor(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->nomorKereta > (arr + j + 1)->nomorKereta) {
                swapKereta(arr + j, arr + j + 1);
            }
        }
    }
}

void jumpSearchNomor(Kereta* arr, int n) {
    if (n == 0) {
        cout << "\n  [!] Data kosong.\n";
        return;
    }

    int cariNomor;
    cout << "\n  === JUMP SEARCH (NOMOR KERETA) ===\n";
    cout << "  Masukkan Nomor Kereta: ";
    cin >> cariNomor;

    Kereta temp[MAX_KERETA];
    for (int i = 0; i < n; i++) {
        temp[i] = *(arr + i);
    }
    sortByNomor(temp, n);

    // hitung ukuran lompatan optimal = akar kuadrat dari jumlah data
    // contoh: n=10 -> step=3, artinya cek indeks 2, 5, 8, dst
    int step = (int)sqrt((double)n);
    int prev = 0;
    int iterasi = 0;

    cout << "\n  Data diurutkan dulu. Ukuran lompatan (step) = sqrt(" << n << ") = " << step << "\n";
    cout << "\n  [FASE 1] Lompat antar blok untuk cari blok yang berisi target:\n";
    garisTipis(70);

    // kondisi lanjut lompat:
    // (a) prev masih dalam batas array (prev < n)
    // (b) nilai elemen di ujung blok saat ini masih kurang dari target
    //     -> berarti target pasti ada di blok berikutnya
    while (prev < n && (temp + (min(step, n) - 1))->nomorKereta < cariNomor) {
        iterasi++;
        int ujungBlok = min(step, n) - 1;

        cout << "  Jump iterasi " << setw(2) << iterasi
             << " | Blok [" << prev << ".." << ujungBlok << "]"
             << " | Cek ujung indeks[" << ujungBlok << "]"
             << " nomor=" << (temp + ujungBlok)->nomorKereta;

        // nilai ujung blok < target -> blok ini tidak mengandung target
        // maju ke blok berikutnya: geser prev dan step sejauh 1 blok
        cout << " < " << cariNomor << " -> lompat ke blok berikutnya\n";

        prev = step;
        step += (int)sqrt((double)n);
        if (prev >= n) break;
    }

    int batasAtas = min(step, n) - 1;
    cout << "\n  [FASE 2] Linear search dalam blok [" << prev << ".." << batasAtas << "]:\n";
    garisTipis(70);

    // setelah blok kandidat ditemukan, periksa elemen satu per satu
    // dari indeks prev hingga batasAtas
    // ini linear search biasa tapi hanya pada sebagian kecil data
    bool ketemu = false;
    for (int i = prev; i <= batasAtas; i++) {
        iterasi++;

        // ambil pointer ke elemen indeks i, lalu bandingkan nomorKereta
        cout << "  Linear iterasi " << setw(2) << iterasi
             << " | indeks[" << i << "]"
             << " | nomorKereta=" << (temp + i)->nomorKereta;

        if ((temp + i)->nomorKereta == cariNomor) {
            // nomor cocok -> TARGET DITEMUKAN
            cout << "  <<< DITEMUKAN!\n";
            cout << "\n  --- HASIL ---\n";
            headerTabel();
            cetakBaris(0, temp + i);
            garisHorizontal();
            ketemu = true;
            break;
        } else if ((temp + i)->nomorKereta > cariNomor) {
            // karena data terurut: jika sudah lebih besar, target pasti tidak ada
            cout << " > " << cariNomor << " -> target tidak ada, hentikan\n";
            break;
        } else {
            cout << " != " << cariNomor << " (tidak cocok, lanjut)\n";
        }
    }

    garisTipis(70);
    if (!ketemu) {
        cout << "\n  [!] Kereta nomor " << cariNomor << " tidak ditemukan.\n";
    }
    cout << "  Total iterasi keseluruhan: " << iterasi << " (dari " << n << " data)\n";
}

void merge(Kereta* arr, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = *(arr + kiri + i);
    }
    for (int j = 0; j < n2; j++) {
        R[j] = *(arr + tengah + 1 + j);
    }

    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (strcasecmp(L[i].namaKereta, R[j].namaKereta) <= 0) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        *(arr + k) = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        *(arr + k) = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Kereta* arr, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);
        merge(arr, kiri, tengah, kanan);
    }
}

void urutNamaKereta(Kereta* arr, int n) {
    cout << "\n  === MERGE SORT: Urutkan Nama Kereta (A-Z) ===\n";
    mergeSort(arr, 0, n - 1);
    cout << "  [v] Data berhasil diurutkan berdasarkan nama kereta.\n\n";
    tampilSemuaKereta(arr, n);
}

void selectionSortHarga(Kereta* arr, int n) {
    cout << "\n  === SELECTION SORT: Urutkan Harga Tiket (Termurah) ===\n";
    for (int i = 0; i < n - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargaTiket < (arr + idxMin)->hargaTiket) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            swapKereta(arr + i, arr + idxMin);
        }
    }
    cout << "  [v] Data berhasil diurutkan berdasarkan harga tiket.\n\n";
    tampilSemuaKereta(arr, n);
}

void initDataAwal() {
    daftarKereta[0].nomorKereta = 101;
    strcpy(daftarKereta[0].namaKereta, "Argo Bromo Anggrek");
    strcpy(daftarKereta[0].asal, "Jakarta");
    strcpy(daftarKereta[0].tujuan, "Surabaya");
    strcpy(daftarKereta[0].jamBerangkat, "08:00");
    strcpy(daftarKereta[0].jamTiba, "17:00");
    daftarKereta[0].hargaTiket = 350000;
    daftarKereta[0].kursiTersedia = 50;

    daftarKereta[1].nomorKereta = 202;
    strcpy(daftarKereta[1].namaKereta, "Gajayana");
    strcpy(daftarKereta[1].asal, "Malang");
    strcpy(daftarKereta[1].tujuan, "Jakarta");
    strcpy(daftarKereta[1].jamBerangkat, "17:30");
    strcpy(daftarKereta[1].jamTiba, "06:00");
    daftarKereta[1].hargaTiket = 420000;
    daftarKereta[1].kursiTersedia = 60;

    daftarKereta[2].nomorKereta = 305;
    strcpy(daftarKereta[2].namaKereta, "Bima");
    strcpy(daftarKereta[2].asal, "Jakarta");
    strcpy(daftarKereta[2].tujuan, "Surabaya");
    strcpy(daftarKereta[2].jamBerangkat, "17:00");
    strcpy(daftarKereta[2].jamTiba, "02:30");
    daftarKereta[2].hargaTiket = 500000;
    daftarKereta[2].kursiTersedia = 40;

    daftarKereta[3].nomorKereta = 114;
    strcpy(daftarKereta[3].namaKereta, "Lodaya");
    strcpy(daftarKereta[3].asal, "Bandung");
    strcpy(daftarKereta[3].tujuan, "Solo");
    strcpy(daftarKereta[3].jamBerangkat, "07:00");
    strcpy(daftarKereta[3].jamTiba, "14:00");
    daftarKereta[3].hargaTiket = 275000;
    daftarKereta[3].kursiTersedia = 80;

    daftarKereta[4].nomorKereta = 450;
    strcpy(daftarKereta[4].namaKereta, "Taksaka");
    strcpy(daftarKereta[4].asal, "Yogyakarta");
    strcpy(daftarKereta[4].tujuan, "Jakarta");
    strcpy(daftarKereta[4].jamBerangkat, "08:00");
    strcpy(daftarKereta[4].jamTiba, "14:30");
    daftarKereta[4].hargaTiket = 320000;
    daftarKereta[4].kursiTersedia = 64;

    daftarKereta[5].nomorKereta = 222;
    strcpy(daftarKereta[5].namaKereta, "Malabar");
    strcpy(daftarKereta[5].asal, "Bandung");
    strcpy(daftarKereta[5].tujuan, "Malang");
    strcpy(daftarKereta[5].jamBerangkat, "16:00");
    strcpy(daftarKereta[5].jamTiba, "05:00");
    daftarKereta[5].hargaTiket = 380000;
    daftarKereta[5].kursiTersedia = 72;

    daftarKereta[6].nomorKereta = 333;
    strcpy(daftarKereta[6].namaKereta, "Sancaka");
    strcpy(daftarKereta[6].asal, "Surabaya");
    strcpy(daftarKereta[6].tujuan, "Yogyakarta");
    strcpy(daftarKereta[6].jamBerangkat, "06:00");
    strcpy(daftarKereta[6].jamTiba, "11:00");
    daftarKereta[6].hargaTiket = 200000;
    daftarKereta[6].kursiTersedia = 90;

    daftarKereta[7].nomorKereta = 409;
    strcpy(daftarKereta[7].namaKereta, "Argo Lawu");
    strcpy(daftarKereta[7].asal, "Solo");
    strcpy(daftarKereta[7].tujuan, "Jakarta");
    strcpy(daftarKereta[7].jamBerangkat, "08:00");
    strcpy(daftarKereta[7].jamTiba, "15:00");
    daftarKereta[7].hargaTiket = 450000;
    daftarKereta[7].kursiTersedia = 55;

    daftarKereta[8].nomorKereta = 515;
    strcpy(daftarKereta[8].namaKereta, "Purwojaya");
    strcpy(daftarKereta[8].asal, "Jakarta");
    strcpy(daftarKereta[8].tujuan, "Cilacap");
    strcpy(daftarKereta[8].jamBerangkat, "07:30");
    strcpy(daftarKereta[8].jamTiba, "14:00");
    daftarKereta[8].hargaTiket = 150000;
    daftarKereta[8].kursiTersedia = 100;

    daftarKereta[9].nomorKereta = 618;
    strcpy(daftarKereta[9].namaKereta, "Cirebon Ekspres");
    strcpy(daftarKereta[9].asal, "Jakarta");
    strcpy(daftarKereta[9].tujuan, "Cirebon");
    strcpy(daftarKereta[9].jamBerangkat, "06:00");
    strcpy(daftarKereta[9].jamTiba, "09:00");
    daftarKereta[9].hargaTiket = 120000;
    daftarKereta[9].kursiTersedia = 120;

    jumlahKereta = 10;
}

void tampilMenu() {
    cout << "\n";
    garisHorizontal();
    cout << "       SISTEM MANAJEMEN KEBERANGKATAN KERETA API\n";
    garisHorizontal();
    cout << "  1. Tampil Semua Jadwal Kereta\n";
    cout << "  2. Tambah Data Kereta Baru\n";
    cout << "  3. Cari Kereta by Rute  (Linear Search)\n";
    cout << "  4. Cari Kereta by Nomor (Jump Search)\n";
    cout << "  5. Urutkan by Nama      (Merge Sort A-Z)\n";
    cout << "  6. Urutkan by Harga     (Selection Sort Termurah)\n";
    cout << "  0. Keluar\n";
    garisTipis();
    cout << "  Pilih menu: ";
}

int main() {
    initDataAwal();

    int pilihan;
    do {
        tampilMenu();
        cin >> pilihan;

        if (pilihan == 1) {
            tampilSemuaKereta(daftarKereta, jumlahKereta);
        } else if (pilihan == 2) {
            tambahKereta();
        } else if (pilihan == 3) {
            linearSearchRute(daftarKereta, jumlahKereta);
        } else if (pilihan == 4) {
            jumpSearchNomor(daftarKereta, jumlahKereta);
        } else if (pilihan == 5) {
            urutNamaKereta(daftarKereta, jumlahKereta);
        } else if (pilihan == 6) {
            selectionSortHarga(daftarKereta, jumlahKereta);
        } else if (pilihan == 0) {
            cout << "\n  Terima kasih! Program selesai.\n\n";
        } else {
            cout << "\n  [!] Pilihan tidak valid. Coba lagi.\n";
        }

    } while (pilihan != 0);

    return 0;
}