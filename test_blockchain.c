#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"

void add_node(BlockchainPtr blockchain, int nid) {
  NodePtr new_node = nodeConstructor();
  NodePtr *headref = &(blockchain->blockchain_head);
  new_node->setNid(new_node, nid);

  while ((*headref)) {
    headref = &((*headref)->next_node);
  }

  new_node->next_node = *headref;
  *headref = new_node;
  
  blockchain->setNumNodes(blockchain, blockchain->getNumNodes(blockchain) + 1);
  blockchain->latest_node = *headref;
}

void remove_nodes(BlockchainPtr blockchain, int nid) {
  NodePtr *noderef = &(blockchain->blockchain_head);
  
  while ((*noderef) && (*noderef)->getNid(*noderef) != nid) {
    noderef = &((*noderef)->next_node);
  }

  if (*noderef != NULL) {
    NodePtr old = *noderef;
    *noderef = (*noderef)->next_node;
    nodeDestructor(old);
  }

  blockchain->setNumNodes(blockchain, blockchain->getNumNodes(blockchain) - 1);
}

void update_numblocks(Node **noderef) {
  (*noderef)->setNumBlocks((*noderef), (*noderef)->getNumBlocks(*noderef) + 1);
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
    printf("%s ", (*blockref)->getBid(*blockref));
    blockref = &(*blockref)->next_block;
  }
}

void ls_bids_nids(Node **node_head, int lflag) {
  Node **noderef = node_head;
  while ((*noderef)) {
    printf("%d", (*noderef)->getNid((*noderef)));
    if (lflag == 1) {
      printf(": ");
      list_bids((&(*noderef)->bid_head));
    }
    printf("\n");
    noderef = &(*noderef)->next_node;
  }
}

//Free all allocated memory (blocks, nodes, blockchain)
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
  blockchainDestructor(blockchain);
}

void prompt(int num, char sync) {
  print_prompt(num, sync);
  printf("\n");
}

int main() {
  Blockchain blockchain;
  blockchainConstructor(&blockchain);

  prompt(blockchain.getNumNodes(&blockchain), blockchain.getSyncState(&blockchain));
  
  // //Add nodes
  int nid = 12;
  printf("first add node\n");
  add_node(&blockchain, nid);
  prompt(blockchain.getNumNodes(&blockchain), blockchain.getSyncState(&blockchain));

  nid = 13;
  printf("second add node\n");
  add_node(&blockchain, nid);
  prompt(blockchain.getNumNodes(&blockchain), blockchain.getSyncState(&blockchain));
  
  nid = 15;
  printf("third add node\n");
  add_node(&blockchain, nid);

  // //Print nid of all nodes in blockchain
  printf("ls\n");
  ls_bids_nids(&(blockchain.blockchain_head), 0);

  // //Remove a node and print the remaining nodes
  // nid = 13;
  // printf("Remove node %d\n", nid);
  // remove_nodes(blockchain, nid);
  // ls_bids_nids(&(blockchain->blockchain_head), 0);
  // prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  // char *bid = "223";
  // printf("add bid %s to node\n", bid);
  
  // //Works
  // addBlock(&blockchain->blockchain_head->bid_head, bid);

  // //Print nids and bids in blockchain
  // printf("Print all nids and bids\n");
  // ls_bids_nids(&(blockchain->blockchain_head), 1);
  // printf("ls blocks again\n");
  // ls_bids_nids(&(blockchain->blockchain_head), 1);

  // printf("Free allocated memory\n");
  // free_blockchain(blockchain);
  
  return 0;
}
