#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"
#include "arguments_blockchain.h"

void synchronize_nodes(BlockchainPtr blockchain, Node **noderef) {
  if (blockchain->sync_state == NOT_SYNCED) {
    
  }
  printf("OK\n");
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
  blockchain.addNode(&blockchain, &(blockchain.blockchain_head), nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  nid = 13;
  printf("second add node\n");
  blockchain.addNode(&blockchain, &(blockchain.blockchain_head), nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);
  
  nid = 15;
  printf("third add node\n");
  blockchain.addNode(&blockchain, &(blockchain.blockchain_head), nid);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Print nid of all nodes in blockchain
  printf("ls\n");
  blockchain.ls(&(blockchain.blockchain_head), NO_BID);

  //Remove a node and print the remaining nodes
  nid = 13;
  printf("Remove node %d\n", nid);
  blockchain.removeNode(&blockchain,&(blockchain.blockchain_head), nid);
  printf("Remove node 12\n");
  blockchain.removeNode(&blockchain,&(blockchain.blockchain_head), 12);
  blockchain.ls(&(blockchain.blockchain_head), NO_BID);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Add blocks
  char *bid = "223";
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  printf("add bid %s to node 12\n", bid);
  blockchain.addBlock(&blockchain, &(blockchain.blockchain_head), bid, 12);
  prompt(blockchain.num_nodes, blockchain.sync_state);
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  printf("Add bid %s to node 15\n", bid);
  blockchain.addBlock(&blockchain, &(blockchain.blockchain_head), bid, 15);
  //printf("number of blocks in nid 15: %d\n", blockchain.blockchain_head->next_node->num_blocks);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Remove block with same bid in all nodes
  printf("number of blocks in nid 12 before removal: %d\n", blockchain.blockchain_head->num_blocks);
  blockchain.removeBlock(&blockchain, &(blockchain.blockchain_head), bid, 12);
  printf("number of blocks in nid 12 after removal: %d\n", blockchain.blockchain_head->num_blocks);
  //printf("number of blocks in nid 15 after removal: %d\n", blockchain.blockchain_head->next_node->num_blocks);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Print nids and bids in blockchain
  printf("Print all nids and bids\n");
  blockchain.ls(&(blockchain.blockchain_head), PRINT_BID);
  printf("ls blocks again\n");
  blockchain.ls(&(blockchain.blockchain_head), PRINT_BID);

  //Syncrhonize nodes
  //synchronize_nodes(&blockchain, &(blockchain.blockchain_head));
  printf("Free allocated memory\n");
  free_blockchain(&blockchain);

  return 0;
}
