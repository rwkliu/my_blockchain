#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"
#include "arguments_blockchain.h"

void synchronize_nodes(BlockchainPtr blockchain, Node **noderef) {
  if (blockchain->sync_state == SYNCED) {
    printf("OK\n");
  } else {
    printf("Nodes not synced: resyncing now\n");
     




    printf("OK\n");
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
  blockchain.ls(&(blockchain.blockchain_head), NO_BID);
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Add a block 
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  char *bid = "223";
  printf("add bid %s to node 12\n", bid);
  add_block_to_node(&(blockchain.blockchain_head), bid, 12);
  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);
  printf("number of blocks in nid 12: %d\n", blockchain.blockchain_head->num_blocks);
  printf("Add bid %s to node 15\n", bid);
  add_block_to_node(&(blockchain.blockchain_head), bid, 15);
  printf("number of blocks in nid 15: %d\n", blockchain.blockchain_head->next_node->num_blocks);
  update_sync_state(&(blockchain), &(blockchain.blockchain_head));
  prompt(blockchain.num_nodes, blockchain.sync_state);

  //Remove block with same bid in all nodes
  printf("number of blocks in nid 12 before removal: %d\n", blockchain.blockchain_head->num_blocks);
  remove_block_from_nodes(&(blockchain.blockchain_head), bid);
  printf("number of blocks in nid 12 after removal: %d\n", blockchain.blockchain_head->num_blocks);
  printf("number of blocks in nid 15 after removal: %d\n", blockchain.blockchain_head->next_node->num_blocks);

  //Print nids and bids in blockchain
  printf("Print all nids and bids\n");
  blockchain.ls(&(blockchain.blockchain_head), NO_BID);
  printf("ls blocks again\n");
  blockchain.ls(&(blockchain.blockchain_head), NO_BID);

  //Syncrhonize nodes
  synchronize_nodes(&blockchain, &(blockchain.blockchain_head));
  //printf("Free allocated memory\n");
  // free_blockchain(&blockchain);

  return 0;
}
