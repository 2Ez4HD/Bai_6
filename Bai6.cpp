#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int SIZE = 101;
struct Node {
    string eng;
    string vie;
    Node* next;
    Node(string e, string v) {
        eng = e;
        vie = v;
        next = NULL;
    }
};
class HashTable {
private:
    Node* table[SIZE];
    int hashFunction(string s) {
        unsigned long long hash = 0;
        for (int i = 0; i < s.length(); i++) {
            hash = hash * 31 + s[i];
        }
        return hash % SIZE;
    }
public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
    }
    void insertWord(string eng, string vie) {
        int index = hashFunction(eng);
        Node* p = table[index];
        while (p != NULL) {
            if (p->eng == eng) {
                p->vie = vie;
                return;
            }
            p = p->next;
        }
        Node* newNode = new Node(eng, vie);
        newNode->next = table[index];
        table[index] = newNode;
    }
    string searchWord(string eng) {
        int index = hashFunction(eng);
        Node* p = table[index];
        while (p != NULL) {
            if (p->eng == eng)
                return p->vie;
            p = p->next;
        }
        return "";
    }
    bool editWord(string eng, string newVie) {
        int index = hashFunction(eng);
        Node* p = table[index];
        while (p != NULL) {
            if (p->eng == eng) {
                p->vie = newVie;
                return true;
            }
            p = p->next;
        }
        return false;
    }
    bool deleteWord(string eng) {
        int index = hashFunction(eng);
        Node* p = table[index];
        Node* prev = NULL;
        while (p != NULL) {
            if (p->eng == eng) {
                if (prev == NULL)
                    table[index] = p->next;
                else
                    prev->next = p->next;
                delete p;
                return true;
            }
            prev = p;
            p = p->next;
        }
        return false;
    }
    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Khong mo duoc file!\n";
            return;
        }
        string eng, vie;
        while (file >> eng) {
            getline(file, vie);
            if (vie.length() > 0 && vie[0] == ' ')
                vie.erase(0, 1);
            insertWord(eng, vie);
        }
        file.close();
        cout << "Da nap tu dien tu file!\n";
    }
    void saveToFile(string filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Khong tao duoc file!\n";
            return;
        }
        for (int i = 0; i < SIZE; i++) {
            Node* p = table[i];

            while (p != NULL) {
                file << p->eng << " " << p->vie << endl;
                p = p->next;
            }
        }
        file.close();
        cout << "Da luu tu dien vao file!\n";
    }
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* p = table[i];
            while (p != NULL) {
                Node* temp = p;
                p = p->next;
                delete temp;
            }
        }
    }
};
void menu() {
    cout << "\n========== TU DIEN ANH - VIET ==========\n";
    cout << "1. Nap tu dien tu file\n";
    cout << "2. Tra tu\n";
    cout << "3. Sua tu\n";
    cout << "4. Them tu moi\n";
    cout << "5. Xoa tu\n";
    cout << "6. Luu tu dien vao file\n";
    cout << "0. Thoat\n";
    cout << "=========================================\n";
    cout << "Chon: ";
}
int main() {
    HashTable dictionary;
    int choice;
    string eng, vie;
    do {
        menu();
        cin >> choice;
        switch (choice) {
        case 1:
            dictionary.loadFromFile("tudien.txt");
            break;
        case 2:
            cout << "Nhap tu tieng Anh: ";
            cin >> eng;
            vie = dictionary.searchWord(eng);
            if (vie != "")
                cout << "Nghia tieng Viet: " << vie << endl;
            else
                cout << "Khong tim thay tu nay!\n";
            break;
        case 3:
            cout << "Nhap tu can sua: ";
            cin >> eng;
            cout << "Nhap nghia moi: ";
            cin.ignore();
            getline(cin, vie);
            if (dictionary.editWord(eng, vie))
                cout << "Sua thanh cong!\n";
            else
                cout << "Khong tim thay tu nay!\n";
            break;
        case 4:
            cout << "Nhap tu tieng Anh: ";
            cin >> eng;
            cout << "Nhap nghia tieng Viet: ";
            cin.ignore();
            getline(cin, vie);
            dictionary.insertWord(eng, vie);
            cout << "Them tu thanh cong!\n";
            break;
        case 5:
            cout << "Nhap tu can xoa: ";
            cin >> eng;
            if (dictionary.deleteWord(eng))
                cout << "Xoa thanh cong!\n";
            else
                cout << "Khong tim thay tu nay!\n";
            break;
        case 6:
            dictionary.saveToFile("tudien.txt");
            break;
        case 0:
            cout << "Ket thuc chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
    return 0;
}