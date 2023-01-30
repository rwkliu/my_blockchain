#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "blockchain.h"
#include "status.h"

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(BlockchainPtr blockchain) {
  blockchainInitialize(blockchain);
  return blockchain;
}

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain) {
  blockchain->num_nodes = 0;
  blockchain->sync_state = SYNCED;
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
  printf(COMMAND_SUCCESS);
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
    remove_all_blocks(&(to_remove)->bid_head);
    nodeDestructor(to_remove);
  } else {
    printf(NODE_NOT_FOUND);
  }

  update_num_nodes(blockchain, RM);
  printf(COMMAND_SUCCESS);
}

//Add block to node with specified nid
void addBlockToNode(BlockchainPtr blockchain, Node **noderef, char *bid, int nid) {
  Node **tracer = noderef;

  while ((*tracer) && (*tracer)->nid != nid) {
    tracer = &(*tracer)->next_node;
  }
  if (*tracer == NULL) {
    printf(NODE_NOT_FOUND);
  } else if ((*tracer)->nid == nid) {
    addBlock(&(*tracer)->bid_head, bid);
    update_numblocks(&(*tracer), ADD);
    update_sync_state(blockchain, noderef);
    printf(COMMAND_SUCCESS);
  }
}

//Remove blocks with specified nid
void removeBlockFromNode(BlockchainPtr blockchain, Node **noderef, char *bid, int nid) {
  Node **tracer = noderef;

  while ((*tracer) && (*tracer)->nid != nid) {
    tracer = &(*tracer)->next_node;
  }
  if (*tracer == NULL) {
    printf(NODE_NOT_FOUND);
  } else if (removeBlock(&(*tracer)->bid_head, bid) == 1) {
    update_numblocks(&(*tracer), RM);
    update_sync_state(blockchain, noderef);
    printf(COMMAND_SUCCESS);
  } else {
    printf(BLOCK_NOT_FOUND);
  }
}

void list_bids(Block **block_head) {
  Block **blockref = block_head;
  while((*blockref)) {
    printf(" %s", (*blockref)->bid);
    blockref = &(*blockref)->next_block;
  }
}

//Print all nids and their bids
void lsBidsNids(Node **node_head, int lflag) {
  Node **noderef = node_head;
  while ((*noderef)) {
    printf("%d", (*noderef)->nid);
    if (lflag == PRINT_BID) {
      printf(":");
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
  if (command == ADD) {
    blockchain->num_nodes += 1;
  } else if (command == RM) {
    blockchain->num_nodes -= 1;
  }
}

//Update the num_blocks variable
void update_numblocks(Node **Noderef, commands command) {
  if (command == ADD) {
    (*Noderef)->num_blocks += 1;
  } else if (command == RM) {
    (*Noderef)->num_blocks -= 1;
  }
}

//Free all allocated memory in blockchain (blocks, nodes)
void free_blockchain(BlockchainPtr blockchain) {
  if (blockchain->blockchain_head == NULL) {
    return;
  }
  NodePtr current_node = blockchain->blockchain_head;
  NodePtr free_node = current_node;

  BlockPtr current_block = current_node->bid_head;

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
