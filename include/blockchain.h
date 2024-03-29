#ifndef BLOCKCHAIN_INCLUDE_H
#define BLOCKCHAIN_INCLUDE_H

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

  void (*addNode)(struct s_blockchain *, Node**, int);
  void (*removeNode)(struct s_blockchain *, Node**, int);
  void (*addBlock)(struct s_blockchain *, Node **, char *, int);
  void (*removeBlock)(struct s_blockchain *, Node **, char *, int);
  void (*ls)(Node**, int);

} Blockchain;
#endif

typedef Blockchain *BlockchainPtr;

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(BlockchainPtr blockchain);

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain);

//Add node to blockchain
void addNode(BlockchainPtr blockchain, Node **noderef, int nid);

//Remove node from blockchain
void removeNode(BlockchainPtr blockchain, Node **noderef, int nid);

//Add block to node with specified nid
void addBlockToNode(BlockchainPtr blockchain, Node **noderef, char *bid, int nid);

//Remove blocks with specified nid from all nodes with that block
void removeBlockFromNode(BlockchainPtr blockchain, Node **noderef, char *bid, int nid);

//Print all nids and their bids
void lsBidsNids(Node **node_head, int lflag); 

//Check all nodes for the same blocks as the first node (genesis blocks)
int is_synchronized(Node **noderef);

//Find block
int block_found(Block **blockref, char *bid);

//Add missing blocks found in node_to_check to node_to_sync
void add_missing_blocks(BlockchainPtr blockchain, Block **block_tracer, Node **node_to_sync);

//Synchronize blockchain
void synchronize_nodes(BlockchainPtr blockchain, Node **noderef);

//Check if all nodes contain the same blocks and update the sync state
void update_sync_state(BlockchainPtr blockchain, Node **noderef);

void update_num_nodes(BlockchainPtr blockchain, commands command);

//Update the num_blocks variable
void update_numblocks(Node **Noderef, commands command);

//Save the blockchain to a backup file
void save_blockchain(Node **noderef);

//Free all allocated memory in blockchain (blocks, nodes)
void free_blockchain(BlockchainPtr blockchain);

#endif