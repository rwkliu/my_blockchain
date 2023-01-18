#include "block.h"

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
