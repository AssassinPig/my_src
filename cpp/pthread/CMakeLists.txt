PROJECT(pthread)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4)

#INCLUDE_DIRECTORIES(/usr/local/include/)
#LINK_DIRECTORIES(/usr/local/lib/)

#SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_C_FLAGS_DEBUG "-O3 -Wall -g -std=c99")


ADD_EXECUTABLE(test_pool 
                test_pool.cpp 
                thread_pool.cpp)
TARGET_LINK_LIBRARIES(test_pool pthread)

ADD_EXECUTABLE(zcondition 
            test_condition.cpp
            zcondition.hpp)

TARGET_LINK_LIBRARIES(zcondition pthread)

