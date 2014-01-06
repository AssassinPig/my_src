#ifndef __ZDB_BASE_H__
#define __ZDB_BASE_H__

#include <my_global.h>
#include <mysql.h>

class zdb_base
{
    public:
        zdb_base(); 
        virtual ~zdb_base();

        void attach(zdb_base* other);
        void detach();
        void connect(const char* hostip, const char* user, const char* password, const char* db, int port=3306);

        virtual void query(const char* sql);

    private:
       MYSQL* m_conn; 
};

#endif //__ZDB_BASE_H__

