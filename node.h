#include "block.h"

#ifndef STRUCT_NODE
#define STRUCT_NODE
typedef struct s_node{
  int nid;
  BlockPtr bid_head;
  struct s_node *next_node;

  int (*getNid)(struct s_node*);
  void (*setNid)(struct s_node*, int);
} Node;
#endif

typedef Node *NodePtr;

//Allocate memory for Node struct
NodePtr nodeConstructor(void);

//Free allocated for Node struct
int nodeDestructor(NodePtr node);

//Initialize Node members
int nodeInitialize(NodePtr node);

//Return a pointer to the first Node with the input nid
NodePtr findNode(NodePtr node_head, int nid);