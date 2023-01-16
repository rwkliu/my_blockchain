#include <stdlib.h>
#include "node.h"

int getNid(NodePtr this) {
  return this->nid;
}

char *getBid(NodePtr this) {
  return this->bid;
}

void setNid(NodePtr this, int nid) {
  this->nid = nid;
}

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
  node->bid = "";
  node->next_node = NULL;
  node->getNid = getNid;
  node->getBid = getBid;
  node->setNid = setNid;
  return 0;
}
