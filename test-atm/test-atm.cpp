#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cctype>

using namespace std;

struct User {
    string norek;
    string pin;
    int saldo;
    string role;
};

const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 1;
bool isNumeric = true;

void blueprintUserAdmin() {
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

//bool isNumeric(const string& input) {
//    for (char ch : input) {
//        if (!isdigit(ch)) {
//            return false;
//        }
//    }
//    return true;
//}

//Validasi
bool isValidNumericUsername(const string& norek) {
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
bool isUniqueUsername(const string& norek) {
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
User* findUserByNorek(const string& norek) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            return &users[i]; // Mengembalikan alamat memori objek User yang sesuai dengan nomor rekening
        }
    }
    return nullptr; // Mengembalikan nullptr jika pengguna tidak ditemukan
}

//register login
void registerUser() {
    string norek, pin;

    cout << "Masukkan norek (10 digit angka): ";
    cin >> norek;

    if (isValidNumericUsername(norek) && isUniqueUsername(norek)) {
        cout << "Masukkan pin: ";
        hidePin(pin);

        if (userCount < MAX_USERS) {
            users[userCount].norek = norek;
            users[userCount].pin = pin;
            users[userCount].role = "user"; // Default role is user
            users[userCount].saldo = 1000000; // Default saldo is 1.000.000
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

//User* loginUser(const string& norek, const string& pin) {
//    for (int i = 0; i < userCount; ++i) {
//        if (users[i].norek == norek && users[i].pin == pin) {
//            return &users[i]; // Mengembalikan alamat memori dari pengguna yang berhasil login
//        }
//    }
//    return nullptr; // Mengembalikan nullptr jika login gagal
//}

bool loginUser(const string& norek, const string& pin, int& saldo, string& role) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek && users[i].pin == pin) {
            saldo = users[i].saldo;
            role = users[i].role;
            return true;
        }
    }
    return false;
}


//dashboard admin
void adminDashboard() {
    cout << "Selamat datang di dashboard admin!" << endl;
};

//dashboard user
void showBalance(int& saldo) {
    cout << "Saldo Anda: " << saldo << " IDR" << endl;
}
void withdrawMoney(int& saldo) {
    int amount;
    cout << "Masukkan jumlah uang yang ingin ditarik: ";
    cin >> amount;

    if (amount > 0 && amount <= saldo) {
        saldo -= amount;
        cout << "Penarikan berhasil. Saldo Anda sekarang: " << saldo << " IDR" << endl;
    }
    else {
        cout << "Jumlah uang tidak valid atau saldo tidak mencukupi." << endl;
    }
}
void transferMoney(User& user) {
	string norek;
	int amount;
	cout << "Masukkan nomor rekening tujuan: ";
	cin >> norek;

    if (isValidNumericUsername(norek)) {
		cout << "Masukkan jumlah uang yang ingin ditransfer: ";
		cin >> amount;

        if (amount > 0 && amount <= user.saldo) {
            for (int i = 0; i < userCount; ++i) {
                if (users[i].norek == norek) {
					users[i].saldo += amount;
					user.saldo -= amount;
					cout << "Transfer berhasil. Saldo Anda sekarang: " << user.saldo << " IDR" << endl;
					return;
				}
			}
			cout << "Nomor rekening tujuan tidak ditemukan." << endl;
		}
        else {
			cout << "Jumlah uang tidak valid atau saldo tidak mencukupi." << endl;
		}
	}
    else {
		cout << "Nomor rekening tidak valid." << endl;
	}
}   
void userDashboard(int& saldo, const string& norek) {
    int choice;

    while (true) {
        cout << "============================\n";
        cout << "Menu Transaksi: \n";
        cout << "1. Tampilkan saldo\n";
        cout << "2. Tarik Tunai\n";
        cout << "3. Transfer\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showBalance(saldo);
            break;
        case 2:
            withdrawMoney(saldo);
            break;
        case 3:
            //transferMoney(user);
            break;
        case 4:
            cout << "Kembali ke menu awal!\n";
            return;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }
};

int main() {
    string norek, pin, role;
    int choice, saldo = 0;
    //User user;

    blueprintUserAdmin();
    //User* user;
    User currentUser;

    do {
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
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

            if (loginUser(norek, pin, saldo, role)) {
                if (role == "admin") {
                    cout << "\nBerhasil login sebagai ADMIN! Selamat datang, " << norek << "!" << endl;
                    adminDashboard();
                    // Tampilkan tampilan khusus admin di sini
                }
                else {
                    cout << "\nBerhasil Login! Selamat Datang, " << norek << "!" << endl;
                    //cout << saldo << endl;
                    userDashboard(saldo, norek);
                    // Tampilkan tampilan khusus pengguna di sini
                }
            }
            else {
                cout << "\nInvalid username or password. Please try again." << endl;
            }
            break;
        case 3:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}