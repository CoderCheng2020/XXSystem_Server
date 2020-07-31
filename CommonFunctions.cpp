/*
 * CommonFunctions.cpp
 *
 *  Created on: 2020年5月8日
 *      Author: root
 */

#include "CommonFunctions.h"
CommonFunctions* CommonFunctions::m_instance = NULL;

CommonFunctions::CommonFunctions() {
	// TODO Auto-generated constructor stub

}

CommonFunctions::~CommonFunctions() {
	// TODO Auto-generated destructor stub
}

void CommonFunctions::SplitString(const string& s, const string& c, vector<string>& v)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}
