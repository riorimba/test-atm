#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cctype>

using namespace std;

// User struct
struct User {
    string norek;
    string pin;
    int saldo = 0;
    string role;
};

// Global variables
const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 3;
bool isNumeric = true;

//test akun
void blueprintUserAndAdmin() {
    users[0].norek = "1234567890";
    users[0].pin = "123456";
    users[0].saldo = 1000000;
    users[0].role = "admin";

    users[1].norek = "1234567891";
    users[1].pin = "123456";
    users[1].saldo = 1000000;
    users[1].role = "user";

    users[2].norek = "1234567892";
    users[2].pin = "123456";
    users[2].saldo = 1000000;
    users[2].role = "user";
}

//Validasi
bool isValidNumericNorek(const string& norek) {
    if (norek.length() == 10) {
        for (char c : norek) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool isValidNumericPin(const string& pin) {
    if (pin.length() == 6) {
        for (char c : pin) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool isUniqueNorek(const string& norek) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            return false;
        }
    }
    return true;
}
void hidePin(string& pin) {
    char ch;
    pin = "";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (pin.length() > 0) {
                cout << "\b \b";
                pin.pop_back();
            }
        }
        else if (isdigit(ch) && pin.length() < 6) {
            cout << '*';
            pin.push_back(ch);
        }
    }
    cout << endl;

    // Memastikan pin memiliki panjang 6 karakter dan berupa digit.
    if (!isValidNumericPin(pin)) {
        cout << "Pin harus 6 digit angka.\nMasukkan Pin: ";
        hidePin(pin);
    }
}

//register login
void registerUser() {
    string norek, pin;

    cout << "Masukkan norek (10 digit angka): ";
    cin >> norek;

    if (isValidNumericNorek(norek) && isUniqueNorek(norek)) {
        cout << "Masukkan pin: ";
        hidePin(pin);

        if (userCount < MAX_USERS) {
            users[userCount].norek = norek;
            users[userCount].pin = pin;
            users[userCount].role = "user"; // Default role 'user'
            users[userCount].saldo = 1000000; // Default saldo 1.000.000
            userCount++;
            cout << "User Berhasil di daftarkan!" << endl;
        }
        else {
            cout << "User mencapai limit. Tidak dapat menambahkan user lagi." << endl;
        }
    }
    else {
        cout << "norek tidak valid atau sudah terdaftar. Norek harus berupa angka 10 digit dan unik." << endl;
    }
}
bool loginUser(const string& norek, const string& pin, string& role, User& currentUser) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek && users[i].pin == pin) {
            /*saldo = users[i].saldo;*/
            role = users[i].role;
            currentUser = users[i];
            return true;
        }
    }
    return false;
}

