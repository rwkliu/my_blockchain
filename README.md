# Welcome to My Blockchain
***

## Task
The task is to implement a blockchain - a chain of nodes that contains a chain of blocks.

## Description
The high level execution sequence is as follows:
1. Prompt user for input
2. Parse the input
3. Execute the command
4. Repeat 1. unless the quit command is entered

## Installation
To compile the program, run make to generate the executable file my_blockchain.

## Usage
The my_blockchain program has the following set of commands available:
* add: add node or block to the blockchain
* rm: remove node or block from the blockchain
* ls: list all nodes by their identifiers (nid). If -l is specified, all blocks associated with the node is listed
* sync: synchronize all of the nodes such that all nodes are composed of the same blocks. 
* quit: save the blockchain to a backup file and quit the program.

### Things to Improve
* Point args.read_buffer to output of my_readline
* Combine command array and command_strings into hash map
* Reduce if-else statements in nid function
* Create generic linked list function library 
* Try implementing an array of pointers to a linked list of bids
* Implement loading a blockchain from a backup file
* Implement '*' functionality

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
