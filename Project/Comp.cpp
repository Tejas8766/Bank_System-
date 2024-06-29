#include "Comp.h"


void Comp::createAccount(std::string id, int count) {
    if(bankStorage1d.empty()) 
        bankStorage1d = std::vector<Account> (M,{"-",INT32_MIN}) ;
    
    int i = 0 ;
    int h1 = hash(id) ;
    int h2 = hashHelper(id) ;
    while(bankStorage1d[h1].id != "-") {
        h1 = (h1 - (i++)*h2) % M ;
        h1 = (h1 + i*h2) % M ;
    }
    bankStorage1d[h1] = Account {id , count} ;
    TotalSize++ ;
    hashID.push_back(h1) ;
}

std::vector<int> Comp::getTopK(int k) {
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


int Comp::getBalance(std::string id) {
    if(bankStorage1d.empty())
        return -1 ;
    
    int i = 0 ;
    int h1 = hash(id) ;
    int h2 = hashHelper(id) ;

    while(bankStorage1d[h1].id != "-") {
        if(bankStorage1d[h1].id == id)
            return bankStorage1d[h1].balance ;

        h1 = (h1 - (i++)*h2) % M ;
        h1 = (h1 + i*h2) % M ;
    }

    return -1;
}

void Comp::addTransaction(std::string id, int count) {
    if(bankStorage1d.empty())
        bankStorage1d = std::vector<Account> (M,{"-",INT32_MIN}) ;

    int i = 0 ;
    int h1 = hash(id) ;
    int h2 = hashHelper(id) ;

    while(bankStorage1d[h1].id != "-") {
        if(bankStorage1d[h1].id == id) {
            bankStorage1d[h1].balance += count ;
            if(bankStorage1d[h1].balance < 0)
                bankStorage1d[h1].balance = 0 ;
            return ;
        }

        h1 = (h1 - (i++)*h2) % M ;
        h1 = (h1 + i*h2) % M ;
    }

    // id not found, but we are at the location where it would be inserted
    if(count > 0) {
        bankStorage1d[h1] = Account {id , count} ;
        TotalSize++ ;
    } else {
        bankStorage1d[h1] = Account {id , 0 } ;
        TotalSize++ ;
    }
    hashID.push_back(h1) ;

}

bool Comp::doesExist(std::string id) {
    if(bankStorage1d.empty())
        return false ;
    
    int i = 0 ;
    int h1 = hash(id) ;
    int h2 = hashHelper(id) ;
    while(bankStorage1d[h1].id != "-") {
        if(bankStorage1d[h1].id == id)
            return true ;
        h1 = (h1 - (i++)*h2) % M ;
        h1 = (h1 + i*h2) % M ;
    }

    return false;
}


bool Comp::deleteAccount(std::string id) {
    if(bankStorage1d.empty())
        return false ;
    
    int i = 0 ;
    int h1 = hash(id) ;
    int h2 = hashHelper(id) ;

    while(bankStorage1d[h1].id != "-") {
        if(bankStorage1d[h1].id == id) {       // id found, delete and return true
            bankStorage1d[h1].id = "+" ;
            bankStorage1d[h1].balance = INT32_MIN ;
            TotalSize-- ;
            return true ;
        }
        h1 = (h1 - (i++)*h2) % M ;
        h1 = (h1 + i*h2) % M ;
    }

    return false;
}



int Comp::databaseSize() {
    return TotalSize;
}




int Comp::hash(std::string id) {
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

int Comp::hashHelper(std::string id) {
    std::vector<int> rndmno1 = {23 , 31 , 41 , 59 , 29 , 37 , 67 , 43 , 53 , 13} ;
    std::vector<int> rndmno2 = {1367 , 2003 , 1697 , 3089 , 2273 , 2017 , 1783 , 1907 , 3001 , 3023} ;
    long long a = (long long)rndmno1[id[19] - '0'] ;
    int Ma = rndmno2[id[20] - '0'] ;
    long long ans = 0;

    for (char i : id) {
        ans = (ans + (long long)((i * a) % M2)) % M2;
        a = (a*a) % Ma;
    }
    
    return (int)(M2-ans);
}


// done
void Comp::mergeSort(std::vector<int> &v, int s, int e) {
    if (s >= e)
        return;

    int m = s + (e - s) / 2;
    mergeSort(v, s, m);
    mergeSort(v, m + 1, e);
    merge(v, s, e);
}

// done
void Comp::merge(std::vector<int> &v, int s, int e) {
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


// Feel free to add any other helper functions you need
// Good Luck!