#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "helpers.h"

void add_node(BlockchainPtr blockchain, NodePtr *headref, int nid) {
  NodePtr new_node = nodeConstructor();
  new_node->setNid(new_node, nid);

  new_node->next_node = NULL;
  new_node->prev_node = *headref;
  *headref = new_node;
  
  blockchain->setNumNodes(blockchain, blockchain->getNumNodes(blockchain) + 1);
  blockchain->latest_node = new_node;
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
  add_node(blockchain, &(blockchain->blockchain_head), nid);
  printf("added node nid: %d\n", blockchain->blockchain_head->getNid(blockchain->blockchain_head));
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  nid = 13;
  printf("second add node\n");
  add_node(blockchain, &(blockchain->latest_node), nid);
  printf("added node nid: %d\n", blockchain->blockchain_head->getNid(blockchain->latest_node));
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  
  nid = 15;
  printf("third add node\n");
  add_node(blockchain, &(blockchain->latest_node), nid);
  printf("added node nid: %d\n", blockchain->blockchain_head->getNid(blockchain->latest_node));
  prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));

  nodeDestructor(blockchain->blockchain_head);
  blockchainDestructor(blockchain);

  return 0;
}
