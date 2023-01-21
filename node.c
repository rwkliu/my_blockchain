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

void update_numblocks(Node **Noderef, commands command) {
  switch (command) {
    case ADD:
      (*Noderef)->num_blocks += 1;
      break;
    case RM:
      (*Noderef)->num_blocks -= 1;
      break;
  }
}

void add_block_to_node(Node **noderef, char *bid, int nid) {
  Node **tracer = noderef;
  while (*tracer) {
    if ((*tracer)->nid == nid) {
      addBlock(&(*tracer)->bid_head, bid);
      update_numblocks(&(*tracer), ADD);
    }
    tracer = &(*tracer)->next_node;
  }
}

void remove_block_from_nodes(Node **noderef, char *bid) {
  Node **tracer = noderef;

  while (*tracer) {
    removeBlock(&(*tracer)->bid_head, bid);
    update_numblocks(&(*tracer), RM);
    tracer = &(*tracer)->next_node;
  }
}
