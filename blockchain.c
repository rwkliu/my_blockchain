#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "blockchain.h"

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
  blockchain->addBlock = addBlockToNode;
  blockchain->removeBlock = removeBlockFromNode;
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
  } else {
    printf("Error message here: nid doesn't exist\n");
  }

  update_num_nodes(blockchain, RM);
}

//Add block to node with specified nid
void addBlockToNode(BlockchainPtr blockchain, Node **noderef, char *bid, int nid) {
  Node **tracer = noderef;
  while (*tracer) {
    if ((*tracer)->nid == nid) {
      addBlock(&(*tracer)->bid_head, bid);
      update_numblocks(&(*tracer), ADD);
    }
    tracer = &(*tracer)->next_node;
  }
  update_sync_state(blockchain, noderef);
  printf("OK\n");
}

//Remove blocks with specified nid from all nodes with that block
void removeBlockFromNode(BlockchainPtr blockchain, Node **noderef, char *bid) {
  Node **tracer = noderef;

  while (*tracer) {
    removeBlock(&(*tracer)->bid_head, bid);
    if (removeBlock(&(*tracer)->bid_head, bid)) {
      update_numblocks(&(*tracer), RM);
    }
    tracer = &(*tracer)->next_node;
  }
  update_sync_state(blockchain, noderef);
  printf("OK\n");
}

void list_bids(Block **block_head) {
  Block **blockref = block_head;
  while((*blockref)) {
    printf("%s ", (*blockref)->bid);
    blockref = &(*blockref)->next_block;
  }
}

//Print all nids and their bids
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

//Update the num_blocks variable
void update_numblocks(Node **Noderef, commands command) {
  switch (command) {
    case ADD:
      (*Noderef)->num_blocks += 1;
      break;
    case RM:
      (*Noderef)->num_blocks -= 1;
      break;
  }
}

//Free all allocated memory in blockchain (blocks, nodes)
void free_blockchain(BlockchainPtr blockchain) {
  NodePtr current_node = blockchain->blockchain_head;
  NodePtr free_node = current_node;
  BlockPtr current_block = current_node->bid_head;
  BlockPtr free_block = current_block;

  while(current_node) {
    if (current_block != NULL) {
      remove_all_blocks(&current_block);
    }
    current_node = current_node->next_node;
    if (current_node != NULL) {
      current_block = current_node->bid_head;
    }
    nodeDestructor(free_node);
    free_node = current_node;
  }
}
