/*
 * CommonFunctions.h
 *
 *  Created on: 2020年5月8日
 *      Author: root
 */

#ifndef SRC_COMMONFUNCTIONS_H_
#define SRC_COMMONFUNCTIONS_H_
#include <string>
#include <vector>

using namespace std;

class CommonFunctions {
public:
	static CommonFunctions* GetInstance()
	{
		if(m_instance == NULL)
		{
			m_instance = new CommonFunctions();
		}
		return m_instance;
	}
	void SplitString(const string& s, const string& c, vector<string>& v);

	virtual ~CommonFunctions();
private:
	CommonFunctions();
	static CommonFunctions* m_instance;
};

#endif /* SRC_COMMONFUNCTIONS_H_ */
