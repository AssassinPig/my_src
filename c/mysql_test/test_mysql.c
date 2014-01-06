#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

int createdb()
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	if (mysql_real_connect(conn, "192.168.0.120", "zhufeng", 
				"654321", "myblog", 3306, NULL, 0) == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	if (mysql_query(conn, "create database testdb")) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	mysql_close(conn);

	return 0;
}

void querydata()
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	if (mysql_real_connect(conn, "192.168.0.120", "zhufeng", 
				"654321", "myblog", 3306, NULL, 0) == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	if (mysql_query(conn, "select * from myblog.user")) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

        MYSQL_RES *result;
        MYSQL_ROW row;
        int num_fields;
        int i;

        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result)))
        {
            for(i = 0; i < num_fields; i++)
            {
                printf("%s ", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
        mysql_free_result(result);

        mysql_close(conn);
}

int main(int argc, char **argv)
{
    printf("MySQL client version: %s\n", mysql_get_client_info());
    //createdb();
    querydata();

    return 0;
}
