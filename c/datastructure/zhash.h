#ifndef _ZHASH_H__ 
#define _ZHASH_H__

#include "zlist.h"

struct zhash {
    int bucket;
    
    int (*hash_key)(const void* key);
    int (*compare)(const void* key1, const void* key2);
    void (*destroy)(const void* data);

    int count;
    zlist_t** list;
};

typedef struct zhash zhash_t; 

zhash_t* create_hash(int bucket, 
        int (*hash_key)(const void* key), 
        int (*compare)(const void* key1, const void* key2),
        void (*destroy)(const void* data));

int hash_insert(zhash_t* hash, const void* data);
int hash_find(zhash_t* hash, const void* data);
void* hash_remove(zhash_t* hash, const void* data);
void hash_clear(zhash_t* hash);
int hash_size(zhash_t* hash);

#endif //_ZHASH_H__
