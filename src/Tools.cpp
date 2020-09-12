//
// Created by taliakat@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "../include/Tools.h"



vector<string> Tools::split(string str, char delimiter) {
    size_t i = 0;
    vector<string> ret;
    string word;
    while(i<str.size()){
        while(i < str.size() && str[i] != delimiter){
            word = word + str[i];
            i++;

        }
        ret.push_back(word);
        if(i<str.size()) {
            str = str.substr(i + 1, str.size() - i - 1);
            i = 0;
            word.clear();
        }
    }
    return ret;
}
 //old one

//void Tools::printMessage(vector<string> vector) {
//    string st;
//    for(size_t i =0; i< vector.size();i++){
//        st = st+ vector[i]+'\n';
//    }
//   cout<<st<<endl;
//}


// new one

void Tools::printMessage(vector<string> vector) {
    string str = vector[0];
    if(str == "ERROR") {
        std::vector<string> tmp = split(vector[1], ':');
        str = str + ":" + tmp[1];
    }
    else if(vector[vector.size()-1].length() > 1)
        str = str + ":" + vector[vector.size()-1];
    cout<<str<<endl;
}

vector<string> Tools::fixSplitedVector(vector<string> words) {
    string str;
    vector<string> ret;
    if(words[0]=="add" || words[0]=="borrow"|| words[0]=="return"){
        for(size_t i =0; i < words.size(); i++){
            if(i>=2)
                str = str+words[i]+" ";
            else
                ret.push_back(words[i]);
        }
        str = str.substr(0, str.size()-1);
        ret.push_back(str);
    }
    else if(words.size()>=6 && words[4]=="book"){
        for(size_t i =0; i < words.size(); i++){
            if(i>=5)
                str = str+words[i]+" ";
            else
                ret.push_back(words[i]);
        }
        str = str.substr(0, str.size()-1);
        ret.push_back(str);
    }
    else if(words.size()>=5 && words[3]=="borrow"){
        for(size_t i =0; i < words.size(); i++){
            if(i>=4)
                str = str+words[i]+" ";
            else
                ret.push_back(words[i]);
        }
        str = str.substr(0, str.size()-1);
        ret.push_back(str);
    }
    else if(words.size()>=3 && words[1]=="has"){
        for(size_t i =0; i < words.size(); i++){
            if(i>=2)
                str = str+words[i]+" ";
            else
                ret.push_back(words[i]);
        }
        str = str.substr(0, str.size()-1);
        ret.push_back(str);
    }
    else if(words[0]=="Taking"|| words[0]=="Returning"){
        for(size_t i =0; i < words.size()-2; i++){
            if(i>=1)
                str = str+words[i]+" ";
            else
                ret.push_back(words[i]);
        }
        str = str.substr(0, str.size()-1);
        ret.push_back(str);
        ret.push_back(words[words.size()-2]);
        ret.push_back(words[words.size()-1]);

    }
    else
        return words;
    return ret;
}

