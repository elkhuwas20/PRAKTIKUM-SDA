#include <iostream>
using namespace std;

struct Mahasiswa {
    int id;
    string nama;
    string prodi;
    string nim;
};

struct Node {
    Mahasiswa data;
    Node* next;
};

void traversal(Node* head) 
{
  if (head == nullptr)
  {
    cout << "List kosong" << endl;
    return;
  }

  Node *temp = head;
  while (temp != nullptr)
  {
    cout << "nama : " << temp->data.nama << endl;
    cout << "prodi : " << temp->data.prodi << endl;
    cout << "nim : " << temp->data.nim << endl;
    temp = temp->next;
    cout << endl;
  }
  cout << "Tidak ada data lagi" << endl;
}

void addfrist(Node** head, Mahasiswa mhs) {
  Node* newNode = new Node();
  newNode->data = mhs;
  newNode->next = *head;
  *head = newNode;
}

void addlast(Node** head, Mahasiswa mhs) {
  Node* newNode = new Node();
  newNode->data = mhs;
  newNode->next = nullptr;

  if (*head == nullptr) {
    *head = newNode;
    return;
  }

  Node* temp = *head;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void addmid(Node** head, Mahasiswa mhs, int posisi) {
  Node* newNode = new Node();
  newNode->data = mhs;

  if (*head == nullptr || posisi == 1) {
    newNode->next = *head;
    *head = newNode;
    return;
  }

  Node* temp = *head;
  for (int i = 1; i < posisi - 1 && temp != nullptr; i++) {
    temp = temp->next;
  }
  newNode->next = temp->next;
  temp->next = newNode;
}

int main() {
    Node* head = nullptr;
    int pilih = 0;

    cout << "==================================================\n";
    cout << "   PROGRAM SINGLE LINKED LIST - PRAKTIKUM SDA\n";
    cout << "==================================================\n\n";

    // Tambah 5 data contoh
    addlast(&head, {1, "Ahmad Rizki", "Teknik Informatika", "2509106001"});
    addlast(&head, {2, "Budi Santoso", "Teknik Komputer", "2509106002"});
    addlast(&head, {3, "Citra Dewi", "Sistem Informasi", "2509106003"});
    addlast(&head, {4, "Doni Pratama", "Teknik Informatika", "2509106004"});
    addlast(&head, {5, "Eka Putri", "Teknik Elektro", "2509106005"});

    cout << "Data awal sudah ditambahkan. Silakan pilih menu di bawah:\n\n";

    while (true) {
        cout << "Menu  : \n"
             << "0. Lihat Data\n"
             << "1. Add First\n"
             << "2. Add Last\n"
             << "3. Add Mid\n"
             << "4. Traversal\n"
             << "5. Exit\n";
        cout << "Pilih : ";
        cin >> pilih;

        Mahasiswa mhs;
        int posisi;

        switch (pilih) {
            case 0:
                traversal(head);
                break;
            case 1:
                cout << "Masukkan nama : ";
                cin >> mhs.nama;
                cout << "Masukkan prodi : ";
                cin >> mhs.prodi;
                cout << "Masukkan nim : ";
                cin >> mhs.nim;
                addfrist(&head, mhs);
                break;
            case 2:
                cout << "Masukkan nama : ";
                cin >> mhs.nama;
                cout << "Masukkan prodi : ";
                cin >> mhs.prodi;
                cout << "Masukkan nim : ";
                cin >> mhs.nim;
                addlast(&head, mhs);
                break;
            case 3:
                cout << "Masukkan nama : ";
                cin >> mhs.nama;
                cout << "Masukkan prodi : ";
                cin >> mhs.prodi;
                cout << "Masukkan nim : ";
                cin >> mhs.nim;
                cout << "Masukkan posisi : ";
                cin >> posisi;
                addmid(&head, mhs, posisi);
                break;              
            case 4:
                traversal(head);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                return 0;   
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
        cout << endl;
    }
    return 0;
}





