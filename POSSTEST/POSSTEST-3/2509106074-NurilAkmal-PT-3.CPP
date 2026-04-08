#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct Kereta {
    int    nomorKereta;
    char   namaKereta[50];
    char   asal[30];
    char   tujuan[30];
    char   jamBerangkat[10];
    char   jamTiba[10];
    double hargaTiket;
    int    kursiTersedia;
};

struct Penumpang {
    int    idTransaksi;
    char   namaPenumpang[50];
    int    nomorKeretaDipilih;
    char   namaKeretaDipilih[50];
    char   rute[70];
    double totalBayar;
};

const int MAX_KERETA  = 100;
const int MAX_ANTRIAN = 50;
const int MAX_STACK   = 50;

Kereta    daftarKereta[MAX_KERETA];
int       jumlahKereta   = 0;

Penumpang antrianTiket[MAX_ANTRIAN];
int       frontAntrian   = 0;
int       rearAntrian    = 0;
int       jumlahAntrian  = 0;

Penumpang riwayatStack[MAX_STACK];
int       topStack       = -1;
int       counterTransaksi = 1;
void garisTebal(int lebar = 80) {
    for (int i = 0; i < lebar; i++) cout << '=';
    cout << '\n';
}
void garisTipis(int lebar = 80) {
    for (int i = 0; i < lebar; i++) cout << '-';
    cout << '\n';
}
void headerTabelKereta() {
    garisTebal();
    cout << left
         << setw(5)  << "No"
         << setw(8)  << "Nomor"
         << setw(22) << "Nama Kereta"
         << setw(14) << "Asal"
         << setw(14) << "Tujuan"
         << setw(8)  << "Brgkt"
         << setw(8)  << "Tiba"
         << setw(12) << "Harga (Rp)"
         << setw(7)  << "Kursi"
         << '\n';
    garisTipis();
}
void cetakBarisKereta(int idx, const Kereta* p) {
    cout << left
         << setw(5)  << (idx + 1)
         << setw(8)  << p->nomorKereta
         << setw(22) << p->namaKereta
         << setw(14) << p->asal
         << setw(14) << p->tujuan
         << setw(8)  << p->jamBerangkat
         << setw(8)  << p->jamTiba
         << setw(12) << fixed << setprecision(0) << p->hargaTiket
         << setw(7)  << p->kursiTersedia
         << '\n';
}

void cetakDetailPenumpang(const Penumpang* p) {
    garisTipis(60);
    cout << "  Nama Penumpang : " << p->namaPenumpang                       << '\n';
    cout << "  Kereta         : " << p->namaKeretaDipilih
         << " (No. " << p->nomorKeretaDipilih << ")"                        << '\n';
    cout << "  Rute           : " << p->rute                                << '\n';
    cout << "  Total Bayar    : Rp "
         << fixed << setprecision(0) << p->totalBayar                       << '\n';
    garisTipis(60);
}

void tampilSemuaKereta(Kereta* arr, int n) {
    cout << "\n  *** DAFTAR SEMUA KERETA ***\n";
    if (n == 0) {
        cout << "  [!] Belum ada data kereta.\n";
        return;
    }
    headerTabelKereta();
    for (int i = 0; i < n; i++) cetakBarisKereta(i, arr + i);
    garisTebal();
    cout << "  Total: " << n << " kereta terdaftar.\n";
}

void tambahKereta() {
    if (jumlahKereta >= MAX_KERETA) {
        cout << "\n  [!] Data penuh! Maksimum " << MAX_KERETA << " kereta.\n";
        return;
    }
    Kereta* k = daftarKereta + jumlahKereta;
    cout << "\n  === TAMBAH DATA KERETA BARU ===\n";
    cout << "  Nomor Kereta    : "; cin >> k->nomorKereta; cin.ignore();
    cout << "  Nama Kereta     : "; cin.getline(k->namaKereta, 50);
    cout << "  Kota Asal       : "; cin.getline(k->asal, 30);
    cout << "  Kota Tujuan     : "; cin.getline(k->tujuan, 30);
    cout << "  Jam Berangkat   : "; cin.getline(k->jamBerangkat, 10);
    cout << "  Jam Tiba        : "; cin.getline(k->jamTiba, 10);
    cout << "  Harga Tiket (Rp): "; cin >> k->hargaTiket;
    cout << "  Kursi Tersedia  : "; cin >> k->kursiTersedia;
    cin.ignore();
    jumlahKereta++;
    cout << "\n  [v] Data kereta berhasil ditambahkan!\n";
}

