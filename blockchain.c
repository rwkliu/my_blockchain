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

//Add node to blockchain
void add_node(BlockchainPtr blockchain, Node **noderef, int nid) {
  Node **tracer = noderef;
  NodePtr new_node = nodeConstructor();
  new_node->nid = nid;

  while(*tracer) {
    tracer = &(*tracer)->next_node;
  }

  new_node->next_node = *tracer;
  *tracer = new_node;

  update_num_nodes(blockchain, ADD);
}

void update_num_nodes(BlockchainPtr blockchain, commands command) {
  switch (command) {
    case ADD:
      blockchain->num_nodes += 1;
      break;
    case RM:
      blockchain->num_nodes -= 1;
      break;
  }
}

void remove_node(BlockchainPtr blockchain, Node **noderef, int nid) {
  Node **tracer = noderef; 
  while ((*tracer) && (*tracer)->nid != nid) {
    tracer = &((*tracer)->next_node);
  }

  if (*tracer != NULL) {
    NodePtr to_remove = *tracer;
    *tracer = (*tracer)->next_node;
    nodeDestructor(to_remove);
  }

  update_num_nodes(blockchain, RM);
}

