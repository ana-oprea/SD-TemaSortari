#include <iostream>
#include <vector>   
#include <ctime>        
#include <random>       // PT srand si rand
#include <fstream>      // PT FISIERE  
#include <chrono>       // PT system_clock (ca sa determin timpul de executie)   
#include <algorithm>    // PT sort()
#include <cmath>        // PT pow
using namespace std;

// INITIALIZEZ VECTORUL CU VALORI RANDOM
void init_vect(vector<int> &v, int N, int Max){
    // DAU CLEAR LA VECTOR CA SA MA ASIGUR CA NU AM ELEMENTE IN VECTOR DE LA CELELALTE SORTARI(RULARI)
    v.clear();
    // time(0) is the number of seconds since 1st Jan 1970 and i use that as a seed to generate the numbers
    srand(int(time(0))); // NEW SEED AT EVERY RUN
    // min + rand() % (max + 1 - min)  to generate a number from [min, max]
    for (int i = 0; i < N; i++)
        v.push_back(0 + rand() % (Max + 1 - 0));
}

// TESTEAZA DACA ALGORITMUL A SORTAT CORECT
// RETURNEAZA 1 DACA E SORTAT CORECT SAU 0 DACA NU
bool test_Sort(vector<int> v){
    for(int i = 0 ;i < v.size() - 1; i++){
        if (v[i] > v[i+1])
            return 0;
    }
    return 1;
}

// TREBUIE SA DAU CA PARAMETRU V CU REFERINTA CA ALTFEL NU O SA-MI MODIFICE VALORILE DIN VECTOR
// BUBBLE SORT COMPARA LA FIECARE PAS DOUA ELEM DIN VECTOR ALATURATE SI DACA NU SUNT IN ORDINE LE INTERSCHIMBA
void bubbleSort(vector <int> &v){
    bool continua = true;
    while(continua){
        continua = false;
        for (int i = 0; i < v.size(); i++){
            for (int j = i + 1; j < v.size(); j++)
                if (v[j-1] > v[j]){
                    swap(v[j], v[j-1]);
                    continua = true;
                }
            if (continua == false)
                break; // sau return;
        }
    }
}

void countSort(vector <int> &v, int maxim){
    vector<int> frecv;

    for (int i = 0; i <= maxim; i++) 
        frecv.push_back(0);;

    for (int i = 0; i < v.size(); i++)
        frecv[v[i]]++;
    
    int pozitie = 0;
    for (int i = 0; i <= maxim; i++) 
        for(int j = 0; j < frecv[i]; j++)
            v[pozitie++] = i;
}

void merge(vector<int> &v, int start, int end, int mid){
    vector<int> Left, Right;

    // INITIALIZEZ VECTORUL Left CU JUMATATEA DIN STANGA A SUBVECTORULUI v
    for (int i = start; i <= mid; i++)
        Left.push_back(v[i]);
    
    // INITIALIZEZ VECTORUL Right CU JUMATATEA DIN DREAPTA A SUBVECTORULUI v
    for (int i = mid + 1; i <= end; i++)
        Right.push_back(v[i]);

    int i = 0,      // pt left
        j = 0,      // pt Right
        k = start;  // pt v

    while (i < Left.size() && j < Right.size()){
        if (Left[i] < Right[j])
            v[k++] = Left[i++];
        else
            v[k++] = Right[j++];
        
    }

    while (i < Left.size())
        v[k++] = Left[i++];

    while (j < Right.size())
        v[k++] = Right[j++];
}

void mergeSort(vector<int> &v, int start, int end){
    // DACA AM MAI MULT DE UN ELEMENT IN v
    if (start < end){
        int mid = start + (end-start)/2;
        mergeSort(v,start, mid);    // PRIMA JUMATATE A LUI v
        mergeSort(v, mid+1, end);   // A DOUA JUMATATE A LUI v
        merge(v, start, end, mid);  // DAU MERGE PARTILOR
    }
}

// QUICK SORT CU MEDIANA DIN 3
int partition(vector<int> &v, int start, int end){
    //MEDIANA DIN 3
    // IAU 3 VALORI RANDOM DIN v
    int nr_rand1 = start + rand() % (end + 1 - start), 
        nr_rand2 = start + rand() % (end + 1 - start),
        nr_rand3 = start + rand() % (end + 1 - start);

    // PRESUPUN CA MEDIANA ESTE PRIMUL ELEMENT ALES RANDOM
    int indice_pivot = nr_rand1;
    if ((v[nr_rand1] >= v[nr_rand2] and v[nr_rand1] <= v[nr_rand3]) or (v[nr_rand1] <= v[nr_rand2] and v[nr_rand1] >= v[nr_rand3]))
        indice_pivot = nr_rand1;
    else{
        if ((v[nr_rand2] >= v[nr_rand1] and v[nr_rand2] <= v[nr_rand3]) or (v[nr_rand2] <= v[nr_rand1] and v[nr_rand2] >= v[nr_rand3]))
            indice_pivot = nr_rand2;
        else{
            indice_pivot = nr_rand3;
        }
    }
    int left = start;
    // VARIABILA pivot RETINE VALOAREA MEDIANEI DIN 3
    int pivot = v[indice_pivot];
    //cout << endl << "Pivot "<<pivot<< " " << endl;

    // INTERSCHIMB VALOAREA DE LA SFARSIT CU VALOAREA PIVOTULUI
    // CA SA AM PIVOTUL AL SFARISITUL VECTORULUI     
    swap(v[indice_pivot], v[end]);
    //cout << endl << "Pivot dupa swap"<<pivot<< " " << endl;

    for( int right = start; right < end; right ++)
        if (v[right] < pivot){
            swap(v[right], v[left]);
            left ++ ;
        }

    swap(v[left], v[end]);
    return left;
}

