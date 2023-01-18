#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "blockchain.h"

void setSyncState(BlockchainPtr this, sync_state state) {
  switch(state) {
    case SYNCED: {
      this->sync_state = 's';
      break;
    }
    case NOT_SYNCED: {
      this->sync_state = '-';  
      break;
    }
    default:
      printf("Incorrect sync_state input parameter\n");
  }
}

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(BlockchainPtr blockchain) {
  blockchainInitialize(blockchain);
  return blockchain;
}

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain) {
  blockchain->num_nodes = 0;
  blockchain->sync_state = 's';
  blockchain->blockchain_head = NULL;
  return 0;
}
