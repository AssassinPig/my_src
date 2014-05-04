#include <stdio.h>
#include <stdlib.h>
#include "zhash.h"

zhash_t* create_hash(int bucket, 
        int (*hash_key)(const void* key), 
        int (*compare)(const void* key1, const void* key2),
        void (*destroy)(const void* data))
{
    zhash_t* hash = (zhash_t*)malloc(sizeof(zhash_t));
    if(hash) {
        hash->list = (zlist_t**)malloc(bucket*sizeof(zlist_t*)); 
        for(int i=0; i<bucket; ++i) {
            hash->list[i] = create_list(); 
        }    

        hash->hash_key = hash_key;
        hash->compare = compare;
        hash->destroy = destroy;
    }

    return hash;
}


int hash_insert(zhash_t* hash, const void* data)
{
    int key = hash->hash_key(data); 
    zlist_t* list = hash->list[key]; 
    if(list) {
        addNode(list, data);
    }

    return 0;
}

int hash_find(zhash_t* hash, const void* data)
{
    int key = hash->hash_key(data); 
    zlist_t* list = hash->list[key]; 
    if(list) {
        return list_find_node(list, data);
    }

    return -1;
}

void* hash_remove(zhash_t* hash, const void* data)
{
    if(!hash_find(hash, data)) {
        return NULL; 
    }

    int key = hash->hash_key(data); 
    zlist_t* list = hash->list[key]; 
    if(list) {
        return DelNode(list, data);
    }

    return NULL;
}

void hash_clear(zhash_t* hash)
{
    for(int i=0; i<hash->bucket; ++i) {
        zlist_t* list = hash->list[i]; 
        ClearList(list); 
    }    
}

int hash_size(zhash_t* hash)
{
    return hash->count;
}

