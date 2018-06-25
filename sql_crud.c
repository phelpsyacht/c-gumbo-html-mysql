#include  <stdio.h>
#include <mysql/mysql.h>   
#include <string.h>

#define LIMIT_N 80

MYSQL *conn_prt;
static const char *set_utf8 = "SET NAMES UTF8";
char *res_row[LIMIT_N];

void sql_init()
{
	conn_prt = mysql_init(NULL);
}

void sql_connect()
{
	if(!mysql_real_connect(conn_prt,"localhost","root",
		"book","book",0,NULL,0))
	{
		printf("failed to connect:%s\n",mysql_error(conn_prt));
		exit(0) ;
	}
	printf("connect success!\n");
}

void insert_msg(char *table_name, char *field, char *msg ,int in_len)
{
	int t;
	char insert_query[in_len];
	char left[5]="(";
	char right[5]=") ";
	char values[50]="values";
	
	char insert_qy[50] = "insert into ";

	strcpy(insert_query,insert_qy);  
	printf("%s\n", insert_query);
	
	strcat(insert_query,left);
	strcat(insert_query,field);
	strcat(insert_query,right);
	strcat(insert_query,values);
	strcat(insert_query,left);
	strcat(insert_query,msg);
	strcat(insert_query,right);
	printf("%s\n",insert_query);

	mysql_real_query(conn_prt,set_utf8,strlen(set_utf8));
	t = mysql_real_query(conn_prt,insert_query,strlen(insert_query));
	if(t)
	{
		printf("failed to query:%s\n",mysql_error(conn_prt));
		return ;
	}

	printf("insert ok\n");
}

void sql_close(){
	mysql_close(conn_prt);
};


