#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cache.h"

// initialize the cache by allocating space for all of the cache
// blocks and initializing them to be invalid and with 0 last access
// times.
void
init_cache(cache_t *cache) {
  // initialize the cache blocks to invalid
  for (int i = 0 ; i < NUM_SETS ; i ++) {
	 for (int j = 0 ; j < 2 ; j ++) {
		cache->sets[i].blocks[j].valid = false;
		cache->sets[i].blocks[j].dirty = false;
	 }
	 cache->sets[i].lru = 0;
  }

  cache->accesses = 0;
  cache->hits = 0;
  cache->writebacks = 0;
}

// given an address, extract the tag field 
unsigned 
address_to_tag(unsigned address) {
  unsigned index_bits = log2(NUM_SETS);
  unsigned offset_bits = log2(BLOCK_SIZE); 
  return address >> (index_bits + offset_bits);
}

// given an address, extract the index field 
unsigned 
address_to_index(unsigned address) {
  unsigned index_bits = log2(NUM_SETS);
  unsigned offset_bits = log2(BLOCK_SIZE);
  return (address >> offset_bits) & ((int)pow(2,index_bits)-1);
}

// Given an address, look up in cache "cache" to see if that
// address hits.  If it does update the LRU.
// Include necessary updates to the access, hit, writeback counters
bool
find_block_and_update_lru(cache_t *cache, unsigned address, bool write) {
  unsigned tag = address_to_tag(address);
  unsigned index = address_to_index(address);
  cache->accesses++;
  
  // FIXME
  if(cache->sets[index].blocks[0].tag == tag){
    cache->hits++;
    cache->sets[index].lru = 1;
    return true;
  }
  if(cache->sets[index].blocks[1].tag == tag){
    cache->hits++;
    cache->sets[index].lru = 0;
    return true;
  }

  return false;  // FIXME: return true if we found the block and false if not
}

// This function should find the LRU block of the correct set and replace it 
// with one that contains "address," updating the LRU appropriately.
// Include necessary updates to the access, hit, writeback counters
void
fill_cache_with_block(cache_t *cache, unsigned address, bool write) {
  unsigned tag = address_to_tag(address);
  unsigned index = address_to_index(address);
  unsigned lru = cache->sets[index].lru;
  cache->sets[index].blocks[lru].tag = tag;
  cache->sets[index].blocks[lru].valid = 1;
  cache->sets[index].blocks[lru].dirty = write;
  cache->sets[index].lru = !lru;
  cache->accesses++;
  if(write){cache->writebacks++;}
  }
