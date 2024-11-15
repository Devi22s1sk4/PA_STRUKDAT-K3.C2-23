#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Struktur untuk menyimpan data destinasi wisata
struct DestinasiWisata {
    int id;
    string namaWisata;
    string lokasi;
    double hargaTiket;
    DestinasiWisata* next;
};

// Stack
class Stack {
private:
    DestinasiWisata* top;
public:
    Stack() : top(nullptr) {}

    void push(DestinasiWisata* destinasi) {
        destinasi->next = top;
        top = destinasi;
    }

    DestinasiWisata* pop() {
        if (top == nullptr) return nullptr;
        DestinasiWisata* temp = top;
        top = top->next;
        return temp;
    }

    DestinasiWisata* peek() {
        return top;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Queue
class Queue {
private:
    DestinasiWisata* front;
    DestinasiWisata* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(DestinasiWisata* destinasi) {
        destinasi->next = nullptr;
        if (rear == nullptr) {
            front = rear = destinasi;
            return;
        }
        rear->next = destinasi;
        rear = destinasi;
    }

    DestinasiWisata* dequeue() {
        if (front == nullptr) return nullptr;
        DestinasiWisata* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        return temp;
    }

    DestinasiWisata* peekFront() {
        return front;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// Fungsi untuk menambahkan destinasi wisata (Create)
void tambahDestinasiWisata(DestinasiWisata*& head, int id, const string& nama, const string& lokasi, double harga) {
    DestinasiWisata* destinasiBaru = new DestinasiWisata;
    destinasiBaru->id = id;
    destinasiBaru->namaWisata = nama;
    destinasiBaru->lokasi = lokasi;
    destinasiBaru->hargaTiket = harga;
    destinasiBaru->next = head;
    head = destinasiBaru;
}

// Fungsi untuk menampilkan daftar destinasi wisata (Read)
void tampilkanDestinasi(DestinasiWisata* head) {
    if (head == nullptr) {
        cout << "Tidak ada destinasi wisata!" << endl;
        return;
    }
    DestinasiWisata* destinasi = head;
    while (destinasi != nullptr) {
        cout << "ID: " << destinasi->id << ", Nama: " << destinasi->namaWisata
            << ", Lokasi: " << destinasi->lokasi << ", Harga Tiket: Rp " << destinasi->hargaTiket << endl;
        destinasi = destinasi->next;
    }
}

// Fungsi untuk memperbarui destinasi wisata (Update)
void ubahDestinasiWisata(DestinasiWisata* head, int id, const string& namaBaru, const string& lokasiBaru, double hargaBaru) {
    DestinasiWisata* destinasi = head;
    while (destinasi != nullptr) {
        if (destinasi->id == id) {
            destinasi->namaWisata = namaBaru;
            destinasi->lokasi = lokasiBaru;
            destinasi->hargaTiket = hargaBaru;
            cout << "Destinasi wisata berhasil diperbarui!" << endl;
            return;
        }
        destinasi = destinasi->next;
    }
    cout << "Destinasi dengan ID " << id << " tidak ditemukan!" << endl;
}

// Fungsi untuk menghapus destinasi wisata (Delete)
void hapusDestinasiWisata(DestinasiWisata*& head, int id) {
    DestinasiWisata* current = head;
    DestinasiWisata* previous = nullptr;

    if (current != nullptr && current->id == id) {
        head = current->next;
        delete current;
        cout << "Destinasi wisata berhasil dihapus!" << endl;
        return;
    }

    while (current != nullptr && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Destinasi dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    previous->next = current->next;
    delete current;
    cout << "Destinasi wisata berhasil dihapus!" << endl;
}

// Fungsi Merge Sort
DestinasiWisata* merge(DestinasiWisata* left, DestinasiWisata* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->hargaTiket < right->hargaTiket) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

DestinasiWisata* mergeSort(DestinasiWisata* head) {
    if (head == nullptr || head->next == nullptr) return head;

    DestinasiWisata* mid = head;
    DestinasiWisata* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        mid = mid->next;
        fast = fast->next->next;
    }

    DestinasiWisata* left = head;
    DestinasiWisata* right = mid->next;
    mid->next = nullptr;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

// Fungsi Quick Sort
DestinasiWisata* partition(DestinasiWisata* low, DestinasiWisata* high) {
    double pivot = high->hargaTiket;
    DestinasiWisata* i = low->next;

    for (DestinasiWisata* j = low; j != high; j = j->next) {
        if (j->hargaTiket < pivot) {
            i = (i == nullptr) ? low : i->next;
            swap(i->hargaTiket, j->hargaTiket);
        }
    }
    swap(i->hargaTiket, high->hargaTiket);
    return i;
}

void quickSort(DestinasiWisata* low, DestinasiWisata* high) {
    if (low != nullptr && high != nullptr && low != high && low != high->next) {
        DestinasiWisata* p = partition(low, high);
        quickSort(low, p);
        quickSort(p->next, high);
    }
}

// Fungsi Pencarian: Fibonacci Search
void fibonacciSearch(DestinasiWisata* head, const string& key) {
    DestinasiWisata* temp = head;
    int index = 0;
    while (temp != nullptr) {
        if (temp->namaWisata == key) {
            cout << "Destinasi ditemukan: " << endl;
            cout << "ID: " << temp->id << ", Nama: " << temp->namaWisata
                 << ", Lokasi: " << temp->lokasi << endl;
            return;
        }
        temp = temp->next;
        index++;
    }
    cout << "Destinasi tidak ditemukan!" << endl;
}

// Fungsi Pencarian: Jump Search
void jumpSearch(DestinasiWisata* head, int key) {
    DestinasiWisata* temp = head;
    int index = 0;
    int prev = 0;
    while (temp != nullptr) {
        if (temp->id == key) {
            cout << "Destinasi ditemukan: " << endl;
            cout << "ID: " << temp->id << ", Nama: " << temp->namaWisata
                 << ", Lokasi: " << temp->lokasi << endl;
            return;
        }
        temp = temp->next;
        index++;
    }
    cout << "Destinasi tidak ditemukan!" << endl;
}

// Fungsi Pencarian: Boyer-Moore Search
void boyerMooreSearch(DestinasiWisata* head, const string& key) {
    DestinasiWisata* temp = head;
    while (temp != nullptr) {
        if (temp->lokasi == key) {
            cout << "Destinasi ditemukan: " << endl;
            cout << "ID: " << temp->id << ", Nama: " << temp->namaWisata
                 << ", Lokasi: " << temp->lokasi << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Destinasi tidak ditemukan!" << endl;
}

// Menu Utama
// Menu Utama
int main() {
    DestinasiWisata* head = nullptr;

    int option;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tambah Destinasi\n";
        cout << "2. Tampilkan Destinasi\n";
        cout << "3. Ubah Destinasi\n";
        cout << "4. Hapus Destinasi\n";
        cout << "5. Sorting Destinasi (Merge Sort)\n";
        cout << "6. Sorting Destinasi (Quick Sort)\n";
        cout << "7. Cari Destinasi (Fibonacci Search) berdasarkan Nama\n";
        cout << "8. Cari Destinasi (Jump Search) berdasarkan ID\n";
        cout << "9. Cari Destinasi (Boyer-Moore Search) berdasarkan Lokasi\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> option;

        if (option == 0) break;

        switch (option) {
            case 1: {
                int id;
                string nama, lokasi;
                double harga;
                cout << "Masukkan ID Destinasi: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Nama Destinasi: ";
                getline(cin, nama);
                cout << "Masukkan Lokasi: ";
                getline(cin, lokasi);
                cout << "Masukkan Harga Tiket: ";
                cin >> harga;
                tambahDestinasiWisata(head, id, nama, lokasi, harga);
                cout << "Destinasi berhasil ditambahkan!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 2:
                tampilkanDestinasi(head);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            case 3: {
                int id;
                string nama, lokasi;
                double harga;
                cout << "Masukkan ID Destinasi yang akan diubah: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Nama Baru: ";
                getline(cin, nama);
                cout << "Masukkan Lokasi Baru: ";
                getline(cin, lokasi);
                cout << "Masukkan Harga Baru: ";
                cin >> harga;
                ubahDestinasiWisata(head, id, nama, lokasi, harga);
                cout << "Destinasi berhasil diubah!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 4: {
                int id;
                cout << "Masukkan ID Destinasi yang akan dihapus: ";
                cin >> id;
                hapusDestinasiWisata(head, id);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 5: {
                head = mergeSort(head);
                cout << "Destinasi berhasil diurutkan menggunakan Merge Sort!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 6: {
                quickSort(head, head);
                cout << "Destinasi berhasil diurutkan menggunakan Quick Sort!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 7: {
                string key;
                cin.ignore();
                cout << "Masukkan Nama Destinasi untuk pencarian: ";
                getline(cin, key);
                fibonacciSearch(head, key);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 8: {
                int key;
                cout << "Masukkan ID Destinasi untuk pencarian: ";
                cin >> key;
                jumpSearch(head, key);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            case 9: {
                string key;
                cin.ignore();
                cout << "Masukkan Lokasi Destinasi untuk pencarian: ";
                getline(cin, key);
                boyerMooreSearch(head, key);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();  // Menunggu input Enter dari pengguna sebelum melanjutkan
                break;
            }
            default:
                cout << "Opsi tidak valid!" << endl;
                break;
        }
    }

    return 0;
}