#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "blockchain.h"

BlockchainPtr BlockchainConstructor() {
  BlockchainPtr blockchain = malloc(sizeof(Blockchain));
  return blockchain;
}

int BlockchainDestructor(BlockchainPtr blockchain) {
  free(blockchain);
  return 0;
}

//main function to test above functions
int main() {
  BlockchainPtr blockchain = BlockchainConstructor();
  if(blockchain != NULL) {
    printf("Blockchain successfully created\n");
  }
  else {
    printf("Blockchain creation failed\n");
  }
  BlockchainDestructor(blockchain);
  return 0;
}