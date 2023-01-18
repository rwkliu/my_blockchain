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

void setNumNodes(BlockchainPtr this, int num) {
  this->num_nodes = num;
}

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

//Free allocated memory for Blockchain struct
int blockchainDestructor(BlockchainPtr blockchain) {
  free(blockchain);
  return 0;
}

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain) {
  blockchain->num_nodes = 0;
  blockchain->sync_state = 's';
  blockchain->blockchain_head = NULL;
  blockchain->latest_node = blockchain->blockchain_head;
  blockchain->getNumNodes = getNumNodes;
  blockchain->getSyncState = getSyncState;
  blockchain->setNumNodes = setNumNodes;
  blockchain->setSyncState = setSyncState;
  return 0;
}

//main function to test above functions
//int main() {
//  BlockchainPtr blockchain = blockchainConstructor();
//  NodePtr node = nodeConstructor();
//
//  if(blockchain != NULL) {
//    printf("Blockchain successfully created\n");
//  } else {
//    printf("Blockchain creation failed\n");
//  }
//  if(node != NULL) {
//    printf("Node successfully created\n");
//  } else {
//    printf("Node creation failed\n");
//  }
//
//  blockchain->setNumNodes(blockchain, 5);
//  blockchain->setSyncState(blockchain, NOT_SYNCED);
//  node->setNid(node, 10);
//  node->setBid(node, "21");
//  printf("blockchain num nodes: %d\n", blockchain->getNumNodes(blockchain));
//  printf("blockchain sync state: %c\n", blockchain->getSyncState(blockchain));
//  printf("node nid: %d\n", node->getNid(node));
//  printf("node bid: %s\n", node->getBid(node));
//  
//  blockchainDestructor(blockchain);
//  nodeDestructor(node);
//  return 0;
//}
