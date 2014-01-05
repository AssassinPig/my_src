#ifndef _ZCONDITION_H__ 
#define _ZCONDITION_H__

#include <pthread.h>

class ZCondition
{
    public:
        ZCondition()
        {
            m_cond = PTHREAD_COND_INITIALIZER; 
            m_mutex = PTREAD_MUTEX_INITIALIZER;
        }
        
        ~ZCondition()
        {
        
        }

        void Wait()
        {
        
        }

        void Signal()
        {
        
        }

    private:
        pthread_cond_t m_cond;
        pthread_mutex_t m_mutex;
};

#endif //_ZCONDITION_H__
