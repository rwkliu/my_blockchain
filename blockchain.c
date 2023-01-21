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
  blockchain->addNode = addNode;
  blockchain->removeNode = removeNode;
  blockchain->ls = lsBidsNids;
  return 0;
}

//Add node to blockchain
void addNode(BlockchainPtr blockchain, Node **noderef, int nid) {
  Node **tracer = noderef;
  NodePtr new_node = nodeConstructor();
  new_node->nid = nid;

  while(*tracer) {
    tracer = &(*tracer)->next_node;
  }

  new_node->next_node = *tracer;
  *tracer = new_node;

  update_num_nodes(blockchain, ADD);
  update_sync_state(blockchain, noderef);
}

//Update the num_nodes variable
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

//Remove node from blockchain
void removeNode(BlockchainPtr blockchain, Node **noderef, int nid) {
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

//Check all nodes for the same blocks as the first node (genesis blocks)
int is_synchronized(Node **noderef) {
  Block *genesis_blocks = (*noderef)->bid_head;
  Node **tracer = &(*noderef)->next_node; 
  
  while(*tracer) {
    if ((*tracer)->num_blocks != (*noderef)->num_blocks) {
      return 0;
    }
    BlockPtr current_block = (*tracer)->bid_head;
    while (current_block) {
      if (strcmp(current_block->bid, (*genesis_blocks).bid) != 0) {
        return 0;
      }
      current_block = (*tracer)->bid_head->next_block;
      genesis_blocks = (*noderef)->bid_head->next_block;
    }
    tracer = &(*tracer)->next_node;
  }
  return 1;
}

//Check if all nodes contain the same blocks and update the sync state
void update_sync_state(BlockchainPtr blockchain, Node **noderef) {
  if (is_synchronized(noderef)) {
    blockchain->sync_state = SYNCED;
  } else {
    blockchain->sync_state = NOT_SYNCED;
  }
}

void list_bids(Block **block_head) {
  Block **blockref = block_head;
  while((*blockref)) {
    printf("%s ", (*blockref)->bid);
    blockref = &(*blockref)->next_block;
  }
}

void lsBidsNids(Node **node_head, int lflag) {
  Node **noderef = node_head;
  while ((*noderef)) {
    printf("%d", (*noderef)->nid);
    if (lflag == PRINT_BID) {
      printf(": ");
      list_bids((&(*noderef)->bid_head));
    }
    printf("\n");
    noderef = &(*noderef)->next_node;
  }
}

