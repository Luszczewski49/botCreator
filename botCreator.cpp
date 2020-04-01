#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;
VOID WINAPI Sleep(DWORD dwMilliseconds);

int kod = 0;
bool klik = false;
int klikniecia = 0;
int tabX[1000];
int tabY[1000];
int czasy[1000];
long licznikMilisekund = 0;
bool zliczanie = false;
char wybor;

void zapisz(string nazwaPliku)
{
    string nazwa = nazwaPliku + ".txt";
    fstream plik(nazwa.c_str(), ios::out);
    if( plik.good() )
    {
        plik << klikniecia << endl;
        for(int i = 0; i < klikniecia; i++)
        {
            plik << tabX[i] << endl;
            plik << tabY[i] << endl;
            plik << czasy[i+1] << endl;
        }

        plik.close();
        cout << "Udany zapis pliku!" << endl;
    }
    else
    {
        cout << "Blad zapisu" << endl;
    }
}

void odtworzBota()
{
    HWND h;
    TCHAR szOldTitle[MAX_PATH];
    GetConsoleTitle(szOldTitle, MAX_PATH);
    h = FindWindow(NULL,szOldTitle);
    ShowWindow(h,SW_MINIMIZE);

    for(int i = 0; i < klikniecia; i++)
    {
        cout << "Praca w toku ...";
        SetCursorPos(tabX[i], tabY[i]);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);
        Sleep(czasy[i+2]);
        system("cls");
    }
    cout << "Koniec pracy" << endl;
}


void wczytajPlik(string nazwaPliku)
{
    int licznikPetli = 0;
    string nazwa = nazwaPliku + ".txt";

    bool sprawdzenieStanu = false;

    ifstream plik;
    plik.open( nazwa.c_str() );
    if( !plik.good() )
    {
        cout << "Nie udalo sie otworzyc pliku" << endl;
    }
    else
    {
        while( true )
        {
            if(sprawdzenieStanu == false)
                plik >> klikniecia;
cout << "Klikniecia: " << klikniecia << endl;
            plik >> tabX[licznikPetli] >> tabY[licznikPetli] >> czasy[licznikPetli+2];
            sprawdzenieStanu = true;
            if( plik.good() )
             {
                 cout << "X: " << tabX[licznikPetli] << endl;
                 cout << "Y: " << tabY[licznikPetli] << endl;
                 cout << "Czas: " << czasy[licznikPetli+2] << endl;
                 cout << endl;
                 licznikPetli++;
             }
            else
            {
            break;
            }
    }
        cout << "Wczytywanie danych zakonczone" << endl;
        cout << "Uruchamianie bota (ekran zostanie zminimalizowany) ..." << endl;
        Sleep(3000);
        system("cls");
        odtworzBota();
    }
}

void stworzBota()
{
    system("cls");
    cout << endl;
    cout << "[Tab] Rozpocznij nagrywanie" << endl;
    cout << "[Esc] Zakoncz nagrywanie" << endl;
    cout << endl;
    cout << "Przed rozpoczeciem zminimalizuj to okno!" << endl;

    while(!(GetAsyncKeyState(9)))
    {

    }

while(kod != 27)
{
    cout << "Nagrywanie w toku ..." << endl;
    Sleep(20);
    system("cls");

}

cout << "Koniec nagrywania, odtworzyc? [t/n]: ";
cin >> wybor;

cin.clear();
cin.sync();

if(wybor == 't')
{
    cout << "Okno zostanie zminimalizowane ..." << endl;
    Sleep(1000);
    system("cls");
    odtworzBota();
}

wybor = '0';
cout << "Zapisac? [t/n]: ";
cin >> wybor;

if(wybor == 't')
{
    string nazwa;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwa;
    cin.clear();
    cin.sync();
    zapisz(nazwa);
}
system("cls");
}


void czas(void * Args)
{
    while(true)
    {
        while(zliczanie)
        {
            licznikMilisekund = licznikMilisekund + 10;
            Sleep(10);
        }
        if(licznikMilisekund != 0)
        {
            czasy[klikniecia] = licznikMilisekund;
            licznikMilisekund = 0;
        }

    }


}

void watek(void * Args)
{
    do
    {
       // kod = getch();
       // if(kbhit())
           // kod = getch();

    }while(!(GetAsyncKeyState(27)));

    kod = 27;
}

void oczekiwanie(void * Args)
{
    while(true)
    {
        while( !(HIBYTE( GetKeyState( VK_LBUTTON ))))
    {

    }
    zliczanie = false;

    klik = true;


    POINT pozycja;
                GetCursorPos(&pozycja);
                tabX[klikniecia] = pozycja.x;
                tabY[klikniecia] = pozycja.y;

    klikniecia++;


    while(HIBYTE( GetKeyState( VK_LBUTTON )))
    {

    }
    zliczanie = true;

    klik = false;
    }


}

int main()
{
    string nazwa;

    _beginthread(watek, 0 , NULL);
    _beginthread(oczekiwanie, 0 , NULL);
    _beginthread(czas, 0, NULL);

    cout << "BotCreator 0.9 Beta, by LuszczewskiTeam" << endl;
    cout << endl;
    while(true)
    {
        cout << "[1] Stworz nowego bota" << endl;
    cout << "[2] Odtworz zapisanego bota" << endl;
    cout << "[3] Zakoncz" << endl;
    cin >> wybor;
    cin.clear();
    cin.sync();

    if(wybor == '1')
        stworzBota();

    if(wybor == '2')
    {
        cout << "Podaj nazwe pliku: ";
        cin >> nazwa;
        cin.clear();
        cin.sync();
        wczytajPlik(nazwa);
    }

    if(wybor == '3')
        break;

    }


    return 0;
}




