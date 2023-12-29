#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

// Struktur data untuk menyimpan informasi pelanggan
struct Customer {
    int id;
    std::string name;
    std::string address;
    std::string phoneNumber;
};

// Struktur data untuk menyimpan pesanan laundry
struct LaundryOrder {
    int orderId;
    int customerId;
    std::string laundryType;
    double quantity; // dalam gram
    double totalCost; // dalam rupiah
    bool isCompleted;
};

// Fungsi untuk menghitung total biaya berdasarkan jenis cucian
double calculateCost(const std::string& laundryType, double quantity) {
    if (laundryType == "kapas") {
        return 500 * (quantity / 100);
    } else if (laundryType == "katun") {
        return 250 * (quantity / 100);
    } else if (laundryType == "wol") {
        return 750 * (quantity / 100);
    } else if (laundryType == "pakaian_biasa") {
        return 200 * (quantity / 100);
    } else {
        return 0; // Jenis cucian tidak valid
    }
}

// Fungsi untuk menampilkan daftar pesanan yang belum selesai
void displayIncompleteOrders(const std::vector<LaundryOrder>& orders, const std::vector<Customer>& customers) {
    std::cout << "Daftar Pesanan Belum Selesai:\n";
    for (const auto& order : orders) {
        if (!order.isCompleted) {
            // Find the customer associated with the order
            auto customerIt = std::find_if(customers.begin(), customers.end(),
                                           [order](const Customer& c) { return c.id == order.customerId; });

            if (customerIt != customers.end()) {
                std::cout << "ID Pesanan: " << order.orderId << ", ID Pelanggan: " << order.customerId
                          << ", Nama Pelanggan: " << customerIt->name
                          << ", Jenis Cucian: " << order.laundryType << ", Jumlah: " << order.quantity
                          << " gram, Total Biaya: " << order.totalCost << " Rupiah\n";
            } else {
                std::cout << "ID Pesanan: " << order.orderId << ", ID Pelanggan: " << order.customerId
                          << ", (Nama Pelanggan tidak ditemukan)"
                          << ", Jenis Cucian: " << order.laundryType << ", Jumlah: " << order.quantity
                          << " gram, Total Biaya: " << order.totalCost << " Rupiah\n";
            }
        }
    }
}

int main() {
    std::vector<Customer> customers;
    std::vector<LaundryOrder> orders;

    int customerIdCounter = 1;
    int orderIdCounter = 1;

    char option;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Input data pelanggan\n";
        std::cout << "2. Pemesanan layanan laundry\n";
        std::cout << "3. Menampilkan daftar pesanan yang belum selesai\n";
        std::cout << "4. Menandai pesanan sebagai selesai\n";
        std::cout << "5. Menampilkan riwayat pesanan yang sudah selesai\n";
        std::cout << "6. Keluar\n";
        std::cout << "Pilih opsi (1-6): ";
        std::cin >> option;

        switch (option) {
            case '1': {
                Customer customer;
                customer.id = customerIdCounter++;
                std::cout << "Nama: ";
                std::cin.ignore(); // Ignore newline character in buffer
                std::getline(std::cin, customer.name);
                std::cout << "Alamat: ";
                std::getline(std::cin, customer.address);
                std::cout << "Nomor Telepon: ";
                std::cin >> customer.phoneNumber;
                customers.push_back(customer);
                std::cout << "Pelanggan berhasil ditambahkan. ID Pelanggan: " << customer.id << "\n";
                break;
            }
            case '2': {
                LaundryOrder order;
                order.orderId = orderIdCounter++;
                std::cout << "ID Pelanggan: ";
                std::cin >> order.customerId;
                std::cout << "Jenis Cucian (kapas/katun/wol/pakaian_biasa): ";
                std::cin >> order.laundryType;
                std::cout << "Jumlah Cucian (gram): ";
                std::cin >> order.quantity;
                order.totalCost = calculateCost(order.laundryType, order.quantity);
                order.isCompleted = false;
                orders.push_back(order);
                std::cout << "Pesanan laundry berhasil ditambahkan. ID Pesanan: " << order.orderId << "\n";
                break;
            }
            
            case '3': {
                displayIncompleteOrders(orders, customers);
                break;
            }
            case '4': {
                int orderId;
                std::cout << "Masukkan ID Pesanan yang sudah selesai: ";
                std::cin >> orderId;
                for (auto& order : orders) {
                    if (order.orderId == orderId) {
                        order.isCompleted = true;
                        std::cout << "Pesanan berhasil ditandai sebagai selesai.\n";
                        break;
                    }
                }
                break;
            }
            case '5': {
                // Display completed orders
                std::cout << "Riwayat Pesanan Selesai:\n";
                for (const auto& order : orders) {
                    if (order.isCompleted) {
                        auto customerIt = std::find_if(customers.begin(), customers.end(),
                                                       [order](const Customer& c) { return c.id == order.customerId; });

                        if (customerIt != customers.end()) {
                            std::cout << "ID Pesanan: " << order.orderId << ", ID Pelanggan: " << order.customerId
                                      << ", Nama Pelanggan: " << customerIt->name
                                      << ", Jenis Cucian: " << order.laundryType << ", Jumlah: " << order.quantity
                                      << " gram, Total Biaya: " << order.totalCost << " Rupiah\n";
                        } else {
                            std::cout << "ID Pesanan: " << order.orderId << ", ID Pelanggan: " << order.customerId
                                      << ", (Nama Pelanggan tidak ditemukan)"
                                      << ", Jenis Cucian: " << order.laundryType << ", Jumlah: " << order.quantity
                                      << " gram, Total Biaya: " << order.totalCost << " Rupiah\n";
                        }
                    }
                }
                break;
            }
            case '6': {
                std::cout << "Terima kasih. Keluar dari program.\n";
                break;
            }
            default: {
                std::cout << "Opsi tidak valid. Silakan pilih opsi 1-6.\n";
            }
        }
    } while (option != '6');

    return 0;
}

