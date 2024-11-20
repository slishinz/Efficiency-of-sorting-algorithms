#include <iostream> //do wprowadzania i wyprowadzania danych
#include <cstdlib> //biblioteka dla wykorzystania funkcji rand
#include <chrono> //biblioteka dla obliczenia czasu

using namespace std;


void babelkowe(int list[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n - i; j++)
            if (list[j - 1] > list[j]) // Jeśli poprzedni element jest większy od bieżącego
                swap(list[j - 1], list[j]); // Zamieniamy je miejscami
}

void wybor(int list[], int n) {
    int mn_index;
    for (int i = 0; i < n - 1; i++) {
        mn_index = i;
        for (int j = i + 1; j < n; j++)
            if (list[j] < list[mn_index])
                mn_index = j;
        swap(list[i], list[mn_index]);
    }
}

void wstawianie(int list[], int listLength)
{
    for(int i = 1; i < listLength; i++)
    {
        int j = i - 1;
        while(j >= 0 && list[j] > list[j + 1])
        {
            swap(list[j], list[j + 1]);//przesuwanie elementów
            j--;
        }
    }
}

void szybkie(int *list, int lewy, int prawy) {
    if (prawy <= lewy) return;

    int i = lewy - 1, j = prawy + 1,
            piv = list[(lewy + prawy) / 2];

    while (true) {
        while (piv > list[++i]);
        while (piv < list[--j]);

        if (i <= j)
            swap(list[i], list[j]);//funkcja swap zamienia wartosciami tab[i] z tab[j]
        else
            break;
    }
    if (j > lewy)
        szybkie(list, lewy, j);
    if (i < prawy)
        szybkie(list, i, prawy);
}

int *buf;

void scal(int list[], int lewy, int srodek, int prawy)
///scalenie posortowanych podtablic
{
    int i = lewy, j = srodek + 1;

    for(int i = lewy;i<=prawy; i++)
        buf[i] = list[i];

    //scalenie dwóch podtablic pomocniczych i zapisanie ich we właściwej tablicy
    for(int k=lewy;k<=prawy;k++)
        if(i<=srodek)
            if(j <= prawy)
                if(buf[j]<buf[i])
                    list[k] = buf[j++];
                else
                    list[k] = buf[i++];
            else
                list[k] = buf[i++];
        else
            list[k] = buf[j++];
}

void scalanie(int list[],int lewy, int prawy)
{
    if(prawy<=lewy) return;
    //gdy mamy jeden element, to jest on już posortowany
    int srodek = (prawy+lewy)/2;
    //znajdujemy srodek podtablicy
    scalanie(list, lewy, srodek);
    //dzielimy tablice na część lewą i część prawą
    scalanie(list, srodek+1, prawy);
    scal(list, lewy, srodek, prawy);
    //scalamy dwie już posortowane tablice
}

bool sprawdz(int list[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (list[i] > list[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL)); // Inicjalizacja generatora liczb losowych
    int n;
    cout << "Podaj ilosc liczb do posortowania: ";
    cin >> n;
    int *list = new int[n];
    buf = new int[n];

    // Wypełnienie tablicy losowymi liczbami
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000; // Zakres od 0 do 999
    }
    chrono::steady_clock::time_point start, end;

    start = chrono::steady_clock::now();
    babelkowe(list, n);
    end = chrono::steady_clock::now();
    cout << "Babelkowe : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms \n";

    start = chrono::steady_clock::now();
    wybor(list, n);
    end = chrono::steady_clock::now();
    cout << "Wybor : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms \n";

    start = chrono::steady_clock::now();
    wstawianie(list, n);
    end = chrono::steady_clock::now();
    cout << "Wstawianie : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms \n";

    start = chrono::steady_clock::now();
    szybkie(list, 0, n - 1);
    end = chrono::steady_clock::now();
    cout << "Szybkie : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms \n";

    start = chrono::steady_clock::now();
    scalanie(list, 0, n - 1);
    end = chrono::steady_clock::now();
    cout << "Scalanie : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms \n";


    cout << "\nPosortowane liczby: ";
    for (int i = 0; i < n; i++)
        cout << list[i] << " ";

    if (sprawdz(list, n)) {
        cout << "\nPosortowane poprawnie." << endl;
    } else {
        cout << "\nBlad sortowania." << endl;
    }


    delete[] list; // Zwolnienie pamięci
    delete[] buf;

    return 0;
}