Kereta* cariKeretaByNomor(Kereta* arr, int n, int nomor) {
    for (int i = 0; i < n; i++)
        if ((arr + i)->nomorKereta == nomor) return arr + i;
    return nullptr;
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}


void linearSearchRute(Kereta* arr, int n) {
    if (n == 0) { cout << "\n  [!] Data kosong.\n"; return; }

    char cariAsal[30], cariTujuan[30];
    cin.ignore();
    cout << "\n  === LINEAR SEARCH (RUTE) ===\n";
    cout << "  Kota Asal   : "; cin.getline(cariAsal, 30);
    cout << "  Kota Tujuan : "; cin.getline(cariTujuan, 30);
    cout << "\n  Proses pencarian:\n";
    garisTipis(70);

    bool ditemukan   = false;
    int  jumlahHasil = 0;

    for (int i = 0; i < n; i++) {
        Kereta* p = arr + i;
        cout << "  Iterasi " << setw(3) << (i + 1)
             << " | [" << i << "] "
             << setw(22) << p->namaKereta
             << " | " << setw(12) << p->asal << "-> " << p->tujuan;

        if (strcasecmp(p->asal, cariAsal) == 0 && strcasecmp(p->tujuan, cariTujuan) == 0) {
            cout << "  <<< COCOK!\n";
            if (!ditemukan) { cout << "\n  --- HASIL ---\n"; headerTabelKereta(); }
            cetakBarisKereta(jumlahHasil++, p);
            ditemukan = true;
        } else {
            cout << "  (tidak cocok)\n";
        }
    }

    garisTipis(70);
    if (!ditemukan)
        cout << "\n  [!] Kereta rute " << cariAsal << " -> " << cariTujuan << " tidak ditemukan.\n";
    else {
        garisTebal();
        cout << "  Ditemukan: " << jumlahHasil << " kereta dari " << n << " data.\n";
    }
}

void sortByNomor(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if ((arr + j)->nomorKereta > (arr + j + 1)->nomorKereta)
                swapKereta(arr + j, arr + j + 1);
}

void jumpSearchNomor(Kereta* arr, int n) {
    if (n == 0) { cout << "\n  [!] Data kosong.\n"; return; }

    int cariNomor;
    cout << "\n  === JUMP SEARCH (NOMOR KERETA) ===\n";
    cout << "  Masukkan Nomor Kereta: "; cin >> cariNomor;

    Kereta temp[MAX_KERETA];
    for (int i = 0; i < n; i++) temp[i] = *(arr + i);
    sortByNomor(temp, n);

    int step    = (int)sqrt((double)n);
    int prev    = 0;
    int iterasi = 0;

    cout << "\n  Data diurutkan. Step = sqrt(" << n << ") = " << step << "\n";
    cout << "\n  [FASE 1] Lompat antar blok:\n";
    garisTipis(70);

    while (prev < n && (temp + (min(step, n) - 1))->nomorKereta < cariNomor) {
        iterasi++;
        int ujungBlok = min(step, n) - 1;
        cout << "  Jump " << setw(2) << iterasi
             << " | Blok [" << prev << ".." << ujungBlok << "]"
             << " | ujung=" << (temp + ujungBlok)->nomorKereta
             << " < " << cariNomor << " -> lompat\n";
        prev  = step;
        step += (int)sqrt((double)n);
        if (prev >= n) break;
    }

    int batasAtas = min(step, n) - 1;
    cout << "\n  [FASE 2] Linear dalam blok [" << prev << ".." << batasAtas << "]:\n";
    garisTipis(70);

    bool ketemu = false;
    for (int i = prev; i <= batasAtas; i++) {
        iterasi++;
        int nomorSaat = (temp + i)->nomorKereta;
        cout << "  Linear " << setw(2) << iterasi
             << " | [" << i << "] nomor=" << nomorSaat;

        if (nomorSaat == cariNomor) {
            cout << "  <<< DITEMUKAN!\n";
            cout << "\n  --- HASIL ---\n";
            headerTabelKereta();
            cetakBarisKereta(0, temp + i);
            garisTebal();
            ketemu = true;
            break;
        } else if (nomorSaat > cariNomor) {
            cout << " > " << cariNomor << " -> berhenti\n";
            break;
        } else {
            cout << " != " << cariNomor << " -> lanjut\n";
        }
    }

    garisTipis(70);
    if (!ketemu)
        cout << "\n  [!] Kereta nomor " << cariNomor << " tidak ditemukan.\n";
    cout << "  Total iterasi: " << iterasi << " dari " << n << " data.\n";
}


