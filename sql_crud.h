#ifndef SQL_CRUD_H_
#define SQL_CRUD_H_

void sql_init();
void sql_connect();
void insert_msg(char *table_name, char *field, char *msg ,int in_len);
void sql_close();

#endif
