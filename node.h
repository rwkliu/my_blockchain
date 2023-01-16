#include "block.h"

#ifndef STRUCT_NODE
#define STRUCT_NODE
typedef struct s_node{
  int nid;
  BlockPtr bid_head;
  struct s_node *next_node;

  int (*getNid)(struct s_node*);
  void (*setNid)(struct s_node*, int);
  void (*setBid)(struct s_node*, char *);
} Node;
#endif

typedef Node *NodePtr;

//Allocate memory for Node struct
NodePtr nodeConstructor(void);

//Free allocated for Node struct
int nodeDestructor(NodePtr node);

//Initialize Node members
int nodeInitialize(NodePtr node);
