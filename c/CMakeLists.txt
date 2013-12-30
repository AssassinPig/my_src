PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
#INCLUDE_DIRECTORIES(/usr/local/include/)
SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_C_FLAGS_DEBUG "-O3 -Wall -g -std=c99")
SET(CMAKE_C_FLAGS_DEBUG "-O3 -Wall -g -std=gnu99")

ADD_EXECUTABLE(main
		main.c 	
		zmalloc.c 
		zlist.c
		zstack.c
		ztree.c 
		zqueue.c
		zstack02.c
                zhash.c
                #zmultipletree.c
		)
ADD_EXECUTABLE(socks5 socks5.c)
TARGET_LINK_LIBRARIES(socks5 pthread)

ADD_EXECUTABLE(ET ET.c)
ADD_EXECUTABLE(get get.c)
ADD_EXECUTABLE(parse parse.c)

ADD_EXECUTABLE(fork_test fork_test.c)
ADD_EXECUTABLE(sig_test sig_test.c)
ADD_EXECUTABLE(setjmp_test setjmp_test.c)
ADD_EXECUTABLE(daemon_test daemon_test.c)

ADD_EXECUTABLE(process_race process_race.c)
ADD_EXECUTABLE(sem_test sem_test.c)
ADD_EXECUTABLE(process_meminfo process_meminfo.c)
ADD_EXECUTABLE(mini_web_server mini_web_server.c)
TARGET_LINK_LIBRARIES(mini_web_server pthread)

ADD_EXECUTABLE(select_test select_test.c)

ADD_EXECUTABLE(productor_consumer productor_consumer.c)
TARGET_LINK_LIBRARIES(productor_consumer pthread)

ADD_EXECUTABLE(share_memory01 share_memory01.c)
ADD_EXECUTABLE(share_memory02 share_memory02.c)
TARGET_LINK_LIBRARIES(share_memory01 pthread)
TARGET_LINK_LIBRARIES(share_memory02 pthread)

#INCLUDE_DIRECTORIES(/usr/include/mysql/)
#LINK_DIRECTORIES(/usr/lib/mysql/)
#ADD_EXECUTABLE(test_mysql test_mysql.c)
#TARGET_LINK_LIBRARIES(test_mysql pthread)
ADD_EXECUTABLE(task_mgr task_mgr.c)
TARGET_LINK_LIBRARIES(task_mgr pthread)

#TARGET_LINK_LIBRARIES(main boost_thread)
#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")
#SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -Wall -g")
