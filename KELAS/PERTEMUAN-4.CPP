#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 100

// ===== STACK =====
int stackArr[10], top = -1;

// ===== QUEUE =====
int queueArr[10], front = -1, rear = -1;

// ===== UNDO REDO =====
string undoStack[MAX], redoStack[MAX];
int topUndo = -1, topRedo = -1;

// ===== UI =====
void garis(){
    cout << "=====================================\n";
}

void header(string judul){
    garis();
    cout << "        " << judul << endl;
    garis();
}

void pause(){
    cout << "\nTekan ENTER...";
    cin.ignore();
    cin.get();
}

// ================= STACK =================
void pushStack(){
    int x;
    if(top == 9){
        cout << "⚠ Stack penuh!\n";
    } else {
        cout << "Input: ";
        cin >> x;
        stackArr[++top] = x;
        cout << "✔ Berhasil push\n";
    }
}

void popStack(){
    if(top == -1){
        cout << "⚠ Stack kosong!\n";
    } else {
        cout << "✔ Pop: " << stackArr[top--] << endl;
    }
}

void tampilStack(){
    if(top == -1){
        cout << "[ Kosong ]\n";
    } else {
        for(int i = top; i >= 0; i--){
            cout << "| " << setw(3) << stackArr[i] << " |\n";
        }
    }
}

// ================= QUEUE =================
void enqueue(){
    int x;
    if(rear == 9){
        cout << "⚠ Queue penuh!\n";
    } else {
        cout << "Input: ";
        cin >> x;
        if(front == -1) front = 0;
        queueArr[++rear] = x;
        cout << "✔ Berhasil enqueue\n";
    }
}

void dequeue(){
    if(front == -1 || front > rear){
        cout << "⚠ Queue kosong!\n";
    } else {
        cout << "✔ Dequeue: " << queueArr[front++] << endl;
    }
}

void tampilQueue(){
    if(front == -1 || front > rear){
        cout << "[ Kosong ]\n";
    } else {
        for(int i = front; i <= rear; i++){
            cout << "| " << setw(3) << queueArr[i] << " | ";
        }
        cout << endl;
    }
}

// ================= UNDO REDO =================
void pushUndo(string aksi){
    if(topUndo < MAX-1) undoStack[++topUndo] = aksi;
}

void pushRedo(string aksi){
    if(topRedo < MAX-1) redoStack[++topRedo] = aksi;
}

string popUndo(){
    if(topUndo >= 0) return undoStack[topUndo--];
    return "";
}

string popRedo(){
    if(topRedo >= 0) return redoStack[topRedo--];
    return "";
}

void clearRedo(){
    topRedo = -1;
}

void tambahAksi(){
    string aksi;
    cout << "Masukkan aksi: ";
    cin.ignore();
    getline(cin, aksi);
    pushUndo(aksi);
    clearRedo();
    cout << "✔ Aksi ditambahkan\n";
}

void undo(){
    if(topUndo == -1){
        cout << "⚠ Tidak ada undo\n";
    } else {
        string temp = popUndo();
        pushRedo(temp);
        cout << "✔ Undo: " << temp << endl;
    }
}

void redo(){
    if(topRedo == -1){
        cout << "⚠ Tidak ada redo\n";
    } else {
        string temp = popRedo();
        pushUndo(temp);
        cout << "✔ Redo: " << temp << endl;
    }
}

void tampilUndoRedo(){
    cout << "\n-- Undo Stack --\n";
    if(topUndo == -1) cout << "Kosong\n";
    else{
        for(int i = topUndo; i >= 0; i--)
            cout << undoStack[i] << endl;
    }

    cout << "\n-- Redo Stack --\n";
    if(topRedo == -1) cout << "Kosong\n";
    else{
        for(int i = topRedo; i >= 0; i--)
            cout << redoStack[i] << endl;
    }
}

// ================= MENU =================
void menuStack(){
    int p;
    do{
        header("MENU STACK");
        cout << "1. Push\n2. Pop\n3. Tampil\n4. Kembali\n";
        cout << "Pilih: ";
        cin >> p;

        switch(p){
            case 1: pushStack(); break;
            case 2: popStack(); break;
            case 3: tampilStack(); break;
        }
        if(p != 4) pause();
    }while(p != 4);
}

void menuQueue(){
    int p;
    do{
        header("MENU QUEUE");
        cout << "1. Enqueue\n2. Dequeue\n3. Tampil\n4. Kembali\n";
        cout << "Pilih: ";
        cin >> p;

        switch(p){
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: tampilQueue(); break;
        }
        if(p != 4) pause();
    }while(p != 4);
}

void menuUndoRedo(){
    int p;
    do{
        header("MENU UNDO REDO");
        cout << "1. Tambah Aksi\n2. Undo\n3. Redo\n4. Tampil\n5. Kembali\n";
        cout << "Pilih: ";
        cin >> p;

        switch(p){
            case 1: tambahAksi(); break;
            case 2: undo(); break;
            case 3: redo(); break;
            case 4: tampilUndoRedo(); break;
        }
        if(p != 5) pause();
    }while(p != 5);
}

// ================= MAIN =================
int main(){
    int pilih;

    do{
        header("APLIKASI STRUKTUR DATA");
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "3. Undo & Redo\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih){
            case 1: menuStack(); break;
            case 2: menuQueue(); break;
            case 3: menuUndoRedo(); break;
            case 4: cout << "Terima kasih!\n"; break;
            default: cout << "❌ Salah!\n";
        }

        if(pilih != 4) pause();

    }while(pilih != 4);

    return 0;
}