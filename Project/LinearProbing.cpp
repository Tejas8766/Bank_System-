#include "LinearProbing.h"


// done
void LinearProbing::createAccount(std::string id, int count) {
    if(bankStorage1d.empty()) 
        bankStorage1d = std::vector<Account> (M,{"-",INT32_MIN}) ;
    
    int i = 0 ;
    int hashVal = hash(id) ;
    while(bankStorage1d[hashVal].id != "-") {
        hashVal = (hashVal - (i++)*jump) % M ;
        hashVal = (hashVal + i*jump) % M ;
    }
    bankStorage1d[hashVal] = Account {id , count} ;
    TotalSize++ ;
    hashID.push_back(hashVal) ;
}


// done
std::vector<int> LinearProbing::getTopK(int k) {
    if(TotalSize == 0)
        return std::vector<int> {} ;

    std::vector<int> ans(TotalSize) ;
    int idxAns = 0 ;

    for(int& h:hashID)
        if(bankStorage1d[h].id != "+")
            ans[idxAns++] = bankStorage1d[h].balance ;

    mergeSort(ans,0,TotalSize - 1) ;

    if(k < TotalSize) 
        ans.erase(ans.begin()+k,ans.end()) ;
    
    return ans;
}

// done
int LinearProbing::getBalance(std::string id) {

    if(bankStorage1d.empty())
        return -1 ;

    int hashVal = hash(id) ;

    if(bankStorage1d[hashVal].id == id)
        return bankStorage1d[hashVal].balance ;

    hashVal = (hashVal + jump) % M ;
    int i = 0 ;

    while(bankStorage1d[hashVal].id != "-") {

        if(bankStorage1d[hashVal].id == id)
            return bankStorage1d[hashVal].balance ;
        
        hashVal = (hashVal - (i++)*jump) % M ;
        hashVal = (hashVal + i*jump) % M ;
        
    }
    
    return -1;
}

// done
void LinearProbing::addTransaction(std::string id, int count) {

    if(bankStorage1d.empty())
        bankStorage1d = std::vector<Account> (M,{"-",INT32_MIN}) ;

    int hashVal = hash(id) ;

    if(bankStorage1d[hashVal].id == id) {           // do transaction and return
        bankStorage1d[hashVal].balance += count ;
        if(bankStorage1d[hashVal].balance < 0)
            bankStorage1d[hashVal].balance = 0 ;
        return ;
    }
    
    hashVal = (hashVal + jump) % M ;
    int i = 0 ;

    while(bankStorage1d[hashVal].id != "-") {

        if(bankStorage1d[hashVal].id == id) {           // do transaction and return
            bankStorage1d[hashVal].balance += count ;
            if(bankStorage1d[hashVal].balance < 0)
                bankStorage1d[hashVal].balance = 0 ;
            return ;
        }
        
        hashVal = (hashVal - (i++)*jump) % M ;
        hashVal = (hashVal + i*jump) % M ;
        
    }
    // id not found, but we are at the location where it would be inserted
    if(count > 0) {
        bankStorage1d[hashVal] = Account {id , count} ;
        TotalSize++ ;
    } else {
        bankStorage1d[hashVal] = Account {id , 0 } ;
        TotalSize++ ;
    }
    hashID.push_back(hashVal) ;
    
}

// done
bool LinearProbing::doesExist(std::string id) {
    if(bankStorage1d.empty())
        return false ;
    int hashVal = hash(id) ;
    if(bankStorage1d[hashVal].id == id)
        return true ;

    hashVal = (hashVal + jump) % M ;
    int i = 0 ;

    while(bankStorage1d[hashVal].id != "-") {
        if(bankStorage1d[hashVal].id == id)
            return true ;
        
        hashVal = (hashVal - (i++)*jump) % M ;
        hashVal = (hashVal + i*jump) % M ;
    }

    return false;
}

// done
bool LinearProbing::deleteAccount(std::string id) {
    if(bankStorage1d.empty())
        return false ;
    
    int hashVal = hash(id) ;
    if(bankStorage1d[hashVal].id == id) {           // id found, delete and return true
        bankStorage1d[hashVal].id = "+" ;
        bankStorage1d[hashVal].balance = INT32_MIN ;
        TotalSize-- ;
        return true ;
    }

    hashVal = (hashVal + jump) % M ;
    int i = 0 ;

    while(bankStorage1d[hashVal].id != "-") {
        if(bankStorage1d[hashVal].id == id) {       // id found, delete and return true
            bankStorage1d[hashVal].id = "+" ;
            bankStorage1d[hashVal].balance = INT32_MIN ;
            TotalSize-- ;
            return true ;
        }
        
        hashVal = (hashVal - (i++)*jump) % M ;
        hashVal = (hashVal + i*jump) % M ;
    }

    return false;
}

// done
int LinearProbing::databaseSize() {
    return TotalSize;
}

// done
int LinearProbing::hash(std::string id) {
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
void LinearProbing::mergeSort(std::vector<int> &v, int s, int e) {
    if (s >= e)
        return;

    int m = s + (e - s) / 2;
    mergeSort(v, s, m);
    mergeSort(v, m + 1, e);
    merge(v, s, e);
}

// done
void LinearProbing::merge(std::vector<int> &v, int s, int e) {
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
