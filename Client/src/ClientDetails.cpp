//
// Created by taliakat@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/ClientDetails.h"

#include <utility>

using namespace std;

ClientDetails::ClientDetails(): _name(""), _passcode(""), _subscriptions(), _inventory(), _wishList(), _borrowedFrom(), _receiptMsg(), mutexSubscriptions(), mutexInventory(), mutexWishList(), mutexBorrowedFrom(), mutexReceiptMsg(){}

ClientDetails::ClientDetails(string name_,string passcode_): _name(std::move(name_)), _passcode(std::move(passcode_)), _subscriptions(), _inventory(), _wishList(), _borrowedFrom(), _receiptMsg(), mutexSubscriptions(), mutexInventory(), mutexWishList(), mutexBorrowedFrom(), mutexReceiptMsg(){}

int ClientDetails::findBookIndex(const string& book) {
    lock_guard<mutex> lock(mutexInventory);
    for(size_t i = 0; i < _inventory.size(); i++){
        if(_inventory[i] == book)
            return i;
    }
    return -1;
}

int ClientDetails::findBookInWishList(const string &book) {
    lock_guard<mutex> lock(mutexWishList);
    for (size_t i = 0; i < _wishList.size(); i++) {
        if (_wishList[i] == book)
            return i;
    }
    return -1;
}

string ClientDetails::deleteBook(const string& book) {
    string ret;
    lock_guard<mutex> lock(mutexInventory);
    for(size_t i = 0; i < _inventory.size() && (ret.empty()); i++) {
        if (_inventory[i] == book) {
            ret = book;
            _inventory.erase(_inventory.begin() + i);
        }
    }
    return ret;
}

string ClientDetails::printInventory() {
    string ret;
    lock_guard<mutex> lock(mutexInventory);
    for(const auto & i : _inventory){
        ret = ret+i+",";
    }
    ret = ret.substr(0, ret.size()-1);
    return ret;
}

string &ClientDetails::getPasscode()  {
    return _passcode;
}

string &ClientDetails::getName()  {
    return _name;
}

 unordered_map<std::string, std::string> &ClientDetails::getBorrowedFrom()  {
    //lock_guard<mutex> lock(mutexBorrowedFrom);
    return _borrowedFrom;
}

 unordered_map<std::string, int> &ClientDetails::getSubscriptions()  {
    //lock_guard<mutex> lock(mutexSubscriptions);
    return _subscriptions;
}

 vector<std::string> &ClientDetails::getInventory()  {
    //lock_guard<mutex> lock(mutexInventory);
    return _inventory;
}

unordered_map<int,string> &ClientDetails::getReceiptMsg()  {
    //lock_guard<mutex> lock(mutexReceiptMsg);
    return _receiptMsg;
}

vector<std::string> &ClientDetails::getWishList(){
    //lock_guard<mutex> lock(mutexWishList);
    return _wishList;
}

void ClientDetails::setName( string &name) {
    ClientDetails::_name = name;
}

void ClientDetails::setPasscode( string &passcode) {
    ClientDetails::_passcode = passcode;
}

 mutex &ClientDetails::getMutexInventory()  {
    return mutexInventory;
}

 mutex &ClientDetails::getMutexSubscriptions()  {
    return mutexSubscriptions;
}

 mutex &ClientDetails::getMutexWishList()  {
    return mutexWishList;
}

 mutex &ClientDetails::getMutexBorrowedFrom()  {
    return mutexBorrowedFrom;
}

 mutex &ClientDetails::getMutexReceiptMsg()  {
    return mutexReceiptMsg;
}







