#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "helpers.h"
#include "arguments_blockchain.h"

int block_found(Block *blockref, char *bid) {
  while (blockref) {
    if (strncmp(blockref->bid, bid, strlen(bid)) == 0) {
      return 1;
    }
    blockref = blockref->next_block;
  }
  return 0;
}

void synchronize_nodes(BlockchainPtr blockchain, Node **noderef) {
 if (blockchain->sync_state == NOT_SYNCED) {
   if (block_found((*noderef)->bid_head, "21")) {
     printf("block found\n");
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
  char *bid1 = malloc(3 * sizeof(char));
  char *bid2 = malloc(3 * sizeof(char));
  strncpy(bid1, "21", 3);
  strncpy(bid2, "22", 3);
  blockchain.addBlock(&blockchain, &(blockchain.blockchain_head), bid1, 12);
  blockchain.addBlock(&blockchain, &(blockchain.blockchain_head), bid2, 15);

  //Print the blockchain
  blockchain.ls(&(blockchain.blockchain_head), PRINT_BID);
  synchronize_nodes(&blockchain, &(blockchain.blockchain_head));
  
  free_blockchain(&blockchain);

  return 0;
}
