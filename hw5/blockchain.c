/*********************************************************************
Homework 5
CS 110: Computer Architecture, Spring 2021
ShanghaiTech University

* Last Modified: 03/28/2021
*********************************************************************/

#include "blockchain.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/sysinfo.h>
//#include <stdio.h>
//#include <unistd.h>

#define MAX_THR 56

int step;
size_t diff_q;
size_t diff_m;


int loop_signal = 0;
//pthread_cond_t cond;
pthread_mutex_t mutex;
//pthread_mutex_t mutex2;

unsigned char one_diff[HASH_BLOCK_SIZE];



void (*func_copy) (unsigned char * a,size_t b,unsigned char * c);
blk_t node_copy;
uint64_t final_nonce;


void blockchain_node_init(blk_t *node, uint32_t index, uint32_t timestamp,
                          unsigned char prev_hash[32], unsigned char *data,
                          size_t data_size) {
    if (!node || !data || !prev_hash)
    return;

    node->header.index = index;
    node->header.timestamp = timestamp;
    node->header.nonce = -1;

    memset(node->header.data, 0, sizeof(unsigned char) * 256);
    memcpy(node->header.prev_hash, prev_hash, HASH_BLOCK_SIZE);
    memcpy(node->header.data, data,
         sizeof(unsigned char) * ((data_size < 256) ? data_size : 256));
}

void blockchain_node_hash(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE],
                          hash_func func) {
  if (node)
    func((unsigned char *)node, sizeof(blkh_t), (unsigned char *)hash_buf);
}

BOOL blockchain_node_verify(blk_t *node, blk_t *prev_node, hash_func func) {
    unsigned char hash_buf[HASH_BLOCK_SIZE];

    if (!node || !prev_node)
    return False;

    blockchain_node_hash(node, hash_buf, func);
    if (memcmp(node->hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE))
    return False;

    blockchain_node_hash(prev_node, hash_buf, func);
    if (memcmp(node->header.prev_hash, hash_buf,
         sizeof(unsigned char) * HASH_BLOCK_SIZE))
    return False;

    return True;
}



void* thread_mine(void* param_nonce)
{
    unsigned char hash_buf[HASH_BLOCK_SIZE];
    blk_t my_node_copy = node_copy;
    my_node_copy.header.nonce = *(uint64_t*) param_nonce;

    while ((my_node_copy.header.nonce <= UINT64_MAX) && !loop_signal) {

        blockchain_node_hash(&my_node_copy, hash_buf, (*func_copy));

        if ((!memcmp(hash_buf, one_diff, sizeof(unsigned char) * diff_q)) &&
            memcmp(&hash_buf[diff_q], &one_diff[diff_q],
                   sizeof(unsigned char) * (HASH_BLOCK_SIZE - diff_q)) <= 0)
        {

            pthread_mutex_lock(&mutex);
//            pthread_cond_signal(&cond);

            loop_signal = 1;
            final_nonce = my_node_copy.header.nonce;

            pthread_mutex_unlock(&mutex);

            break;
        }

        (my_node_copy.header.nonce)+=step;
    }


    pthread_exit(NULL);
}


/* The implementation of mining */
void blockchain_node_mine(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE],
                          size_t diff, hash_func func)
{
    /* Set the standard value */
    diff_q = diff / 8;
    diff_m = diff % 8;
    memset(one_diff, 0xFF, sizeof(unsigned char) * HASH_BLOCK_SIZE);
    memset(one_diff, 0, sizeof(unsigned char) * diff_q);
    one_diff[diff_q] = ((uint8_t)0xFF) >> diff_m;
    func_copy = func;
    node_copy = *node;
    loop_signal = 0;
//    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);


    /* Set how many threads we want to use */
    step = get_nprocs()*2;
    if (step > MAX_THR) step = MAX_THR;
//    step = 4;
//    if (diff >10 && diff <= 16) step = 4;
//    if (diff >16 && diff <= 18) step = 16;
//    printf("#core: %d\n", step);

    /* allocate space of threads and nonces */
    pthread_t list[MAX_THR];
    uint64_t nonce[MAX_THR];


    /* create and run the threads */
//    pthread_mutex_lock(&mutex);

    for (int i = 0; i < step; i++)
    {
        nonce[i] = i;
        pthread_create((list + i), NULL, thread_mine, (nonce + i));
    }


    /* wait for the signal that find the right nonce */
//    pthread_cond_wait(&cond, &mutex);
//
//    loop_signal = 1;
//
//    pthread_mutex_unlock(&mutex);


    /* Identify the results, join the threads, save the nouce and hash_buf */
    for (int i = 0; i < step; i++) pthread_join(list[i], NULL);

    node->header.nonce = final_nonce;
    blockchain_node_hash(node, hash_buf, func);
    memcpy(node->hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);


    /* clear the allocate memory, the cond and mutex */
//    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
}
