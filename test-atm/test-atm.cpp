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
    string status;
    int loginAttempts = 0;
};

// Global variables
const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 4;

//test akun
void blueprintUserAndAdmin() {
    users[0].norek = "1234567890";
    users[0].pin = "123456";
    users[0].saldo = 1000000;
    users[0].role = "admin";
    users[0].status = "aktif";

    users[1].norek = "1234567891";
    users[1].pin = "123456";
    users[1].saldo = 1000000;
    users[1].role = "user";
    users[1].status = "aktif";

    users[2].norek = "1234567892";
    users[2].pin = "123456";
    users[2].saldo = 1000000;
    users[2].role = "user";
    users[2].status = "aktif";

    users[3].norek = "1234567893";
    users[3].pin = "123456";
    users[3].saldo = 1000000;
    users[3].role = "user";
    users[3].status = "terblokir";
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
//1.otomatisasi norek register
void registerUser() {
    string norek, pin, status;

    cout << "\n== REGISTER ==\n";
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
            users[userCount].status = "aktif"; // Default status 'aktif'
            users[userCount].loginAttempts = 0; // Default login attempts 0
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
            if (users[i].status == "terblokir") {
                cout << "\nNorek diblokir. Hubungi admin untuk bantuan.\n";
                return false;
                break;
            }
            role = users[i].role;
            currentUser = users[i];
            return true;
        }
    }
    return false;
}