void merge(Kereta* arr, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++) L[i] = *(arr + kiri + i);
    for (int j = 0; j < n2; j++) R[j] = *(arr + tengah + 1 + j);

    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (strcasecmp(L[i].namaKereta, R[j].namaKereta) <= 0)
            *(arr + k++) = L[i++];
        else
            *(arr + k++) = R[j++];
    }
    while (i < n1) *(arr + k++) = L[i++];
    while (j < n2) *(arr + k++) = R[j++];

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
    cout << "\n  === MERGE SORT: Nama Kereta A-Z ===\n";
    mergeSort(arr, 0, n - 1);
    cout << "  [v] Diurutkan berdasarkan nama.\n\n";
    tampilSemuaKereta(arr, n);
}

void selectionSortHarga(Kereta* arr, int n) {
    cout << "\n  === SELECTION SORT: Harga Termurah ===\n";
    for (int i = 0; i < n - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < n; j++)
            if ((arr + j)->hargaTiket < (arr + idxMin)->hargaTiket)
                idxMin = j;
        if (idxMin != i) swapKereta(arr + i, arr + idxMin);
    }
    cout << "  [v] Diurutkan berdasarkan harga tiket.\n\n";
    tampilSemuaKereta(arr, n);
}


void enqueue(Penumpang* queue, int& rear, int& jumlah, Penumpang* dataBaru) {
    if (jumlah >= MAX_ANTRIAN) {
        cout << "\n  [OVERFLOW] Antrian penuh! Maksimum " << MAX_ANTRIAN << " penumpang.\n";
        return;
    }
    *(queue + rear) = *dataBaru;
    rear = (rear + 1) % MAX_ANTRIAN;
    jumlah++;
    cout << "\n  [v] " << dataBaru->namaPenumpang
         << " berhasil masuk antrian. (Posisi ke-" << jumlah << ")\n";
}

bool dequeue(Penumpang* queue, int& front, int& jumlah, Penumpang* hasil) {
    if (jumlah == 0) {
        cout << "\n  [UNDERFLOW] Antrian kosong! Tidak ada penumpang.\n";
        return false;
    }
    *hasil = *(queue + front);
    front  = (front + 1) % MAX_ANTRIAN;
    jumlah--;
    return true;
}

void peekAntrian(Penumpang* queue, int front, int jumlah) {
    cout << "\n  === PEEK ANTRIAN (Penumpang Terdepan) ===\n";
    if (jumlah == 0) {
        cout << "  [!] Antrian kosong.\n";
        return;
    }
    cetakDetailPenumpang(queue + front);
}

void tampilAntrian(Penumpang* queue, int front, int jumlah) {
    cout << "\n  === DAFTAR ANTRIAN TIKET ===\n";
    if (jumlah == 0) {
        cout << "  [!] Antrian kosong.\n";
        return;
    }
    garisTebal();
    cout << left
         << setw(5)  << "Pos"
         << setw(22) << "Nama Penumpang"
         << setw(8)  << "No KA"
         << setw(22) << "Nama Kereta"
         << setw(28) << "Rute"
         << setw(14) << "Total Bayar"
         << '\n';
    garisTipis();
    for (int i = 0; i < jumlah; i++) {
        Penumpang* p = queue + ((front + i) % MAX_ANTRIAN);
        cout << left
             << setw(5)  << (i + 1)
             << setw(22) << p->namaPenumpang
             << setw(8)  << p->nomorKeretaDipilih
             << setw(22) << p->namaKeretaDipilih
             << setw(28) << p->rute
             << "Rp " << fixed << setprecision(0) << p->totalBayar
             << '\n';
    }
    garisTebal();
    cout << "  Total antrian: " << jumlah << " penumpang.\n";
}

void menuEnqueue() {
    tampilSemuaKereta(daftarKereta, jumlahKereta);
    if (jumlahKereta == 0) return;

    Penumpang baru;
    cout << "\n  === PESAN TIKET (MASUK ANTRIAN) ===\n";
    cin.ignore();
    cout << "  Nama Penumpang     : "; cin.getline(baru.namaPenumpang, 50);

    int nomor;
    cout << "  Nomor Kereta       : "; cin >> nomor; cin.ignore();

    Kereta* k = cariKeretaByNomor(daftarKereta, jumlahKereta, nomor);
    if (k == nullptr) {
        cout << "\n  [!] Kereta nomor " << nomor << " tidak ditemukan.\n";
        return;
    }
    if (k->kursiTersedia <= 0) {
        cout << "\n  [!] Maaf, kursi " << k->namaKereta << " sudah habis.\n";
        return;
    }

    baru.idTransaksi        = 0;
    baru.nomorKeretaDipilih = k->nomorKereta;
    strcpy(baru.namaKeretaDipilih, k->namaKereta);
    strcpy(baru.rute, k->asal);
    strcat(baru.rute, " -> ");
    strcat(baru.rute, k->tujuan);
    baru.totalBayar = k->hargaTiket;

    enqueue(antrianTiket, rearAntrian, jumlahAntrian, &baru);
}