//dashboard admin
void registerUserByAdmin() {
    string norek, pin, role;
    int saldo;

    cout << "Masukkan norek (10 digit angka): ";
    cin >> norek;

    if (isValidNumericNorek(norek) && isUniqueNorek(norek)) {
        cout << "Masukkan pin: ";
        hidePin(pin);

        do {
            cout << "Masukkan role (admin/user): ";
            cin >> role;
            if (role != "admin" && role != "user") {
                cout << "Role tidak valid. Masukkan 'admin' atau 'user'." << endl;
            }
        } while (role != "admin" && role != "user");

        cout << "Masukkan saldo awal akun: ";
        cin >> saldo;

        if (userCount < MAX_USERS) {
            users[userCount].norek = norek;
            users[userCount].pin = pin;
            users[userCount].role = role; 
            users[userCount].saldo = saldo; 
            userCount++;
            cout << "User Berhasil di daftarkan!" << endl;
        }
        else {
            cout << "User mencapai limit. Tidak dapat menambahkan user lagi." << endl;
        }
    }
    else {
        cout << "norek tidak valid atau sudah terdaftar. Norek harus berupa angka 10 digit dan unik." << endl;
    }
}
void editUserByNorek() {
    string norek;

    cout << "Masukkan nomor rekening pengguna yang ingin diubah: ";
    cin >> norek;

    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            // Meminta input baru dari pengguna
            string newNorek, newPin, newRole;
            int newSaldo;

            cout << "Masukkan nomor rekening baru: ";
            cin >> newNorek;

            // Validasi nomor rekening baru
            if (isValidNumericNorek(newNorek) && isUniqueNorek(newNorek)) {
                cout << "Masukkan pin baru: ";
                hidePin(newPin);
                cout << "Masukkan role baru (admin/user): ";
                cin >> newRole;
                cout << "Masukkan saldo baru: ";
                cin >> newSaldo;

                // Mengganti informasi pengguna dengan informasi baru
                users[i].norek = newNorek;
                users[i].pin = newPin;
                users[i].role = newRole;
                users[i].saldo = newSaldo;

                cout << "Informasi pengguna berhasil diubah." << endl;
                return;
            }
            else {
                cout << "Nomor rekening baru tidak valid atau sudah terdaftar." << endl;
                return;
            }
        }
    }

    cout << "Pengguna dengan nomor rekening " << norek << " tidak ditemukan." << endl;
}
void deleteUserByNorek() {
    string norek;
    cout << "Masukkan nomor rekening pengguna yang ingin dihapus: ";
    cin >> norek;

    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            char confirm;
            cout << "Apakah Anda yakin ingin menghapus pengguna dengan nomor rekening " << norek << "? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                // Menghapus pengguna dari array dengan menggeser elemen-elemen setelahnya
                for (int j = i; j < userCount - 1; ++j) {
                    users[j] = users[j + 1];
                }
                userCount--; // Mengurangi jumlah pengguna setelah penghapusan
                cout << "Pengguna dengan nomor rekening " << norek << " berhasil dihapus." << endl;
            }
            else {
                cout << "Pengguna dengan nomor rekening " << norek << " tidak dihapus." << endl;
            }
            return;
        }
    }
    cout << "Pengguna dengan nomor rekening " << norek << " tidak ditemukan." << endl;
}
void adminDashboard() {
    int choice;
    do {
        cout << "\n=== DASHBOARD ADMIN ===" << endl;
        cout << "1. Daftarkan Nasabah/Admin" << endl;
        cout << "2. Edit Nasabah" << endl;
        cout << "3. Hapus Akun Nasabah" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih opsi : ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUserByAdmin();
            break;
        case 2:
             editUserByNorek();
            break;
        case 3:
             deleteUserByNorek();
            break;
        case 4:
            cout << "Keluar dari Dashboard Admin." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (choice != 4);
    
    
};

//dashboard user
void showBalance(User& currentUser) {
    cout << "Saldo Anda: IDR. " << currentUser.saldo << endl;
}
void withdrawMoney(User& currentUser) {
    int tarik;

    cout << "Masukkan jumlah uang yang ingin ditarik: ";
    cin >> tarik;

    if (tarik > 0 && tarik <= currentUser.saldo) {
        currentUser.saldo -= tarik;
        cout << "Penarikan berhasil. Saldo Anda sekarang: IDR. " << currentUser.saldo << endl;
    }
    else {
        cout << "Jumlah uang tidak valid atau saldo tidak mencukupi." << endl;
    }
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == currentUser.norek) {
            users[i].saldo = currentUser.saldo;
            break;
        }
    }
    return;
}
void transferMoney(User& user) {
    string norek;
    int transfer;

    cout << "Masukkan nomor rekening tujuan: ";
    cin >> norek;

    if (!isValidNumericNorek(norek)) {
        cout << "Nomor rekening tidak valid." << endl;
        return;
    }

    cout << "Masukkan jumlah uang yang ingin ditransfer: IDR. ";
    while (!(cin >> transfer) || transfer <= 0) {
        cout << "Jumlah uang yang dimasukkan tidak valid. Silakan coba lagi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (transfer > user.saldo) {
        cout << "Saldo tidak mencukupi untuk melakukan transfer sebesar itu." << endl;
        return;
    }

    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            users[i].saldo += transfer;
            user.saldo -= transfer;
            cout << "Transfer berhasil ke norek " << norek << endl;
            cout << " Saldo Anda sekarang : IDR. " << user.saldo << endl; 
            return;
        }
    }

    cout << "Nomor rekening tujuan tidak ditemukan." << endl;
}
void userDashboard(User& currentUser) {
    int choice;

    while (true) {
        cout << "\n=== DASHBOARD USER ===\n";
        cout << "Menu Transaksi: \n";
        cout << "1. Tampilkan saldo\n";
        cout << "2. Tarik Tunai\n";
        cout << "3. Transfer\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showBalance(currentUser);
            break;
        case 2:
            withdrawMoney(currentUser);
            break;
        case 3:
            transferMoney(currentUser);
            break;
        case 4:
            for (int i = 0; i < userCount; ++i) {
                if (users[i].norek == currentUser.norek) {
                    users[i].saldo = currentUser.saldo;
                    break;
                }
            }
            return;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }
};

int main() {
    string norek, pin, role;
    int choice;


    blueprintUserAndAdmin();
    User currentUser;

    do {
        cout << "\n=== ATM ===" << endl;
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Pilih Opsi: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            cout << "Masukkan norek: ";
            cin >> norek;
            cout << "Masukkan pin: ";
            hidePin(pin);

            if (loginUser(norek, pin, role, currentUser)) {
                if (role == "admin") {
                    cout << "\nBerhasil login sebagai ADMIN! Selamat datang, " << norek << "!" << endl;
                    //dashboard admin
                    adminDashboard();
                }
                else {
                    cout << "\nBerhasil Login! Selamat Datang, " << norek << "!" << endl;
                    //dashboard user
                    userDashboard(currentUser);
                }
            }
            else {
                cout << "\nNorek atau Password tidak valid. Silahkan coba lagi." << endl;
            }
            break;
        case 3:
            cout << "Keluar dari program. Selamat Tinggal!" << endl;
            break;
        default:
            cout << "Kesalahan pemilihan. Coba lagi." << endl;
        }
    } while (choice != 3);

    return 0;
}