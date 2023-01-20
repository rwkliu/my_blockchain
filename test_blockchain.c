#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"
#include "arguments_blockchain.h"

#define PRINT_BID 1
#define NO_BID 0

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

void remove_nodes(BlockchainPtr blockchain, Node **noderef, int nid) {
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

void update_numblocks(Node **Noderef) {
  (*Noderef)->num_blocks += 1;
}

void add_block_to_node(Node **noderef, char *bid, int nid) {
  Node **tracer = noderef;
  while(*tracer) {
    printf("while loop entered\n");
    if ((*tracer)->nid == nid) {
      addBlock(&(*tracer)->bid_head, bid);
      update_numblocks(&(*tracer));
    }
    tracer = &(*tracer)->next_node;
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
  }

  //print the genesis block bids
  if (genesis_blocks != NULL) {
    while(genesis_blocks) {
      printf("bid in the genesis block: %s\n", genesis_blocks->bid);
      genesis_blocks = genesis_blocks->next_block;
    }
  }
  return 0;
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

void ls_bids_nids(Node **node_head, int lflag) {
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

//Free all allocated memory in blockchain (blocks, nodes)
void free_blockchain(BlockchainPtr blockchain) {
  NodePtr current_node = blockchain->blockchain_head;
  NodePtr free_node = current_node;
  BlockPtr current_block = current_node->bid_head;
  BlockPtr free_block = current_block;

  while(current_node) {
    if (current_block != NULL) {
      while (current_block) {
        current_block = current_block->next_block;
        blockDestructor(free_block);
        free_block = current_block;
      }
    }
    current_node = current_node->next_node;
    if (current_node != NULL) {
      current_block = current_node->bid_head;
    }
    nodeDestructor(free_node);
    free_node = current_node;
  }
}

void prompt(int num, char sync) {
  print_prompt(num, sync);
  printf("\n");
}

int main() {
  Blockchain blockchain;
  blockchainConstructor(&blockchain);

  prompt(blockchain.num_nodes, blockchain.sync_state);
  
  //Add nodes
  int nid = 12;
  printf("first add node\n");
  add_node(&(blockchain), &(blockchain.blockchain_head), nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  nid = 13;
  printf("second add node\n");
  add_node(&(blockchain), &(blockchain.blockchain_head), nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);
  
  nid = 15;
  printf("third add node\n");
  add_node(&(blockchain), &(blockchain.blockchain_head), nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Print nid of all nodes in blockchain
  printf("ls\n");
  ls_bids_nids(&(blockchain.blockchain_head), NO_BID);

  //Remove a node and print the remaining nodes
  nid = 13;
  printf("Remove node %d\n", nid);
  remove_nodes(&blockchain,&(blockchain.blockchain_head), nid);
  ls_bids_nids(&(blockchain.blockchain_head), NO_BID);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  char *bid = "223";
  printf("add bid %s to node\n", bid);
  add_block_to_node(&(blockchain.blockchain_head), bid, 12);
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  //addBlock(&(blockchain.blockchain_head->bid_head), bid);

  //Print nids and bids in blockchain
  printf("Print all nids and bids\n");
  ls_bids_nids(&(blockchain.blockchain_head), PRINT_BID);
  printf("ls blocks again\n");
  ls_bids_nids(&(blockchain.blockchain_head), PRINT_BID);

  printf("Free allocated memory\n");
  // free_blockchain(&blockchain);

  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);
  
  return 0;
}
