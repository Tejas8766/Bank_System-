#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int TotalSize = 0 ;
    std::vector<int> hashID ;
    void merge(std::vector<int>& v, int s , int e) ;
    void mergeSort(std::vector<int>& v, int s , int e) ;
    int M = 10000019 ;        // prime number
};

#endif // CHAINING_H
