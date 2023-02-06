#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"
#include "arguments_blockchain.h"

int block_found(Block **blockref, char *bid) {
  while (*blockref) {
    if (strncmp((*blockref)->bid, bid, strlen(bid)) == 0) {
      return 1;
    }
    blockref = &(*blockref)->next_block;
  }
  return 0;
}

void synchronize_nodes(BlockchainPtr blockchain, Node **noderef) {
  if (blockchain->sync_state == NOT_SYNCED) {
    Node **node_to_sync = noderef;
    Node **node_to_check = &(*noderef)->next_node;
    Block **block_tracer = &(*node_to_check)->bid_head;

    //Synchronize first node
    while (*node_to_check) {
      while (*block_tracer) {
        if (!block_found(&(*node_to_sync)->bid_head, (*block_tracer)->bid)) {
          addBlock(&(*node_to_sync)->bid_head, (*block_tracer)->bid);
        }
        block_tracer = &(*block_tracer)->next_block;
      }
      node_to_check = &(*node_to_check)->next_node;
      block_tracer = &(*node_to_check)->bid_head;
    }
    //Syncrhonize subsequent nodes. Add missing blocks to node if it has blocks.
    //Otherwise, add all the blocks from the previous node
    node_to_sync = &(*noderef)->next_node;
    node_to_check = noderef;
    block_tracer = &(*node_to_check)->bid_head;

    while (*node_to_check && *node_to_sync) {
      while (*block_tracer) {
        if (!block_found(&(*node_to_sync)->bid_head, (*block_tracer)->bid)) {
          addBlock(&(*node_to_sync)->bid_head, (*block_tracer)->bid);
        }
        block_tracer = &(*block_tracer)->next_block;
      }
      node_to_check = &(*node_to_check)->next_node;
      block_tracer = &(*node_to_check)->bid_head;
      node_to_sync = &(*node_to_sync)->next_node;
    }
  }
  printf("OK\n");
}

int main() {
  Blockchain blockchain;
  blockchainConstructor(&blockchain);

  //add nodes
  blockchain.addNode(&blockchain, &(blockchain.blockchain_head), 12);
  blockchain.addNode(&blockchain, &(blockchain.blockchain_head), 15);
  blockchain.addNode(&blockchain, &(blockchain.blockchain_head), 13);

  //add blocks
  char *bid1 = "21";
  char *bid2 = "22";
  blockchain.addBlock(&blockchain, &(blockchain.blockchain_head), bid1, 12);
  blockchain.addBlock(&blockchain, &(blockchain.blockchain_head), bid2, 15);

  //Print the blockchain
  blockchain.ls(&(blockchain.blockchain_head), PRINT_BID);
  synchronize_nodes(&blockchain, &(blockchain.blockchain_head));
  blockchain.ls(&(blockchain.blockchain_head), PRINT_BID);
  
  free_blockchain(&blockchain);

  return 0;
}
