//
// Created by taliakat@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef ASS3_TOOLS_H
#define ASS3_TOOLS_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <mutex>

using namespace std;

class Tools {

public:
    static vector<string> split(string str, char delimiter);
    static void printMessage(vector<string>);
    static vector<string> fixSplitedVector(vector<string>);

};


#endif //ASS3_TOOLS_H
