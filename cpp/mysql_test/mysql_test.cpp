#include "zdb_orm.h"
#include "zdb_base.h"

#define DBHOST "192.168.0.120"
#define USER "zhufeng"
#define PASSWORD "654321"
#define DATABASE "myblog"

#define NUMOFFSET 100
#define COLNAME 200

int main(int argc, const char *argv[]) {
    const std::string url(DBHOST);
    const std::string user(USER); 
    const std::string password(PASSWORD); 
    const std::string database(DATABASE); 

    zdb_base base;
    base.connect(url.c_str(), 
                user.c_str(),
                password.c_str(),
                database.c_str());

    std::string sql = "select * from user";
    base.query(sql.c_str());

    return 0;
}
