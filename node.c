#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

//Allocate memory for Node struct
NodePtr nodeConstructor(void) {
  NodePtr node = malloc(sizeof(Node));
  nodeInitialize(node);
  return node;
}

//Free allocated memory for Node struct
int nodeDestructor(NodePtr node) {
  free(node);
  return 0;
}

//Initialize Node members
int nodeInitialize(NodePtr node) {
  node->nid = 0;
  node->num_blocks = 0;
  node->bid_head = NULL;
  node->next_node = NULL;
  return 0;
}
