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

void list_nids(Node **noderef) {
  while ((*noderef)) {
    printf("%d", (*noderef)->getNid(*noderef));
    noderef = &(*noderef)->next_node;
  }
}

void list_bids(Block **blockref) {
  while((*blockref)) {
    printf("%s ", (*blockref)->getBid(*blockref));
    blockref = &(*blockref)->next_block;
  }
}

void ls_blockchain(Node **noderef, int lflag) {
  while ((*noderef)) {
    printf("%d", (*noderef)->getNid((*noderef)));
    if (lflag == 1) {
      printf(": ");
      list_bids((&(*noderef)->bid_head));
    }
    printf("\n");
    *noderef = (*noderef)->next_node;
  }
}

//Free all allocated memory (blocks, nodes, blockchain)
void free_blockchain(BlockchainPtr blockchain) {
  NodePtr current_node = blockchain->blockchain_head;
  NodePtr free_node = current_node;
  // printf("current_node nid: %d\n", blockchain->blockchain_head->nid);
  BlockPtr current_block = current_node->bid_head;
  BlockPtr free_block = current_block;
  // printf("current block bid: %s\n", (*current_block)->getBid(*current_block));

  printf("Before while loops\n");
  while(current_node) {
    printf("node while entered\n");
    if (current_block != NULL) {
      while (current_block) {
        current_block = current_block->next_block;
        printf("block while entered\n");
        blockDestructor(free_block);
        printf("block3 while entered\n");
        free_block = current_block;
      }
    }
    printf("After if statement\n");
    current_node = current_node->next_node;
    printf("After setting current_node\n");
    if (current_node != NULL) {
      current_block = current_node->bid_head;
    }
    printf("After setting current_block\n");
    nodeDestructor(free_node);
    printf("After freeing free_node\n");
    free_node = current_node;
    printf("After setting free_node\n");
  }
  printf("After while loops\n");
  blockchainDestructor(blockchain);
}

void prompt(int num, char sync) {
  print_prompt(num, sync);
  printf("\n");
}

int main() {
  BlockchainPtr blockchain = blockchainConstructor();

  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  
  //Add nodes
  int nid = 12;
  printf("first add node\n");
  add_node(blockchain, nid);
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  nid = 13;
  printf("second add node\n");
  add_node(blockchain, nid);
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  
  nid = 15;
  printf("third add node\n");
  add_node(blockchain, nid);
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  //Print nid of all nodes in blockchain
  // printf("ls\n");
  // list_nids(&(blockchain->blockchain_head));

  //Remove a node and print the remaining nodes
  // nid = 13;
  // printf("Remove node %d\n", nid);
  // remove_nodes(blockchain, nid);
  // list_nids(&(blockchain->blockchain_head));
  // prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  char *bid = "223";
  NodePtr desired_node = findNode(blockchain->blockchain_head, 15);
  printf("desired node nid: %d\n", desired_node->getNid(desired_node));
  printf("add bid %s to node\n", bid);
  //Segfaults
  // desired_node->bid_head->addBlock(&(desired_node->bid_head), bid);
  // printf("Desired node's bid: %s\n", desired_node->bid_head->getBid(desired_node->bid_head));
  
  // blockchain->blockchain_head->bid_head->addBlock(&(desired_node->bid_head), bid);
  
  //Works
  addBlock(&(desired_node->bid_head), bid);
  update_numblocks(&(desired_node));
  // addBlock(&(desired_node->bid_head), "world");
  // update_numblocks(&(desired_node));
  // printf("number of blocks in node: %d\n", desired_node->getNumBlocks(desired_node));

  //Print nids and bids in blockchain
  // printf("Print all nids and bids\n");
  // ls_blockchain(&(blockchain->blockchain_head), 1);
  // printf("ls blocks again\n");
  // ls_blockchain(&(blockchain->blockchain_head), 1);

  printf("Free allocated memory\n");
  free_blockchain(blockchain);
  
  return 0;
}
