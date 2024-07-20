#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"
#include "Tree.h"
#include "Jobs.h"

/**
 * Interprets and executes a parsed command tree.
 *
 * @param t The root of the parsed command tree.
 * @param eof Pointer to an integer representing end-of-file condition.
 * @param jobs The structure holding job information for job control.
 */
extern void interpretTree(Tree t, int *eof, Jobs jobs);

#endif
