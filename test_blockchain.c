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

  //print the genesis block bids
  //if (genesis_blocks != NULL) {
  //  while(genesis_blocks) {
  //    printf("bid in the genesis block: %s\n", genesis_blocks->bid);
  //    genesis_blocks = genesis_blocks->next_block;
  //  }
  //}
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

void synchronize_nodes(BlockchainPtr blockchain, Node **noderef) {
  if (blockchain->sync_state == SYNCED) {
    printf("OK\n");
  } else {
    printf("Nodes not synced: resyncing now\n");
     




    printf("OK\n");
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
  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);

  nid = 13;
  printf("second add node\n");
  add_node(&(blockchain), &(blockchain.blockchain_head), nid);
  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);
  
  nid = 15;
  printf("third add node\n");
  add_node(&(blockchain), &(blockchain.blockchain_head), nid);
  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Print nid of all nodes in blockchain
  printf("ls\n");
  ls_bids_nids(&(blockchain.blockchain_head), NO_BID);

  //Remove a node and print the remaining nodes
  nid = 13;
  printf("Remove node %d\n", nid);
  remove_node(&blockchain,&(blockchain.blockchain_head), nid);
  ls_bids_nids(&(blockchain.blockchain_head), NO_BID);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Add a block 
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  char *bid = "223";
  printf("add bid %s to node\n", bid);
  add_block_to_node(&(blockchain.blockchain_head), bid, 12);
  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);

  //Remove a block
  printf("number of blocks in nid 12 before removal: %d\n", blockchain.blockchain_head->num_blocks);
  remove_block_from_nodes(&(blockchain.blockchain_head), bid);
  printf("number of blocks in nid 12 after removal: %d\n", blockchain.blockchain_head->num_blocks);

  //Print nids and bids in blockchain
  printf("Print all nids and bids\n");
  ls_bids_nids(&(blockchain.blockchain_head), PRINT_BID);
  printf("ls blocks again\n");
  ls_bids_nids(&(blockchain.blockchain_head), PRINT_BID);

  //Syncrhonize nodes
  synchronize_nodes(&blockchain, &(blockchain.blockchain_head));
  //printf("Free allocated memory\n");
  // free_blockchain(&blockchain);

  return 0;
}
