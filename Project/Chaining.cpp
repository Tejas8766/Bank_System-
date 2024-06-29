#include "Chaining.h"

// done
void Chaining::createAccount(std::string id, int count) {

    if(bankStorage2d.empty()) 
        bankStorage2d.resize(M) ;
    
    int hashVal = hash(id) ;
    bankStorage2d[hashVal].push_back(Account {id , count}) ;
    TotalSize++ ;
    hashID.push_back(hashVal) ;
}


// done
std::vector<int> Chaining::getTopK(int k) {
    if(TotalSize == 0)
        return std::vector<int> {} ;
    
    std::vector<int> ans(TotalSize) ;
    int x = 0 ;
    for(int& i:hashID)
        for(Account& j:bankStorage2d[i])
            ans[x++] = j.balance ;
    
    mergeSort(ans,0,TotalSize-1) ;
    
    if(k < TotalSize) 
        ans.erase(ans.begin()+k,ans.end()) ;
    
    return ans ;
}


// done
int Chaining::getBalance(std::string id) {

    if(bankStorage2d.empty()) 
        return -1 ;

    int hashVal = hash(id) ;
    for(Account& i:bankStorage2d[hashVal])
        if(i.id == id)
        return i.balance ;
    
    return -1;

}


// done
void Chaining::addTransaction(std::string id, int count) {
    if(bankStorage2d.empty())
        bankStorage2d.resize(M) ;

    int hashVal = hash(id) ;

    for(Account& i:bankStorage2d[hashVal])
        if(i.id == id) {             // id found
            i.balance += count ;
            if(i.balance < 0) 
                i.balance = 0 ;
            return ;                // stop the function
        }

    if(count > 0) {                 // id not found so create one
        bankStorage2d[hashVal].push_back(Account {id , count}) ;
        TotalSize++ ;
    } else {
        bankStorage2d[hashVal].push_back(Account {id , 0}) ;
        TotalSize++ ;
    }
    hashID.push_back(hashVal) ;
}


// done
bool Chaining::doesExist(std::string id) {
    if(bankStorage2d.empty())
        return false ;
    int hashVal = hash(id) ;
    for(Account& i:bankStorage2d[hashVal])
        if(i.id == id)
            return true ;
    return false;
}


// done
bool Chaining::deleteAccount(std::string id) {
    if(bankStorage2d.empty())
        return false ;
    
    int hashVal = hash(id) ;
    for(Account& i:bankStorage2d[hashVal])
        if(i.id == id) {
            bankStorage2d[hashVal].erase(bankStorage2d[hashVal].begin()+int(&i - &bankStorage2d[hashVal][0])) ;
            TotalSize-- ;
            if(bankStorage2d[hashVal].empty())
                for(int& i:hashID)
                    if(i == hashVal) {
                        hashID.erase(hashID.begin() + int(&i - &hashID[0])) ;
                        break ;
                    }

            return true ;
        }
    
    return false;
}


// done
int Chaining::databaseSize() {
    return TotalSize ;
}


// done
int Chaining::hash(std::string id) {
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

// done
void Chaining::mergeSort(std::vector<int> &v, int s, int e) {
    if (s >= e)
        return;

    int m = s + (e - s) / 2;
    mergeSort(v, s, m);
    mergeSort(v, m + 1, e);
    merge(v, s, e);
}

// done
void Chaining::merge(std::vector<int> &v, int s, int e) {
    int m = s + (e - s) / 2;
    int SizeLeft = m - s + 1;
    int SizeRight = e - m;

    int *leftArr = new int[SizeLeft],
        *rightArr = new int[SizeRight];

    for (int i = 0; i < SizeLeft; i++)
        leftArr[i] = v[s + i];
    for (int j = 0; j < SizeRight; j++)
        rightArr[j] = v[m + 1 + j];

    int idxLftArr = 0, idxRtArr = 0;
    int idxMainArr = s;

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
