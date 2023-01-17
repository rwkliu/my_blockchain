#include <stdlib.h>
#include <string.h>
#include "block.h"

char *getBid(BlockPtr this) {
  return this->bid;
}

void setBid(BlockPtr this, char *bid) {
  this->bid = bid;
}

void addBlock(BlockPtr *block_head, char *bid) {
  BlockPtr new_block = blockConstructor();
  BlockPtr *headref = block_head;
  new_block->setBid(new_block, bid);

  while((*headref)) {
    headref = &((*headref)->next_block);
  }

  new_block->next_block = *headref;
  *headref = new_block;
}

void removeBlock(BlockPtr *block_head, char *bid) {
  BlockPtr *headref = block_head;

  while ((*headref) && strcmp((*headref)->getBid(*headref), bid) != 0) {
    headref = &((*headref)->next_block);
  }

  if (*headref == NULL) {
    BlockPtr to_delete = *headref;
    *headref = (*headref)->next_block;
    blockDestructor(to_delete);
  }
}

//Allocate memory for Block struct
BlockPtr blockConstructor(void) {
  BlockPtr block = malloc(sizeof(Block));
  blockInitialize(block);
  return block;
}

//Free allocated memory for Block struct
int blockDestructor(BlockPtr block) {
  // free(block->bid);
  free(block);
  return 0;
}

//Initialize Block members
int blockInitialize(BlockPtr block) {
  block->bid = NULL;
  block->next_block = NULL;
  block->getBid = getBid;
  block->setBid = setBid;
  block->addBlock = addBlock;
  block->removeBlock = removeBlock;
  
  return 0;
}