void push(Penumpang* stack, int& top, Penumpang* data) {
    if (top >= MAX_STACK - 1) {
        cout << "\n  [OVERFLOW] Riwayat penuh! Maksimum " << MAX_STACK << " transaksi.\n";
        return;
    }
    top++;
    *(stack + top) = *data;
    cout << "\n  [v] Transaksi #" << data->idTransaksi
         << " atas nama " << data->namaPenumpang << " dicatat.\n";
}

bool pop(Penumpang* stack, int& top, Penumpang* hasil) {
    if (top == -1) {
        cout << "\n  [UNDERFLOW] Riwayat kosong! Tidak ada transaksi.\n";
        return false;
    }
    *hasil = *(stack + top);
    top--;
    return true;
}

void peekStack(Penumpang* stack, int top) {
    cout << "\n  === PEEK RIWAYAT (Transaksi Terakhir) ===\n";
    if (top == -1) {
        cout << "  [!] Riwayat kosong.\n";
        return;
    }
    Penumpang* p = stack + top;
    garisTipis(60);
    cout << "  ID Transaksi   : #" << p->idTransaksi << '\n';
    cetakDetailPenumpang(p);
}

void tampilRiwayat(Penumpang* stack, int top) {
    cout << "\n  === RIWAYAT TRANSAKSI ===\n";
    if (top == -1) {
        cout << "  [!] Belum ada riwayat transaksi.\n";
        return;
    }
    garisTebal();
    cout << left
         << setw(5)  << "No"
         << setw(8)  << "ID Trx"
         << setw(22) << "Nama Penumpang"
         << setw(8)  << "No KA"
         << setw(22) << "Nama Kereta"
         << setw(28) << "Rute"
         << setw(14) << "Total Bayar"
         << '\n';
    garisTipis();
    for (int i = top; i >= 0; i--) {
        Penumpang* p = stack + i;
        cout << left
             << setw(5)  << (top - i + 1)
             << setw(8)  << p->idTransaksi
             << setw(22) << p->namaPenumpang
             << setw(8)  << p->nomorKeretaDipilih
             << setw(22) << p->namaKeretaDipilih
             << setw(28) << p->rute
             << "Rp " << fixed << setprecision(0) << p->totalBayar
             << '\n';
    }
    garisTebal();
    cout << "  Total riwayat: " << (top + 1) << " transaksi.\n";
}


void menuDequeue() {
    cout << "\n  === PROSES TIKET (DEQUEUE) ===\n";
    Penumpang hasil;
    if (!dequeue(antrianTiket, frontAntrian, jumlahAntrian, &hasil)) return;

    cout << "\n  [>] Memproses tiket: " << hasil.namaPenumpang << '\n';
    cetakDetailPenumpang(&hasil);

    hasil.idTransaksi = counterTransaksi++;

    Kereta* k = cariKeretaByNomor(daftarKereta, jumlahKereta, hasil.nomorKeretaDipilih);
    if (k != nullptr && k->kursiTersedia > 0) {
        k->kursiTersedia--;
        cout << "  Sisa kursi " << k->namaKereta << ": " << k->kursiTersedia << '\n';
    }

    push(riwayatStack, topStack, &hasil);
    cout << "  [v] Tiket diproses! ID Transaksi: #" << hasil.idTransaksi << '\n';
}

void menuPopRiwayat() {
    cout << "\n  === BATALKAN TRANSAKSI TERAKHIR (POP) ===\n";
    Penumpang hasil;
    if (!pop(riwayatStack, topStack, &hasil)) return;

    cout << "\n  [!] Transaksi dibatalkan:\n";
    garisTipis(60);
    cout << "  ID Transaksi   : #" << hasil.idTransaksi << '\n';
    cetakDetailPenumpang(&hasil);

    Kereta* k = cariKeretaByNomor(daftarKereta, jumlahKereta, hasil.nomorKeretaDipilih);
    if (k != nullptr) {
        k->kursiTersedia++;
        cout << "  [v] Kursi dikembalikan. Sisa " << k->namaKereta
             << ": " << k->kursiTersedia << '\n';
    }
    cout << "  [v] Transaksi #" << hasil.idTransaksi << " berhasil dibatalkan.\n";
}