//dashboard admin
void detailUser() {
    string norek;
    cout << "Masukkan nomor rekening pengguna yang dicari: ";
    cin >> norek;

    // Mencari pengguna berdasarkan nomor rekening
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            cout << "\n=== Detail Pengguna ===" << endl;
            cout << "Nomor Rekening: " << users[i].norek << endl;
            cout << "Saldo: " << users[i].saldo << " IDR" << endl;
            cout << "Role: " << users[i].role << endl;
            cout << "Status: " << users[i].status << endl;
            return;
        }
    }

    // Menampilkan pesan jika pengguna tidak ditemukan
    cout << "\nPengguna dengan nomor rekening " << norek << " tidak ditemukan." << endl;
}
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
            users[userCount].status = "aktif";
            users[userCount].loginAttempts = 0;
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
            string newNorek, newPin, newRole, newStatus;

            cout << "Masukkan nomor rekening baru: ";
            cin >> newNorek;

            // Validasi nomor rekening baru
            if (isValidNumericNorek(newNorek) && isUniqueNorek(newNorek)) {
                cout << "Masukkan pin baru: ";
                hidePin(newPin);
                cout << "Masukkan role baru (admin/user): ";
                cin >> newRole;
                cout << "Masukkan Status (aktif/terblokir): ";
                cin >> newStatus;

                // Mengganti informasi pengguna dengan informasi baru
                users[i].norek = newNorek;
                users[i].pin = newPin;
                users[i].role = newRole;
                users[i].status = newStatus;

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
        cout << "1. Detail User" << endl;
        cout << "2. Daftarkan Nasabah/Admin" << endl;
        cout << "3. Edit Nasabah" << endl;
        cout << "4. Hapus Akun Nasabah" << endl;
        cout << "5. Kembali ke menu" << endl;
        cout << "Pilih opsi : ";
        cin >> choice;

        switch (choice) {
        case 1:
            detailUser();
            break;
        case 2:
            registerUserByAdmin();
            break;
        case 3:
             editUserByNorek();
            break;
        case 4:
             deleteUserByNorek();
            break;
        case 5:
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
    cout << "\nSaldo Anda: IDR. " << currentUser.saldo << endl;
}
void addMoney(User& currentUser) {
    cout << "Masukkan jumlah uang yang ingin disetor: IDR. ";
    int setor;
    while (!(cin >> setor) || setor <= 0) {
		cout << "Jumlah uang yang dimasukkan tidak valid. Silakan coba lagi: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
    currentUser.saldo += setor;
	cout << "\nSetoran berhasil. Saldo Anda sekarang: IDR. " << currentUser.saldo << endl;
    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == currentUser.norek) {
			users[i].saldo = currentUser.saldo;
			break;
		}
	}
	return;
};
void withdrawMoney(User& currentUser) {
    int tarik;

    cout << "Masukkan jumlah uang yang ingin ditarik: ";
    cin >> tarik;

    if (tarik > 0 && tarik <= currentUser.saldo) {
        currentUser.saldo -= tarik;
        cout << "\nPenarikan berhasil. Saldo Anda sekarang: IDR. " << currentUser.saldo << endl;
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
        cout << "\nNomor rekening tidak valid." << endl;
        return;
    }

    cout << "Masukkan jumlah uang yang ingin ditransfer: IDR. ";
    while (!(cin >> transfer) || transfer <= 0) {
        cout << "\nJumlah uang yang dimasukkan tidak valid. Silakan coba lagi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (transfer > user.saldo) {
        cout << "\nSaldo tidak mencukupi untuk melakukan transfer sebesar itu." << endl;
        return;
    }

    for (int i = 0; i < userCount; ++i) {
        if (users[i].norek == norek) {
            users[i].saldo += transfer;
            user.saldo -= transfer;
            cout << "\nTransfer berhasil ke norek " << norek << endl;
            cout << " Saldo Anda sekarang : IDR. " << user.saldo << endl; 
            return;
        }
    }

    cout << "\nNomor rekening tujuan tidak ditemukan." << endl;
}
void userBlock(User& user) {
    string pin, confirmPin;
    cout << "Masukkan pin norek untuk memblokir norek\n";
    cout << "Masukkan pin: ";
    hidePin(pin);
    cout << "KONFIRMASI PEMBLOKIRAN, Massukkan pin: ";
    hidePin(confirmPin);

    if (pin == user.pin && confirmPin == user.pin) {
		user.status = "terblokir";
		cout << "Norek berhasil diblokir." << endl;
	}
    else {
		cout << "Pin dan Konfirmasi tidak cocok. Norek tidak diblokir." << endl;
	}
}
void changePin(User& currentUser) {
	string newPin,confirmPin;
	cout << "Masukkan pin baru: ";
	hidePin(newPin);
    cout << "Konfirmasi pin baru: ";
    hidePin(confirmPin);

    if (newPin == confirmPin) {
        currentUser.pin = newPin;
        cout << "Pin berhasil diubah." << endl;
    }
    else {
		cout << "Pin dan Konfirmasi tidak cocok. Pin tidak diubah." << endl;
	}
	
}
void userDashboard(User& currentUser) {
    currentUser.loginAttempts = 0;
    int choice;

    while (true) {
        cout << "\n=== DASHBOARD USER ===\n";
        cout << "Menu Transaksi: \n";
        cout << "1. Tampilkan saldo\n";
        cout << "2. Setor tunai\n";
        cout << "3. Tarik tunai\n";
        cout << "4. Transfer\n";
        cout << "5. Ganti pin\n";
        cout << "6. Blokir akun\n";
        cout << "7. Logout\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showBalance(currentUser);
            break;
        case 2:
            addMoney(currentUser);
            break;
        case 3:
            withdrawMoney(currentUser);
            break;
        case 4:
            transferMoney(currentUser);
            break;
        case 5:
            changePin(currentUser);
            break;
        case 6:
            userBlock(currentUser);
        case 7:
            cout << "\nKeluar dari Dashboard User." << endl;
            for (int i = 0; i < userCount; ++i) {
                if (users[i].norek == currentUser.norek) {
                    users[i].saldo = currentUser.saldo;
                    users[i].pin = currentUser.pin;
                    users[i].status = currentUser.status;
                    break;
                }
            }
            return;
        default:
            cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
        }
    }
};


int main() {
    string norek, pin, role;
    int choice;


    blueprintUserAndAdmin();
    User currentUser;
    const int MAX_LOGIN_ATTEMPTS = 3;


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
            do {
                cout << "\n=== LOGIN ===" << endl;
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
                    currentUser.loginAttempts++;
                    if (currentUser.loginAttempts >= MAX_LOGIN_ATTEMPTS) {                  
                        cout << "\nAkun Anda telah terblokir setelah 3x upaya login gagal.\n";
                        for (int i = 0; i < userCount; ++i) {
                            if (users[i].norek == norek) {
                                users[i].status = "terblokir";
                                break;
                            }
                        }
                    }
                    else {
                        int remainingAttempts = MAX_LOGIN_ATTEMPTS - currentUser.loginAttempts;
                        cout << "\nNorek atau Password tidak valid. Silahkan coba lagi. Sisa percobaan: " << remainingAttempts << endl;
                    }
                }
            } while (currentUser.status != "terblokir");
                
            break;
        case 3:
            cout << "\nKeluar dari program. Selamat Tinggal!" << endl;
            break;
        default:
            cout << "\nKesalahan pemilihan. Coba lagi." << endl;
        }
    } while (choice != 3);

    return 0;
}