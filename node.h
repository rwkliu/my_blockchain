#include "block.h"
#include "arguments_blockchain.h"

#ifndef STRUCT_NODE
#define STRUCT_NODE
typedef struct s_node{
  int nid;
  int num_blocks;
  BlockPtr bid_head;
  struct s_node *next_node;

} Node;
#endif

typedef Node *NodePtr;

//Allocate memory for Node struct
NodePtr nodeConstructor(void);

//Free allocated for Node struct
int nodeDestructor(NodePtr node);

//Initialize Node members
int nodeInitialize(NodePtr node);

//Update the num_blocks variable
void update_numblocks(Node **noderef, commands command);

//Add block to end of Block linked list
void addBlock(Block **block_head, char *bid);

//Add block to node's Block linked list
void add_block_to_node(Node **noderef, char *bid, int nid); 

//Remove block from nodes
void remove_block_from_nodes(Node **noderef, char *bid);