#ifndef PARSER_H
#define PARSER_H

// Tree is a type representing the structure of a parsed command.
typedef void *Tree;

/**
 * Parses a given string (command line input) into a Tree structure.
 * This function is the entry point to the parser component of the shell.
 * It takes a command line string and converts it into a structured tree
 * represtation that can be used for further processing and execution.
 *
 * @param s The string representing the command line input to be parsed.
 * @return A Tree structure representing the parsed command, or NULL if parsing fails.
 */
extern Tree parseTree(char *s);

/**
 * Frees the memory associated with a Tree structure.
 * This function should be called to clean up a Tree structure once it is no longer needed,
 * to prevent memory leaks.
 *
 * @param t The Tree structure to be freed.
 */
extern void freeTree(Tree t);

#endif
