#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Struktur data untuk menyimpan informasi pelanggan
struct Customer {
    int id;
    string name;
    string address;
    string phoneNumber;
};

// Struktur data untuk menyimpan informasi pesanan laundry
struct LaundryOrder {
    int customerId;
    string laundryType;
    int quantity;
    int totalPrice;
    bool isCompleted;
};

// Vector untuk menyimpan data pelanggan dan pesanan laundry
vector<Customer> customers;
vector<LaundryOrder> orders;

// Fungsi untuk menghasilkan ID pelanggan secara otomatis
int generateCustomerId() {
    static int idCounter = 1;
    return idCounter++;
}

// Fungsi untuk menambahkan data pelanggan
void addCustomer() {
    Customer customer;
    customer.id = generateCustomerId();

    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, customer.name);

    cout << "Masukkan Alamat Pelanggan: ";
    getline(cin, customer.address);

    cout << "Masukkan Nomor Telepon Pelanggan: ";
    getline(cin, customer.phoneNumber);

    customers.push_back(customer);
}

// Fungsi untuk menampilkan data pelanggan berdasarkan ID
void displayCustomerById(int customerId) {
    auto it = find_if(customers.begin(), customers.end(), [customerId](const Customer& c) {
        return c.id == customerId;
    });

    if (it != customers.end()) {
        cout << "ID Pelanggan: " << it->id << endl;
        cout << "Nama: " << it->name << endl;
        cout << "Alamat: " << it->address << endl;
        cout << "Nomor Telepon: " << it->phoneNumber << endl;
    } else {
        cout << "Pelanggan tidak ditemukan." << endl;
    }
}

// Fungsi untuk menambahkan pesanan laundry
void placeOrder() {
    LaundryOrder order;
    order.customerId = generateCustomerId();

    cout << "Jenis Cucian (kapas/katun/wol/pakaian biasa): ";
    cin >> order.laundryType;

    cout << "Jumlah Cucian (g): ";
    cin >> order.quantity;

    // Menghitung total biaya berdasarkan jenis cucian
    if (order.laundryType == "kapas") {
        order.totalPrice = order.quantity * 500 / 100;
    } else if (order.laundryType == "katun") {
        order.totalPrice = order.quantity * 250 / 100;
    } else if (order.laundryType == "wol") {
        order.totalPrice = order.quantity * 750 / 100;
    } else if (order.laundryType == "pakaian biasa") {
        order.totalPrice = order.quantity * 200 / 100;
    } else {
        cout << "Jenis cucian tidak valid." << endl;
        return;
    }

    order.isCompleted = false;
    orders.push_back(order);

    cout << "Pesanan berhasil ditempatkan." << endl;
}

// Fungsi untuk menampilkan daftar pesanan yang belum selesai
void displayPendingOrders() {
    cout << "Daftar Pesanan Belum Selesai:" << endl;
    for (const auto& order : orders) {
        if (!order.isCompleted) {
            cout << "ID Pelanggan: " << order.customerId << " | Jenis Cucian: " << order.laundryType
                 << " | Jumlah: " << order.quantity << "g | Total Biaya: Rp. " << order.totalPrice
                 << " | Status: Belum Selesai" << endl;
        }
    }
}

// Fungsi untuk menandai pesanan sebagai selesai
void markOrderCompleted(int customerId) {
    auto it = find_if(orders.begin(), orders.end(), [customerId](const LaundryOrder& order) {
        return order.customerId == customerId && !order.isCompleted;
    });

    if (it != orders.end()) {
        it->isCompleted = true;
        cout << "Pesanan telah selesai dan dapat diambil." << endl;
    } else {
        cout << "Pesanan tidak ditemukan atau sudah selesai." << endl;
    }
}

// Fungsi untuk menampilkan riwayat pesanan yang sudah selesai
void displayCompletedOrders() {
    cout << "Riwayat Pesanan Selesai:" << endl;
    for (const auto& order : orders) {
        if (order.isCompleted) {
            cout << "ID Pelanggan: " << order.customerId << " | Jenis Cucian: " << order.laundryType
                 << " | Jumlah: " << order.quantity << "g | Total Biaya: Rp. " << order.totalPrice
                 << " | Status: Selesai" << endl;
        }
    }
}

int main() {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Input data pelanggan\n";
        cout << "2. Pemesanan layanan laundry\n";
        cout << "3. Menampilkan daftar pesanan yang belum selesai\n";
        cout << "4. Menandai pesanan sebagai selesai\n";
        cout << "5. Menampilkan riwayat pesanan yang sudah selesai\n";
        cout << "6. Mencari dan menampilkan data pelanggan berdasarkan ID\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu (0-6): ";
        cin >> choice;
        cin.ignore();  // Membersihkan buffer

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                placeOrder();
                break;
            case 3:
                displayPendingOrders();
                break;
            case 4:
                int customerId;
                cout << "Masukkan ID Pelanggan untuk menandai pesanan sebagai selesai: ";
                cin >> customerId;
                markOrderCompleted(customerId);
                break;
            case 5:
                displayCompletedOrders();
                break;
            case 6:
                int searchCustomerId;
                cout << "Masukkan ID Pelanggan untuk mencari dan menampilkan data: ";
                cin >> searchCustomerId;
                displayCustomerById(searchCustomerId);
                break;
            case 0:
                cout << "Program selesai. Terima kasih!";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.";
        }

    } while (choice != 0);

    return 0;
}

