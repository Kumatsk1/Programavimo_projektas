#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Struktura kambariui
struct Kambarys {
    int id;
    int numeris;
    string tipas;
    double kaina;
    string statusas;
    int kliento_id; // 0 - jei kambarys laisvas
};

// Struktura klientui
struct Klientas {
    int id;
    string vardas;
    string pavarde;
    int kambario_id; // kuriame kambaryje gyvena
};

// Masyvai
Kambarys kambariai[100];
int kiekis = 0;

Klientas klientai[100];
int klientu_kiekis = 0;

// Failo operacijos - kambariai

void nuskaitytiIsFailo() {
    ifstream failas("kambariai.txt");
    kiekis = 0;
    while (failas >> kambariai[kiekis].id
                  >> kambariai[kiekis].numeris
                  >> kambariai[kiekis].tipas
                  >> kambariai[kiekis].kaina
                  >> kambariai[kiekis].statusas
                  >> kambariai[kiekis].kliento_id) {
        kiekis++;
    }
    failas.close();
}

void irasytiIFaila() {
    ofstream failas("kambariai.txt");
    for (int i = 0; i < kiekis; i++) {
        failas << kambariai[i].id       << " "
               << kambariai[i].numeris  << " "
               << kambariai[i].tipas    << " "
               << kambariai[i].kaina    << " "
               << kambariai[i].statusas << " "
               << kambariai[i].kliento_id << "\n";
    }
    failas.close();
}

// Failo operacijos - klientai
void nuskaitytiKlientusIsFailo() {
    ifstream failas("klientai.txt");
    klientu_kiekis = 0;
    while (failas >> klientai[klientu_kiekis].id
                  >> klientai[klientu_kiekis].vardas
                  >> klientai[klientu_kiekis].pavarde
                  >> klientai[klientu_kiekis].kambario_id) {
        klientu_kiekis++;
    }
    failas.close();
}

void irasytiKlientusIFaila() {
    ofstream failas("klientai.txt");
    for (int i = 0; i < klientu_kiekis; i++) {
        failas << klientai[i].id         << " "
               << klientai[i].vardas     << " "
               << klientai[i].pavarde    << " "
               << klientai[i].kambario_id << "\n";
    }
    failas.close();
}

// Rodyti visus kambarius

void rodytiVisusKambarius() {
    if (kiekis == 0) { cout << "Sarasas tuscias.\n"; return; }

    cout << left << setw(5)  << "ID"
                 << setw(10) << "Numeris"
                 << setw(12) << "Tipas"
                 << setw(10) << "Kaina"
                 << setw(12) << "Statusas"
                 << setw(12) << "Kliento ID" << "\n";
    cout << string(59, '-') << "\n";

    for (int i = 0; i < kiekis; i++) {
        string kliento = (kambariai[i].kliento_id == 0) ? "-" : to_string(kambariai[i].kliento_id);
        cout << left << setw(5)  << kambariai[i].id
                     << setw(10) << kambariai[i].numeris
                     << setw(12) << kambariai[i].tipas
                     << setw(10) << kambariai[i].kaina
                     << setw(12) << kambariai[i].statusas
                     << setw(12) << kliento << "\n";
    }
}

// Rodyti tik laisvus kambarius

void rodytiLaisvaKambarius() {
    cout << left << setw(5)  << "ID"
                 << setw(10) << "Numeris"
                 << setw(12) << "Tipas"
                 << setw(10) << "Kaina"
                 << setw(10) << "Statusas" << "\n";
    cout << string(47, '-') << "\n";

    bool rasta = false;
    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].statusas == "laisvas") {
            cout << left << setw(5)  << kambariai[i].id
                         << setw(10) << kambariai[i].numeris
                         << setw(12) << kambariai[i].tipas
                         << setw(10) << kambariai[i].kaina
                         << setw(10) << kambariai[i].statusas << "\n";
            rasta = true;
        }
    }
    if (!rasta) cout << "Nera laisvų kambariu.\n";
}

// Klientas atvyko - rezervacija (laisvas -> uzimtas)

