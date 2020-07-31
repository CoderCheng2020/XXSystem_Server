#ifndef __ACCESSDB_H__
#define __ACCESSDB_H__

#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include "CommonFlags.h"

using namespace std;

class AccessDB
{
public:
	static AccessDB* GetInstance()
	{
		if(m_instance == NULL)
		{
			m_instance = new AccessDB();
		}
		return m_instance;
	}

	bool executeSQL(string& sql_str, string& resultStr);
	bool create_table(string& table_str_sql);
	~AccessDB();
private:
	MYSQL *m_connection;
	MYSQL_RES *m_res;
	MYSQL_FIELD* m_fieldInfo;
	MYSQL_ROW m_row;
	static AccessDB* m_instance;
private:
	AccessDB();
	bool initDB(string server_host, string user, string password, string db_name);
};


#endif

