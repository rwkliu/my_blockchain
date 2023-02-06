#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
    if ((*tracer)->nid == nid) {
      printf(NODE_EXISTS);
      return;
    }
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

void list_bids(Block **block_head, int num_blocks) {
  Block **blockref = block_head;
  while((*blockref)) {
    printf(" %s", (*blockref)->bid);
    if (num_blocks > 1 && (*blockref)->next_block != NULL) {
      printf(",");
    }
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
      list_bids((&(*noderef)->bid_head), (*noderef)->num_blocks);
    }
    printf("\n");
    noderef = &(*noderef)->next_node;
  }
}

int block_found(Block **blockref, char *bid) {
  while (*blockref) {
    if (strncmp((*blockref)->bid, bid, strlen(bid)) == 0) {
      return 1;
    }
    blockref = &(*blockref)->next_block;
  }
  return 0;
}

//Check all nodes for the same blocks as the first node (genesis blocks)
int is_synchronized(Node **noderef) {
  Block **genesis_blocks = &(*noderef)->bid_head;
  Node **tracer = &(*noderef)->next_node; 
  
  while(*tracer) {
    if ((*tracer)->num_blocks != (*noderef)->num_blocks) {
      return 0;
    }
    BlockPtr current_block = (*tracer)->bid_head;
    while (current_block) {
      if (!block_found(genesis_blocks, current_block->bid)) {
        return 0;
      }
      current_block = current_block->next_block;
    }
    genesis_blocks = &(*noderef)->bid_head;
    tracer = &(*tracer)->next_node;
  }
  return 1;
}

void add_missing_blocks(BlockchainPtr blockchain, Block **block_tracer, Node **node_to_sync) {
  while (*block_tracer) {
    if (!block_found(&(*node_to_sync)->bid_head, (*block_tracer)->bid)) {
      addBlock(&(*node_to_sync)->bid_head, (*block_tracer)->bid);
      update_numblocks(node_to_sync, ADD);
      update_sync_state(blockchain, &(blockchain->blockchain_head));
    }
    block_tracer = &(*block_tracer)->next_block;
  }
}

void synchronize_nodes(BlockchainPtr blockchain, Node **noderef) {
  if (blockchain->sync_state == NOT_SYNCED) {
    Node **node_to_sync = noderef;
    Node **node_to_check = &(*noderef)->next_node;
    Block **block_tracer = &(*node_to_check)->bid_head;

    //Synchronize first node
    while (*node_to_check) {
      add_missing_blocks(blockchain, block_tracer, node_to_sync);
      node_to_check = &(*node_to_check)->next_node;
      block_tracer = &(*node_to_check)->bid_head;
    }
    //Synchronize subsequent nodes. Add missing blocks to node if it has blocks.
    //Otherwise, add all the blocks from the previous node
    node_to_sync = &(*noderef)->next_node;
    node_to_check = noderef;
    block_tracer = &(*node_to_check)->bid_head;

    while (*node_to_check && *node_to_sync) {
      add_missing_blocks(blockchain, block_tracer, node_to_sync);
      node_to_check = &(*node_to_check)->next_node;
      block_tracer = &(*node_to_check)->bid_head;
      node_to_sync = &(*node_to_sync)->next_node;
    }
  }
  printf("OK\n");
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

void save_blockchain(Node **noderef) {
  int file_descriptor;
  Block **block_tracer = &(*noderef)->bid_head;
  file_descriptor = open("blockchain_backup.txt", O_RDWR | O_CREAT, 
                        ((S_IWUSR | S_IRUSR) | (S_IRGRP | S_IWGRP) | S_IROTH));
  
  while ((*noderef)) {
    char *nid_string = signed_decimal((*noderef)->nid);
    write(file_descriptor, nid_string, strlen(nid_string));
    write(file_descriptor, ": ", 2);
    while (*block_tracer) {
      write(file_descriptor, (*block_tracer)->bid, strlen((*block_tracer)->bid));
      if ((*noderef)->num_blocks > 1 && (*block_tracer)->next_block != NULL) {
        write(file_descriptor, ", ", 2);
      }
      block_tracer = &(*block_tracer)->next_block;
    }
    write(file_descriptor, "\n", 1);
    free(nid_string);
    noderef = &(*noderef)->next_node;
  }
  close(file_descriptor);
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
