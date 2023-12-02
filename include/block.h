#ifndef BLOCK_INCLUDE_H
#define BLOCK_INCLUDE_H

#ifndef STRUCT_BLOCK
#define STRUCT_BLOCK
typedef struct s_bid {
  char *bid;
  struct s_bid *next_block;

} Block;
#endif

typedef Block *BlockPtr;

//Allocate memory for Block struct
BlockPtr blockConstructor(void);

//Free allocated memory for Block struct
int blockDestructor(BlockPtr block);

//Initialize Block members
int blockInitialize(BlockPtr block);

//Remove block from Block linked list
int removeBlock(Block **block_head, char *bid);

int remove_all_blocks(Block **block_head);

#endif