void rezervuotiKambari() {
    rodytiLaisvaKambarius();

    int id;
    cout << "\nIveskite kambario ID, kuri norite rezervuoti: ";
    cin >> id;

    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].id == id) {
            if (kambariai[i].statusas == "uzimtas") {
                cout << "Sis kambarys jau uzimtas!\n";
                return;
            }

            // Ivesti kliento duomenis
            Klientas k;
            k.id = klientu_kiekis + 1; // automatinis ID
            cout << "\nIveskite kliento varda: ";
            cin >> k.vardas;
            cout << "Iveskite kliento pavarde: ";
            cin >> k.pavarde;
            k.kambario_id = id;

            klientai[klientu_kiekis] = k;
            klientu_kiekis++;

            // Atnaujinti kambario statusa
            kambariai[i].statusas  = "uzimtas";
            kambariai[i].kliento_id = k.id;

            cout << "\nKambarys " << kambariai[i].numeris << " rezervuotas!\n";
            cout << "Kliento ID: " << k.id << "\n";
            return;
        }
    }
    cout << "Kambarys su tokiu ID nerastas.\n";
}

// Klientas isvyko - atlaisvinimas (uzimtas -> laisvas)

void atlaisvintiKambari() {
    cout << left << setw(5)  << "ID"
                 << setw(10) << "Numeris"
                 << setw(12) << "Tipas"
                 << setw(10) << "Kaina"
                 << setw(12) << "Statusas"
                 << setw(12) << "Kliento ID" << "\n";
    cout << string(59, '-') << "\n";

    bool rasta = false;
    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].statusas == "uzimtas") {
            string kliento = to_string(kambariai[i].kliento_id);
            cout << left << setw(5)  << kambariai[i].id
                         << setw(10) << kambariai[i].numeris
                         << setw(12) << kambariai[i].tipas
                         << setw(10) << kambariai[i].kaina
                         << setw(12) << kambariai[i].statusas
                         << setw(12) << kliento << "\n";
            rasta = true;
        }
    }
    if (!rasta) { cout << "Nera uzimtu kambariu.\n"; return; }

    int id;
    cout << "\nIveskite kambario ID, kuri norite atlaisvinti: ";
    cin >> id;

    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].id == id) {
            if (kambariai[i].statusas == "laisvas") {
                cout << "Sis kambarys jau laisvas!\n";
                return;
            }

            // Istrinti klienta is masyvo
            int kliento_id = kambariai[i].kliento_id;
            for (int j = 0; j < klientu_kiekis; j++) {
                if (klientai[j].id == kliento_id) {
                    for (int k = j; k < klientu_kiekis - 1; k++) {
                        klientai[k] = klientai[k + 1];
                    }
                    klientu_kiekis--;
                    break;
                }
            }

            kambariai[i].statusas   = "laisvas";
            kambariai[i].kliento_id = 0;
            cout << "Kambarys " << kambariai[i].numeris << " atlaisvintas!\n";
            return;
        }
    }
    cout << "Kambarys su tokiu ID nerastas.\n";
}

// Perziureti kliento duomenis pagal kliento ID

void perziuretiKlienta() {
    if (klientu_kiekis == 0) { cout << "Nera uzregistruotu klientu.\n"; return; }

    // Rodyti klientu sarasa
    cout << left << setw(12) << "Kliento ID"
                 << setw(12) << "Kambario ID" << "\n";
    cout << string(24, '-') << "\n";
    for (int i = 0; i < klientu_kiekis; i++) {
        cout << left << setw(12) << klientai[i].id
                     << setw(12) << klientai[i].kambario_id << "\n";
    }

    int id;
    cout << "\nIveskite kliento ID: ";
    cin >> id;

    for (int i = 0; i < klientu_kiekis; i++) {
        if (klientai[i].id == id) {
            cout << "\n--- Kliento duomenys ---\n";
            cout << "ID:       " << klientai[i].id      << "\n";
            cout << "Vardas:   " << klientai[i].vardas   << "\n";
            cout << "Pavarde:  " << klientai[i].pavarde  << "\n";

            // Rasti kambari pagal kambario_id
            for (int j = 0; j < kiekis; j++) {
                if (kambariai[j].id == klientai[i].kambario_id) {
                    cout << "Kambarys: " << kambariai[j].numeris << " ("
                         << kambariai[j].tipas << ", "
                         << kambariai[j].kaina << " EUR)\n";
                }
            }
            return;
        }
    }
    cout << "Klientas su tokiu ID nerastas.\n";
}

