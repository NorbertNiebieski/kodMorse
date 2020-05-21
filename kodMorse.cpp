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

	literki[0] = "12";                               //a
	literki[1] = "2111";                             //b
	literki[2] = "2121";                             //c
	literki[3] = "211";                              //d
	literki[4] = "1";                                //e
	literki[5] = "1121";                             //f
	literki[6] = "221";                              //g
	literki[7] = "1111";                             //h
	literki[8] = "11";                               //i
	literki[9] = "1222";                             //j
	literki[10] = "212";                              //k
	literki[11] = "1211";                             //l
	literki[12] = "22";                               //m
	literki[13] = "21";                               //n
	literki[14] = "222";                              //o
	literki[15] = "1221";                             //p
	literki[16] = "2212";                             //q
	literki[17] = "121";                              //r
	literki[18] = "111";                              //s
	literki[19] = "2";                                //t
	literki[20] = "112";                              //u
	literki[21] = "1112";                             //v
	literki[22] = "122";                              //w
	literki[23] = "2112";                             //x
	literki[24] = "2122";                             //y
	literki[25] = "2211";                             //z


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

	string odpowiedz = "";

	int dlugosc_tekstu = tekst.length();
	char litera = tekst[dlugosc_tekstu - 1];                                     //usuwanie spacji z konca
	if (litera == 32) { tekst.erase(dlugosc_tekstu - 1); }

	pikanie(tlumacz(tekst), takt, wysokosc_dzwieku, false);
	cout << endl << "Co powiedzialem?" << endl;
	getline(cin, odpowiedz);
	transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);
	transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);

	if (odpowiedz == tekst)   cout << "Udalo Ci sie!";
	else                    cout << "Niestety zle, prawidlowa odpowiedz to " << tekst;
}

void sprawdz_losowe_litery() {

	srand(time(NULL));

	string odpowiedz = "";
	string litera = " ";
	litera[0] = (rand() % 26) + 97;
	pikanie(tlumacz(litera), takt, wysokosc_dzwieku, false);
	cout << "Co powiedzialem?" << endl;
	getline(cin, odpowiedz);
	transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);

	if (odpowiedz == litera)   cout << "Udalo Ci sie!";
	else                     cout << "Niestety zle, prawidlowa odpowiedz to " << litera;
}

void sprawdz_losowe_slowo_z_pliku(string sciezka = "") {

	fstream plik;
	int dlugosc_pliku = 0;

	plik.open("baza_slow/test.txt", ios::in);
	if (plik.good()) {
		srand(time(NULL));
		string linia = " ";
		while (true)
		{
			if (getline(plik, linia))
			{
				dlugosc_pliku++;
			}
			else
			{
				break;
			}

		}
		int losowanko = rand() % dlugosc_pliku + 1;
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



	//kod_Morse['a']="21";

	while (true) {
		//sprawdz_losowe_slowo_z_pliku("baza_slow/test.txt");
		sprawdz_losowe_litery();
		getchar();
		getchar();
	}

	//sprawdz("hehe");



	return 0;
}


