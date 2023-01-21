#include "node.h"

#define SYNCED 's'
#define NOT_SYNCED '-'
#define PRINT_BID 1
#define NO_BID 0

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

//Add node to blockchain
void add_node(BlockchainPtr blockchain, Node **noderef, int nid);

void update_num_nodes(BlockchainPtr blockchain, commands command);

void remove_node(BlockchainPtr blockchain, Node **noderef, int nid);

//Check all nodes for the same blocks as the first node (genesis blocks)
int is_synchronized(Node **noderef);

//Check if all nodes contain the same blocks and update the sync state
void update_sync_state(BlockchainPtr blockchain, Node **noderef);

void ls_bids_nids(Node **node_head, int lflag); 
