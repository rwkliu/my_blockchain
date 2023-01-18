#include "node.h"

#ifndef ENUM_SYNC_STATE
#define ENUM_SYNC_STATE
typedef enum e_sync_state {
  SYNCED, NOT_SYNCED
} sync_state;
#endif

#ifndef STRUCT_BLOCKCHAIN
#define STRUCT_BLOCKCHAIN
typedef struct s_blockchain {
  int num_nodes;
  char sync_state;
  NodePtr blockchain_head;
  NodePtr latest_node;

  int (*getNumNodes)(struct s_blockchain *);
  char (*getSyncState)(struct s_blockchain *);
  void (*setNumNodes)(struct s_blockchain *, int);
  void (*setSyncState)(struct s_blockchain *, sync_state);
} Blockchain;
#endif

typedef Blockchain *BlockchainPtr;

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(BlockchainPtr blockchain);

//Free allocated memory for Blockchain struct
int blockchainDestructor(BlockchainPtr blockchain);

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain);

