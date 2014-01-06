PROJECT(mysql_test)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS_DEBUG "-O3 -Wall -g -std=gnu99")

INCLUDE_DIRECTORIES(/usr/include/mysql/)
LINK_DIRECTORIES(/usr/lib/)

ADD_EXECUTABLE(test_mysql test_mysql.c)
TARGET_LINK_LIBRARIES(test_mysql mysqlclient)
