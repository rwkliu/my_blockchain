#ifndef STRUCT_NODE
#define STRUCT_NODE
typedef struct s_node{
  int nid;
  char *bid;
  struct s_node *next_node;
  struct s_node *prev_node;
} Node;
#endif

typedef Node *NodePtr;

#ifndef STRUCT_BLOCKCHAIN
#define STRUCT_BLOCKCHAIN
typedef struct s_blockchain {
  int num_nodes;
  char sync_state;
  NodePtr blockchain_head;

  int (*getNumNodes)(struct s_blockchain *Blockchain_ptr);
  char (*getSyncState)(struct s_blockchain *Blockchain_ptr);
} Blockchain;
#endif

typedef Blockchain *BlockchainPtr;

//Allocate memory for Blockchain struct
BlockchainPtr blockchainConstructor(void);

//Free allocated memory for Blockchain struct
int blockchainDestructor(BlockchainPtr blockchain);

//Initialize Blockchain members
int blockchainInitialize(BlockchainPtr blockchain);

//Allocate memory for Node struct
NodePtr nodeConstructor(void);

//Free allocated for Node struct
int nodeDestructor(NodePtr node);

//Initialize Node members
int nodeInitialize(NodePtr node);
