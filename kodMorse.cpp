#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

int takt = 300;                         // w ms
int wysokosc_dzwieku = 700;             // w hz

void pikanie(vector<int> tekst, int takt = 300, int wysokosc_dzwieku = 700, bool czy_pisac = true) //vector int juz zakodowany w morsie
{
	int dlugosc_tekstu = tekst.size();

	if (czy_pisac) {
		for (int i = 0; i < dlugosc_tekstu; i++) {

			switch (tekst[i]) {

			case 2:                                   // palza
				Beep(wysokosc_dzwieku, 3 * takt);
				cout << "-";
				break;
			case 1:                                   // kropka
				Beep(wysokosc_dzwieku, takt);
				cout << "*";
				break;
			case 0:                                   // przerwa
				Sleep(takt);
				cout << " ";
				break;
			default:
				cout << endl << "error";
				exit(0);
			}
		}
	}
	else {
		for (int i = 0; i < dlugosc_tekstu; i++) {

			switch (tekst[i]) {

			case 2:                                   // palza
				Beep(wysokosc_dzwieku, 3 * takt);
				break;
			case 1:                                   // kropka
				Beep(wysokosc_dzwieku, takt);
				break;
			case 0:                                   // przerwa
				Sleep(takt);
				break;
			default:
				cout << endl << "error";
				exit(0);
			}
		}
	}
}

vector<int> tlumacz(string tekst) {

	transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);

	string literki[26];

	literki[0] = "12";									//a
	literki[1] = "2111";								//b
	literki[2] = "2121";								//c
	literki[3] = "211";									//d
	literki[4] = "1";									//e
	literki[5] = "1121";								//f
	literki[6] = "221";									//g
	literki[7] = "1111";								//h
	literki[8] = "11";									//i
	literki[9] = "1222";								//j
	literki[10] = "212";								//k
	literki[11] = "1211";								//l
	literki[12] = "22";									//m
	literki[13] = "21";									//n
	literki[14] = "222";								//o
	literki[15] = "1221";								//p
	literki[16] = "2212";								//q
	literki[17] = "121";								//r
	literki[18] = "111";								//s
	literki[19] = "2";									//t
	literki[20] = "112";								//u
	literki[21] = "1112";								//v
	literki[22] = "122";								//w
	literki[23] = "2112";								//x
	literki[24] = "2122";								//y
	literki[25] = "2211";								//z

	int dlugosc_tekstu = tekst.size();

	vector<int> przetlumaczone;
	string kod = " ";
	char litera = ' ';
	int dlugosc = 0;

	for (int i = 0; i < dlugosc_tekstu; i++)
	{
		litera = tekst[i];
		if ((litera > 96) && (litera < 123)) {                //a=0 itd.

			kod = literki[litera - 97];
			dlugosc = kod.size();

			for (int i = 0; i < dlugosc; i++)
			{
				przetlumaczone.push_back(kod[i] - 48);
				przetlumaczone.push_back(0);
			}

		}
		else if (litera == 32) {}                 // spacja
		else {
			cout << "Blad! Musisz podac litery, tekst zostal przetlumaczony do tego miejsca";
			return przetlumaczone;
		}
		przetlumaczone.push_back(0);
		przetlumaczone.push_back(0);

	}

	return przetlumaczone;

}

void sprawdz(string tekst) {

	string odpowiedz = " ";

	int dlugosc_tekstu = tekst.length();
	char litera = tekst[dlugosc_tekstu - 1];                                     //usuwanie spacji z konca
	if (litera == 32) { tekst.erase(dlugosc_tekstu - 1); }

	pikanie(tlumacz(tekst), takt, wysokosc_dzwieku, false);
	cout << endl << "Co powiedzialem?" << endl;
	cin.ignore();
	getline(cin, odpowiedz);
	transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);
	transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);

	if (odpowiedz == tekst) cout << "Udalo Ci sie!";
	else                    cout << "Niestety zle, prawidlowa odpowiedz to " << tekst;
}

void sprawdz_losowe_litery() {

	srand(time(NULL));

	string odpowiedz = " ";
	string litera = " ";
	litera[0] = (rand() % 26) + 97;
	pikanie(tlumacz(litera), takt, wysokosc_dzwieku, false);
	cout << "Co powiedzialem?" << endl;
	cin.ignore();
	getline(cin, odpowiedz);
	transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);

	if (odpowiedz == litera) cout << "Udalo Ci sie!";
	else                     cout << "Niestety zle, prawidlowa odpowiedz to " << litera;
}

void sprawdz_losowe_slowo_z_pliku(string sciezka = "") {

	fstream plik;
	int dlugosc_pliku = 0;

	plik.open(sciezka, ios::in);
	if (plik.good()) {
		srand(time(NULL));
		string linia = " ";

		while (std::getline(plik, linia))
			++dlugosc_pliku;

		int losowanko = rand() % dlugosc_pliku + 1;
		
		plik.clear(); 
		plik.seekg(0);

		for (int i = 0; i < losowanko; i++)
		{
			getline(plik, linia);
		}

		sprawdz(linia);
	}

	plik.close();
}

int main()
{
	map<char, string > kod_Morse;

	char wybor;
	string tekst;

	do
	{
		wybor = '0';
		system("cls");

		cout << "MENU GLOWNE:" << endl;
		cout << "------------------------------------------" << endl;
		cout << "1. Tlumaczenie tekstu na kod morsa " << endl;
		cout << "2. Sprawdzanie znajomosci losowych liter " << endl;
		cout << "3. Sprawdzenie znajomosci losowych slow " << endl;
		cout << "4. Sprawdzanie znajomosci losowych slow z podanego pliku " << endl;
		cout << "5. Wyjscie z programu " << endl;
		cout << "------------------------------------------" << endl;
		cout << "Wybor: ";
		cin >> wybor;

		switch (wybor)
		{
		case '1':
			
			system("cls");

			cout << "Podaj tekst do przetlumaczenia: ";
			cin >> tekst;
			cout << endl;
			pikanie(tlumacz(tekst));
			cout << endl << "Nacisnij dowolny klawisz, zeby kontynuwac";
			getchar(); getchar();
			break;

		case '2':

			system("cls");

			sprawdz_losowe_litery();
			getchar();
			break;

		case '3':
			
			system("cls");

			sprawdz_losowe_slowo_z_pliku("Baza_slow.txt");
			getchar();
			break;

		case '4':
			
			system("cls");

			cout << "Podaj sciezke do pliku .txt (kazde slowo ktore ma byc sprawdzane powino byc w nowej lini) " << endl;
			cin.ignore();
			string sciezka = "";
			getline(cin, sciezka);

			system("cls");
			
			sprawdz_losowe_slowo_z_pliku(sciezka);
			getchar();
			break;
		}

	} while (wybor != '5');

	return 0;
}