void menuPeekGabungan() {
    peekAntrian(antrianTiket, frontAntrian, jumlahAntrian);
    peekStack(riwayatStack, topStack);
}

void initDataAwal() {
    daftarKereta[0] = {101, "Argo Bromo Anggrek", "Jakarta",    "Surabaya",   "08:00", "17:00", 350000, 50};
    daftarKereta[1] = {202, "Gajayana",           "Malang",     "Jakarta",    "17:30", "06:00", 420000, 60};
    daftarKereta[2] = {305, "Bima",               "Jakarta",    "Surabaya",   "17:00", "02:30", 500000, 40};
    daftarKereta[3] = {114, "Lodaya",             "Bandung",    "Solo",       "07:00", "14:00", 275000, 80};
    daftarKereta[4] = {450, "Taksaka",            "Yogyakarta", "Jakarta",    "08:00", "14:30", 320000, 64};
    daftarKereta[5] = {222, "Malabar",            "Bandung",    "Malang",     "16:00", "05:00", 380000, 72};
    daftarKereta[6] = {333, "Sancaka",            "Surabaya",   "Yogyakarta", "06:00", "11:00", 200000, 90};
    daftarKereta[7] = {409, "Argo Lawu",          "Solo",       "Jakarta",    "08:00", "15:00", 450000, 55};
    daftarKereta[8] = {515, "Purwojaya",          "Jakarta",    "Cilacap",    "07:30", "14:00", 150000, 100};
    daftarKereta[9] = {618, "Cirebon Ekspres",    "Jakarta",    "Cirebon",    "06:00", "09:00", 120000, 120};
    jumlahKereta    = 10;
}

void tampilMenu() {
    cout << "\n";
    garisTebal();
    cout << "       SISTEM MANAJEMEN KEBERANGKATAN KERETA API\n";
    garisTebal();
    cout << "  [ DATA KERETA ]\n";
    cout << "   1. Tampil Semua Jadwal Kereta\n";
    cout << "   2. Tambah Data Kereta Baru\n";
    cout << "   3. Cari Kereta by Rute   (Linear Search)\n";
    cout << "   4. Cari Kereta by Nomor  (Jump Search)\n";
    cout << "   5. Urutkan by Nama       (Merge Sort A-Z)\n";
    cout << "   6. Urutkan by Harga      (Selection Sort Termurah)\n";
    cout << "\n  [ ANTRIAN & TRANSAKSI ]\n";
    cout << "   7.  Pesan Tiket          (Enqueue ke Antrian)\n";
    cout << "   8.  Proses Tiket         (Dequeue dari Antrian)\n";
    cout << "   9.  Tampil Antrian       (Semua isi Queue)\n";
    cout << "   10. Tampil Riwayat       (Semua isi Stack)\n";
    cout << "   11. Batalkan Transaksi   (Pop dari Stack)\n";
    cout << "   12. Peek Antrian & Riwayat\n";
    cout << "\n   0.  Keluar\n";
    garisTipis();
    cout << "  Pilih menu: ";
}

int main() {
    initDataAwal();

    int pilihan;
    do {
        tampilMenu();
        cin >> pilihan;

        switch (pilihan) {
            case  1: tampilSemuaKereta(daftarKereta, jumlahKereta);            break;
            case  2: tambahKereta();                                            break;
            case  3: linearSearchRute(daftarKereta, jumlahKereta);             break;
            case  4: jumpSearchNomor(daftarKereta, jumlahKereta);              break;
            case  5: urutNamaKereta(daftarKereta, jumlahKereta);               break;
            case  6: selectionSortHarga(daftarKereta, jumlahKereta);           break;
            case  7: menuEnqueue();                                             break;
            case  8: menuDequeue();                                             break;
            case  9: tampilAntrian(antrianTiket, frontAntrian, jumlahAntrian); break;
            case 10: tampilRiwayat(riwayatStack, topStack);                    break;
            case 11: menuPopRiwayat();                                          break;
            case 12: menuPeekGabungan();                                        break;
            case  0: cout << "\n  Terima kasih! Program selesai.\n\n";         break;
            default: cout << "\n  [!] Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}