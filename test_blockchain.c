#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "helpers.h"

void add_node(BlockchainPtr blockchain, int nid) {
  NodePtr new_node = nodeConstructor();
  NodePtr *headref;
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
}

void list_nids(Node **headref) {
  while ((*headref)) {
    printf("%d\n", (*headref)->getNid(*headref));
    headref = &(*headref)->next_node;
  }
}

void prompt(int num, char sync) {
  print_prompt(num, sync);
  printf("\n");
}

int main() {
  BlockchainPtr blockchain = blockchainConstructor();

  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  
  //Add node routine
  int nid = 12;
  printf("first add node\n");
  add_node(blockchain, nid);
  printf("added node nid: %d\n", blockchain->blockchain_head->getNid(blockchain->blockchain_head));
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  nid = 13;
  printf("second add node\n");
  add_node(blockchain, nid);
  printf("added node nid: %d\n", blockchain->blockchain_head->getNid(blockchain->latest_node));
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  
  nid = 15;
  printf("third add node\n");
  add_node(blockchain, nid);
  printf("added node nid: %d\n", blockchain->blockchain_head->getNid(blockchain->latest_node));
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  printf("ls\n");
  list_nids(&(blockchain->blockchain_head));

  nid = 13;
  printf("Remove node %d\n", nid);
  remove_nodes(blockchain, nid);
  list_nids(&(blockchain->blockchain_head));

  nodeDestructor(blockchain->blockchain_head);
  blockchainDestructor(blockchain);

  return 0;
}
