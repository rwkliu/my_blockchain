#ifndef BLOCKCHAIN
#define BLOCKCHAIN
typedef struct s_blockchain {
  int num_nodes;
  char sync_status;

  struct s_blockchain (*init_blockchain)();

} Blockchain;
#endif

typedef Blockchain *BlockchainPtr;

#ifndef BLOCK
#define BLOCK
typedef struct s_block {
  int nid;
  char *bid;
  struct s_block *next_block;
  struct s_block *prev_block;
} Block;
#endif

typedef Block *Block_ptr;