// Prideti nauja kambari

void pridetiKambari() {
    if (kiekis >= 100) { cout << "Masyvas pilnas!\n"; return; }

    kambariai[kiekis].id         = kiekis + 1;
    kambariai[kiekis].kliento_id = 0;

    cout << "\nIveskite kambario numeri: ";
    cin >> kambariai[kiekis].numeris;

    cout << "Iveskite tipa (standart/lux/deluxe): ";
    cin >> kambariai[kiekis].tipas;

    if      (kambariai[kiekis].tipas == "standart") kambariai[kiekis].kaina = 50.00;
    else if (kambariai[kiekis].tipas == "lux")      kambariai[kiekis].kaina = 90.00;
    else if (kambariai[kiekis].tipas == "deluxe")   kambariai[kiekis].kaina = 150.00;
    else {
        cout << "Nezinomas tipas, kaina nustatyta 0.\n";
        kambariai[kiekis].kaina = 0.00;
    }
    cout << "Numatytoji kaina: " << kambariai[kiekis].kaina << " EUR\n";
    cout << "Palikti sia kaina? (1 - taip / 2 - ivesti sava): ";
    int kainosPasirinkimas;
    cin >> kainosPasirinkimas;
    if (kainosPasirinkimas == 2) {
        cout << "Iveskite savo kaina: ";
        cin >> kambariai[kiekis].kaina;
    }

    kambariai[kiekis].statusas = "laisvas";
    kiekis++;
    cout << "\nKambaris pridetas!\n";
}

// Pasalinti kambari

void pasalintiKambari() {
    rodytiVisusKambarius();

    int id;
    cout << "\nIveskite ID kambario, kuri norite pasalinti: ";
    cin >> id;

    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].id == id) {
            for (int j = i; j < kiekis - 1; j++) {
                kambariai[j] = kambariai[j + 1];
            }
            kiekis--;
            cout << "Kambaris pasalintas!\n";
            return;
        }
    }
    cout << "Kambarys su tokiu ID nerastas.\n";
}

// Papildoma funkcija 1 - paieska pagal tipa

void ieskotiKambario() {
    string raktas;
    cout << "Iveskite tipa ieskoti (standart/lux/deluxe): ";
    cin >> raktas;

    bool rasta = false;
    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].tipas == raktas) {
            string kliento = (kambariai[i].kliento_id == 0) ? "-" : to_string(kambariai[i].kliento_id);
            cout << "ID:" << kambariai[i].id
                 << " Nr:" << kambariai[i].numeris
                 << " Tipas:" << kambariai[i].tipas
                 << " Kaina:" << kambariai[i].kaina
                 << " Statusas:" << kambariai[i].statusas
                 << " KlientoID:" << kliento << "\n";
            rasta = true;
        }
    }
    if (!rasta) cout << "Nerasta jokiu atitikmenų.\n";
}

// Papildoma funkcija 2 - rikiavimas pagal kaina

void rikiuotiPagalKaina() {
    for (int i = 0; i < kiekis; i++) {
        for (int j = 0; j < kiekis - 1; j++) {
            if (kambariai[j].kaina > kambariai[j + 1].kaina) {
                Kambarys laikinas  = kambariai[j];
                kambariai[j]       = kambariai[j + 1];
                kambariai[j + 1]   = laikinas;
            }
        }
    }
    cout << "Surikiuota pagal kaina!\n";
    rodytiVisusKambarius();
}

// Perkelti klienta i kita kambari

