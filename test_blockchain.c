#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"

#define PRINT_BID 1
#define NO_BID 0

void update_num_nodes(BlockchainPtr blockchain) {
  blockchain->num_nodes += 1;
}

void add_node(BlockchainPtr blockchain, int nid) {
  NodePtr new_node = nodeConstructor();
  Node *headref = blockchain->blockchain_head;
  new_node->nid = nid;

  while (headref) {
    headref = headref->next_node;
  }

  new_node->next_node =headref;
  headref= new_node;

  update_num_nodes(blockchain);
}

void remove_nodes(BlockchainPtr blockchain, int nid) {
  Node **noderef = &(blockchain->blockchain_head);
  
  while ((*noderef) && (*noderef)->nid != nid) {
    noderef = &((*noderef)->next_node);
  }

  if (*noderef != NULL) {
    NodePtr to_remove = *noderef;
    *noderef = (*noderef)->next_node;
    nodeDestructor(to_remove);
  }

  blockchain->num_nodes -= 1;
}

void update_numblocks(Node **blockref) {
  (*blockref)->num_blocks += 1;
}

void add_block_to_node(BlockchainPtr blockchain, char *bid, int nid) {
  Node **noderef = &(blockchain->blockchain_head);
  while(*noderef) {
    printf("while loop entered\n");
    if ((*noderef)->nid == nid) {
      addBlock(&(*noderef)->bid_head, bid);
      update_numblocks(&(*noderef));
    }
    *noderef = (*noderef)->next_node;
  }
}

//Check all nodes for the same blocks as the first node
int is_synchronized(Node **noderef) {

}

//Check if all nodes contain the same blocks and update the sync state
void update_sync_state(BlockchainPtr blockchain) {

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
  add_node(&blockchain, nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  nid = 13;
  printf("second add node\n");
  // add_node(&blockchain, nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);
  
  nid = 15;
  printf("third add node\n");
  // add_node(&blockchain, nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Print nid of all nodes in blockchain
  printf("ls\n");
  ls_bids_nids(&(blockchain.blockchain_head), NO_BID);

  //Remove a node and print the remaining nodes
  // nid = 13;
  // printf("Remove node %d\n", nid);
  // remove_nodes(&blockchain, nid);
  // ls_bids_nids(&(blockchain.blockchain_head), NO_BID);
  // prompt(blockchain.num_nodes, blockchain.sync_state);

  char *bid = "223";
  printf("add bid %s to node\n", bid);
  add_block_to_node(&blockchain, bid, 12);
  // addBlock(&(blockchain.blockchain_head->bid_head), bid);

  //Print nids and bids in blockchain
  printf("Print all nids and bids\n");
  ls_bids_nids(&(blockchain.blockchain_head), PRINT_BID);
  printf("ls blocks again\n");
  ls_bids_nids(&(blockchain.blockchain_head), PRINT_BID);

  printf("Free allocated memory\n");
  // free_blockchain(&blockchain);
  
  return 0;
}
