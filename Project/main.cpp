#include<iostream>
#include<vector>
using namespace std;


// #define M (int)102497 ;


struct Account {
    std::string id;
    int balance;
};


// done
void merge(std::vector<int>& v, int s, int e) {
    int m = s + (e - s) / 2;
    int SizeLeft = m - s + 1;
    int SizeRight = e - m;
 
    int *leftArr = new int[SizeLeft],
        *rightArr = new int[SizeRight];
 
    for (int i = 0; i < SizeLeft; i++)
        leftArr[i] = v[s + i];
    for (int j = 0; j < SizeRight; j++)
        rightArr[j] = v[m + 1 + j];
 
    int idxLftArr = 0, idxRtArr = 0, idxMainArr = s;
 
    while (idxLftArr < SizeLeft && idxRtArr < SizeRight)
        if (leftArr[idxLftArr] >= rightArr[idxRtArr])
            v[idxMainArr++] = leftArr[idxLftArr++];
        else
            v[idxMainArr++] = rightArr[idxRtArr++];

    while (idxLftArr < SizeLeft)
        v[idxMainArr++] = leftArr[idxLftArr++];
 
    while (idxRtArr < SizeRight)
        v[idxMainArr++] = rightArr[idxRtArr++];

    delete[] leftArr;
    delete[] rightArr;
}


// done
void mergeSort(std::vector<int>& v, int s , int e) {
    if (s >= e)
        return;

    int m = s + (e - s) / 2 ;
    mergeSort(v , s , m) ;
    mergeSort(v , m + 1 , e) ;
    merge(v , s , e) ;
}





// int Hash(string s) {
//     vector<double> randomno = {1.27 , 3.47 , 2.85 , 1.57 , 2.14 , 2.32 , 3.18 , 1.69 , 3.67 , 1.75} ;
//     // int LD = *s.end() - '0' ;
//     double a = randomno[s[20] - '0'] ;
//     long long ans = 0 ;
//     int m = M ;
//     int ct = 0;
//     for(char i:s) {
//         cout << a << endl ;
//         ans = (ans + (long long)(i*a))%m ;
//         a *= a ;
//         if(a>22000)
//             a = randomno[s[20] - '0'] ;
//     }
//     return (int)ans ;
// }

    // int i = 0 ;
    // int hashVal = hash(id) ;
    // while(bankStorage1d[hashVal].balance != INT32_MIN)
    //     hashVal += - i*jump + (++i)*jump ;


int Hash(std::string id) {
    int M = 10000019 ;        // prime number
    std::vector<int> rndmno1 = {23 , 31 , 41 , 59 , 29 , 37 , 67 , 43 , 53 , 13} ;
    std::vector<int> rndmno2 = {1367 , 2003 , 1697 , 3089 , 2273 , 2017 , 1783 , 1907 , 3001 , 3023} ;
    long long a = (long long)rndmno1[id[19] - '0'] ;
    int Ma = rndmno2[id[20] - '0'] ;
    long long ans = 0;

    for (char i : id) {
        ans = (ans + (long long)((i * a) % M)) % M;
        a = (a*a) % Ma;
    }

    return (int)ans;
}








int main() {

    cout << Hash("aaaa9123876_9988776655") << endl ;

    return 0;
}