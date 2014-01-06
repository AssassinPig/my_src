#include "zdb_base.h"

zdb_base::zdb_base()
{
    m_conn = mysql_init(NULL); 
}
     
zdb_base::~zdb_base()
{
    mysql_close(m_conn);
}

void zdb_base::attach(zdb_base* other)
{
   mysql_close(m_conn); 
   m_conn = mysql_init(other->m_conn);
}

void zdb_base::detach()
{
    mysql_close(m_conn);
    m_conn = NULL;
}

void zdb_base::connect(const char* hostip, const char* user, const char* password, const char* db, int port)
{
    if( mysql_real_connect(m_conn, hostip, user, password, db, port, NULL, 0) == NULL) {
        printf("zdb_base::connect() failed\n");
    }    
}

void zdb_base::query(const char* sql)
{
   if(mysql_query(m_conn, sql)) {
        printf("zdb_base::query failed\n"); 
        printf("sql:%s\n", sql); 
   }
}
