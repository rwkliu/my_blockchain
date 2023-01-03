#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "blockchain.h"

int getNumNodes(BlockchainPtr this) {
  return this->num_nodes;
}

char getSyncState(BlockchainPtr this) {
  return this->sync_state;
}

BlockchainPtr blockchainConstructor(void) {
  BlockchainPtr blockchain = malloc(sizeof(Blockchain));
  return blockchain;
}

int blockchainDestructor(BlockchainPtr blockchain) {
  free(blockchain);
  return 0;
}

int blockchainInitialize(BlockchainPtr blockchain) {
  blockchain->num_nodes = 0;
  blockchain->sync_state = 's';
  blockchain->first_block = NULL;
  blockchain->get_num_nodes = getNumNodes;
  blockchain->get_sync_state = getSyncState;
  return 0;
}

//main function to test above functions
// int main() {
//   BlockchainPtr blockchain = blockchainConstructor();
//   blockchainInitialize(blockchain);

//   if(blockchain != NULL) {
//     printf("Blockchain successfully created\n");
//   }
//   else {
//     printf("Blockchain creation failed\n");
//   }

//   printf("blockchain num nodes: %d\n", blockchain->get_num_nodes(blockchain));
//   printf("blockchain sync state: %c\n", blockchain->get_sync_state(blockchain));
//   blockchainDestructor(blockchain);
//   return 0;
// }