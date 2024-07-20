#ifndef COMMAND_H
#define COMMAND_H

// Forward declaration of Command as a pointer to an undefined structure.
typedef void *Command;

#include "Tree.h"
#include "Jobs.h"
#include "Sequence.h"

// Function to create a new Command from a list of words (args).
extern Command newCommand(T_words words);

// Function to execute a Command within a given pipeline and job context.
extern void execCommand(Command command, Pipeline pipeline, Jobs jobs,
			int *jobbed, int *eof, int fg);

// Function to free memory associated with a Command.
extern void freeCommand(Command command);

// Function to free any global or static state maintained by the Command module.
extern void freestateCommand();

#endif
