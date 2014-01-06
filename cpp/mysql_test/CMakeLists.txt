PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4)
#AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_C_FLAGS_DEBUG "-O3 -Wall -g -std=c99")

INCLUDE_DIRECTORIES(/usr/include/mysql)
#INCLUDE_DIRECTORIES(/usr/local/include/)
#INCLUDE_DIRECTORIES(/usr/local/include/cppconn)
#LINK_DIRECTORIES(/usr/local/lib/)
LINK_DIRECTORIES(/usr/lib/)

ADD_EXECUTABLE(mysql_test 
                mysql_test.cpp
                zdb_base.cpp)
#TARGET_LINK_LIBRARIES(mysql_test mysqlcppconn)
TARGET_LINK_LIBRARIES(mysql_test mysqlclient)
