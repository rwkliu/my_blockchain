#include <stdlib.h>
#include "node.h"

int getNid(NodePtr this) {
  return this->nid;
}

void setNid(NodePtr this, int nid) {
  this->nid = nid;
}

int getNumBlocks(NodePtr this) {
  return this->num_blocks;
}

void setNumBlocks(NodePtr this, int num_blocks) {
  this->num_blocks = num_blocks;
}

//Return a pointer to the first Node with the input nid
NodePtr findNode(NodePtr node_head, int nid) {
  while(node_head) {
    if (node_head->getNid(node_head) == nid) {
      return node_head;
    }
    node_head = node_head->next_node;
  }
  return NULL;
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
  node->num_blocks = 0;
  node->bid_head = NULL;
  node->next_node = NULL;
  node->getNid = getNid;
  node->setNid = setNid;
  node->getNumBlocks = getNumBlocks;
  node->setNumBlocks = setNumBlocks;
  return 0;
}
