#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cache.h"
#include "itoa.c"

int main(void){
  char *buffer;
  unsigned i;
  unsigned nums[] = {0b10010101, 0b01010010, 0b11010010, 0b00000001};
  printf("----- address_to_tag -----\n");
  for(i=0;i<4;i++){
    buffer = itoa(nums[i],2);
    printf("address: %s\n", buffer);
    buffer = itoa(address_to_tag(nums[i]), 2);
    printf("tag: %s\n", buffer);
  }


  printf("----- address_to_index -----\n");
  for(i=0;i<4;i++){
    buffer = itoa(nums[i],2);
    printf("address: %s\n", buffer);
    buffer = itoa(address_to_index(nums[i]), 2);
    printf("index: %s\n", buffer);
  }

  return 0;
}
