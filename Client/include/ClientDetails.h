//
// Created by taliakat@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef ASS3_CLIENTDETAILS_H
#define ASS3_CLIENTDETAILS_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>


using namespace std;



class ClientDetails {
private:
    std::string _name;
    std::string _passcode;
    std::unordered_map<std::string, int> _subscriptions;
    std::vector<std::string> _inventory;
    std::vector<std::string> _wishList;
    std::unordered_map<std::string,std::string> _borrowedFrom; //TODO: first is the book _name
    std::unordered_map<int, string> _receiptMsg;
    std::mutex mutexSubscriptions;
    std::mutex mutexInventory;
    std::mutex mutexWishList;
    std::mutex mutexBorrowedFrom;
    std::mutex mutexReceiptMsg;


public:

    ClientDetails();

    virtual ~ClientDetails(){}

    int findBookIndex(const string& book);

    int findBookInWishList(const string& book);

    string deleteBook(const string& book);

    string printInventory();

    ClientDetails(string name, string passcode);

    string &getPasscode() ;

    unordered_map<std::string, std::string> &getBorrowedFrom() ;

    unordered_map<std::string, int> &getSubscriptions() ;

    vector<std::string> &getInventory() ;

    string &getName() ;

    unordered_map<int,string> &getReceiptMsg() ;

    vector<std::string> &getWishList();

    void setName( string &name);

     mutex &getMutexInventory() ;

    void setPasscode( string &passcode);

     mutex &getMutexSubscriptions() ;

     mutex &getMutexWishList() ;

     mutex &getMutexBorrowedFrom() ;

     mutex &getMutexReceiptMsg() ;

};


#endif //ASS3_CLIENTDETAILS_H
