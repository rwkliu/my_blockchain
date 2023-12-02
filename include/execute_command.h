#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H

#include "blockchain.h"
#include "helpers.h"

void execute_command(BlockchainPtr blockchain, string_array *split_read_buffer);

#endif