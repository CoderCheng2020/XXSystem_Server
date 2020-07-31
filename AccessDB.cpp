#include "AccessDB.h"

AccessDB* AccessDB::m_instance = NULL;

AccessDB::AccessDB()
{
	m_connection = mysql_init(NULL);
	if(m_connection == NULL)
	{
		perror("mysql_init");
		exit(1);
	}
	string computerName("localhost");
	string userName("root");
	string userPwd("HGCheng387417840*");
	string DBName("XXSYSTEM");
	initDB(computerName, userName, userPwd, DBName);
}

AccessDB::~AccessDB()
{
	if(m_connection != NULL)
	{
		mysql_close(m_connection);
	}
}

bool AccessDB::initDB(string server_host, string user, string password, string db_name)
{
	m_connection = mysql_real_connect(m_connection, server_host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), 0, NULL, 0);
	
	if(m_connection == NULL)
	{
		perror("mysql_real_connect");
		exit(1);
	}
	
	return true;
}

bool AccessDB::executeSQL(string& sql_str, string& resultStr)
{
	if(mysql_query(m_connection, "set names utf8"))
	{
		fprintf(stderr, "%d: %s\n", mysql_errno(m_connection), mysql_error(m_connection));
	}
	
	int t = mysql_query(m_connection, sql_str.c_str());
	
	if(t)
	{
		printf("Error making query: %s\n", mysql_error(m_connection));
		exit(1);
	}
	else
	{
		m_res = mysql_use_result(m_connection);
		if(m_res)
		{
			for(int i=0; i<mysql_field_count(m_connection); i++)
			{
				m_row = mysql_fetch_row(m_res);
				m_fieldInfo = mysql_fetch_fields(m_res);
				if(m_row <= 0)
				{
					break;
				}
				for(int r=0; r<mysql_num_fields(m_res); r++)
				{
                    PRINT("%s\t", m_row[r]);
                    resultStr += string(m_fieldInfo[r].name) + "," + m_row[r] + "#";
				}
                 resultStr += "%";
                PRINT("\n");
			}
		}
		mysql_free_result(m_res);
	}
	return true;
}

bool AccessDB::create_table(string& table_str_sql)
{
	int t = mysql_query(m_connection, table_str_sql.c_str());
	if(t)
	{
		printf("Error making query: %s\n", mysql_error(m_connection));
		exit(1);
	}
	return true;
}