void quickSort(vector<int> &v, int start, int end){
    if (start < end){
        int pivot = partition(v, start, end);
        quickSort(v, start, pivot - 1);
        quickSort(v, pivot + 1, end);
    }
}

void countSortR(vector <int> &v, int maxim, int power, int baza){
    vector<vector<int>> B(baza);

    for (int i = 0; i < v.size(); i++)
        B[(v[i]/power)%10].push_back(v[i]);

    // for (int i = 0; i < B.size(); i++){
    //     // cout<< endl << "Bucketul " << i << ": ";
    //     for(int j = 0; j < B[i].size(); j++)
    //         cout<<B[i][j];}
    
    int pozitie = 0;

    for (int i = 0; i < B.size(); i++)
        for(int j = 0; j < B[i].size(); j++)
            v[pozitie++] = B[i][j];
}

int maxim(vector<int>v){
    int maxi = v[0];
    for (int i = 1; i < v.size(); i++)
        if (maxi < v[i])
            maxi = v[i];
    return maxi;
}

//LSD 
// RADIX SORT FOLOSESTE UN FEL DE COUNT SORT CA SUBRUTINA DE SORTARE
void radixSort(vector<int> &v, int baza){
    int maxi = maxim(v);
    for (int power = 1; maxi/power > 0; power*=10)
        countSortR(v, maxi, power, baza);
}


int main(){
    ifstream f("input.txt");
    int T,      // NR DE TESTE
        N,      // NR DE ELEM
        Max;    // CEL MAI MARE ELEM DIN VECTOR

    f >> T; 
    for (int i = 1; i <= T; i++){
        cout << "Test " << i << ": " << endl;
        f >> N;
        f >> Max;
        vector<int> v(N);
        auto start = chrono::system_clock::now(), end = chrono::system_clock::now();
        chrono::duration<double> time_elapsed;

        // SORTARE DIN C++
        if (N < pow(10,7)){
            init_vect(v, N, Max);
            start = chrono::system_clock::now();
            sort(v.begin(), v.end());
            end = chrono::system_clock::now();
            time_elapsed = end - start;
            cout << "Timp de executie pentru sortarea din C++: " << time_elapsed.count() << " *" <<test_Sort(v) <<endl;
        }
        else{
                cout << "Timpul de executie este prea mare si s-a oprit executia sortarii din C++." << endl;
        }

        // BUBBLE SORT
        if (N < pow(10,6)){
            init_vect(v, N, Max);
            start = chrono::system_clock::now();
            bubbleSort(v);
            end = chrono::system_clock::now();
            time_elapsed = end - start;

            cout << "Timp de executie pentru Bubble sort: " << time_elapsed.count() << " *" <<test_Sort(v) <<endl;
            }
            else{
                cout << "Timpul de executie este prea mare si s-a oprit executia sortarii cu Bubble Sort." << endl;
        }

        // COUNT SORT
        if (N < pow(10,11) ){
            init_vect(v, N, Max);
            start = chrono::system_clock::now();
            countSort(v, Max);;
            end = chrono::system_clock::now();
            time_elapsed = end - start;

            cout << "Timp de executie pentru Count sort: " << time_elapsed.count() << " *" <<test_Sort(v) <<endl;
        }
        else{
            cout << "Timpul de executie este prea mare si s-a oprit executia sortarii cu Count Sort." << endl;
        }

        // MERGE SORT
        if (N < pow(10,9))
        {
            init_vect(v, N, Max);
            start = chrono::system_clock::now();
            mergeSort(v, 0, v.size()-1);
            end = chrono::system_clock::now();
            time_elapsed = end - start;

            cout << "Timp de executie pentru Merge sort: " << time_elapsed.count() << " *" <<test_Sort(v) <<endl;
        }
        else{
            cout << "Timpul de executie este prea mare si s-a oprit executia sortarii cu Merge Sort." << endl;
        }

        // QUICK SORT
        if(N < pow(10,7)){
            init_vect(v, N, Max);
            start = chrono::system_clock::now();
            quickSort(v, 0, v.size()-1);
            end = chrono::system_clock::now();
            time_elapsed = end - start;
            cout << "Timp de executie pentru Quick sort: " << time_elapsed.count() << " *" <<test_Sort(v) <<endl;
        }
        else{
            cout << "Timpul de executie este prea mare si s-a oprit executia sortarii cu Quick Sort." << endl;
        }

        // RADIX SORT
        if(N < pow(10,9)){
            init_vect(v, N, Max);
            start = chrono::system_clock::now();
            radixSort(v, 10);
            end = chrono::system_clock::now();
            time_elapsed = end - start;
            cout << "Timp de executie pentru Radix sort: " << time_elapsed.count() << " *" <<test_Sort(v) <<endl;
        }
        else{
            cout << "Timpul de executie este prea mare si s-a oprit executia sortarii cu Radix Sort." << endl;
        }
            v.clear();
    }

    f.close();
    return 0;
}