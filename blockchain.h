#include "node.h"

#define SYNCED 's'
#define NOT_SYNCED '-'

#ifndef ENUM_SYNC_STATE
#define ENUM_SYNC_STATE
typedef enum e_sync_state {
  IS_SYNCED, IS_NOT_SYNCED
} sync_state;
#endif

#ifndef STRUCT_BLOCKCHAIN
#define STRUCT_BLOCKCHAIN
typedef struct s_blockchain {
  int num_nodes;
  char sync_state;
  NodePtr blockchain_head;

} Blockchain;
#endif

typedef Blockchain *BlockchainPtr;

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(BlockchainPtr blockchain);

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain);