void perkeltiKlienta() {
    if (klientu_kiekis == 0) { cout << "Nera uzregistruotu klientu.\n"; return; }

    // Rodyti klientu sarasa
    cout << left << setw(12) << "Kliento ID"
                 << setw(12) << "Kambario ID" << "\n";
    cout << string(24, '-') << "\n";
    for (int i = 0; i < klientu_kiekis; i++) {
        cout << left << setw(12) << klientai[i].id
                     << setw(12) << klientai[i].kambario_id << "\n";
    }

    int kliento_id;
    cout << "\nIveskite kliento ID, kuri norite perkelti: ";
    cin >> kliento_id;

    // Rasti klienta
    int kliento_index = -1;
    for (int i = 0; i < klientu_kiekis; i++) {
        if (klientai[i].id == kliento_id) {
            kliento_index = i;
            break;
        }
    }
    if (kliento_index == -1) { cout << "Klientas su tokiu ID nerastas.\n"; return; }

    // Rodyti laisvus kambarius
    cout << "\nLaisvi kambariai:\n";
    rodytiLaisvaKambarius();

    int naujas_kambario_id;
    cout << "\nIveskite naujo kambario ID: ";
    cin >> naujas_kambario_id;

    // Patikrinti ar naujas kambarys laisvas
    int naujas_index = -1;
    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].id == naujas_kambario_id) {
            if (kambariai[i].statusas == "uzimtas") {
                cout << "Sis kambarys jau uzimtas!\n";
                return;
            }
            naujas_index = i;
            break;
        }
    }
    if (naujas_index == -1) { cout << "Kambarys su tokiu ID nerastas.\n"; return; }

    // Atlaisvinti sena kambari
    int senas_kambario_id = klientai[kliento_index].kambario_id;
    for (int i = 0; i < kiekis; i++) {
        if (kambariai[i].id == senas_kambario_id) {
            kambariai[i].statusas   = "laisvas";
            kambariai[i].kliento_id = 0;
            break;
        }
    }

    // Uzimti nauja kambari
    kambariai[naujas_index].statusas   = "uzimtas";
    kambariai[naujas_index].kliento_id = kliento_id;

    // Atnaujinti kliento kambario ID
    klientai[kliento_index].kambario_id = naujas_kambario_id;

    cout << "Klientas perkeltas i kambari " << kambariai[naujas_index].numeris << "!\n";
}

// Pagrindine programa

int main() {
    nuskaitytiIsFailo();
    nuskaitytiKlientusIsFailo();

    int pasirinkimas;

    do {
        cout << "\n===== VIESBUCIO KAMBARIU SISTEMA =====\n";
        cout << "1. Rodyti visus kambarius\n";
        cout << "2. Rodyti laisvus kambarius\n";
        cout << "3. Rezervuoti kambari (klientas atvyko)\n";
        cout << "4. Atlaisvinti kambari (klientas isvyko)\n";
        cout << "5. Perkelti klienta i kita kambari\n";
        cout << "6. Perziureti kliento duomenis\n";
        cout << "7. Prideti nauja kambari\n";
        cout << "8. Pasalinti kambari\n";
        cout << "9. Ieskoti pagal tipa\n";
        cout << "10. Rikiuoti pagal kaina\n";
        cout << "11. Issaugoti ir iseiti\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            pasirinkimas = -1;
            cout << "Klaida! Iveskite skaiciu is meniu.\n";
            continue;
        }

        if      (pasirinkimas == 1) rodytiVisusKambarius();
        else if (pasirinkimas == 2) rodytiLaisvaKambarius();
        else if (pasirinkimas == 3) rezervuotiKambari();
        else if (pasirinkimas == 4) atlaisvintiKambari();
        else if (pasirinkimas == 5) perkeltiKlienta();
        else if (pasirinkimas == 6) perziuretiKlienta();
        else if (pasirinkimas == 7) pridetiKambari();
        else if (pasirinkimas == 8) pasalintiKambari();
        else if (pasirinkimas == 9) ieskotiKambario();
        else if (pasirinkimas == 10) rikiuotiPagalKaina();
        else if (pasirinkimas == 11) {
            irasytiIFaila();
            irasytiKlientusIFaila();
            cout << "Duomenys issaugoti.\n";
        } else {
            cout << "Neteisingas pasirinkimas.\n";
        }

    } while (pasirinkimas != 11);

    return 0;
}
