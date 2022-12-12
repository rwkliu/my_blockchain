#ifndef BLOCK
#define BLOCK
typedef struct s_block {
  int nid;
  char *bid;
  struct s_block *next_block;
  struct s_block *prev_block;
} Block;
#endif

typedef Block *BlockPtr;

#ifndef BLOCKCHAIN
#define BLOCKCHAIN
typedef struct s_blockchain {
  int num_nodes;
  char sync_state;
  BlockPtr first_block;

  int (*get_num_nodes)(struct s_blockchain *Blockchain_ptr);
  char (*get_sync_state)(struct s_blockchain *Blockchain_ptr);
} Blockchain;
#endif

typedef Blockchain *BlockchainPtr;

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(void);

//Free allocated memory for Blockchain struct
int blockchainDestructor(BlockchainPtr blockchain);

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain);