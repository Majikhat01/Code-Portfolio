#ifndef SCANNER_H
#define SCANNER_H

// Scanner is a type representing a lexical scanner.
typedef void *Scanner;

/**
 * Creates a new Scanner object.
 * Initializes a scanner for the given input string, preparing it for tokenization.
 *
 * @param s The input string to be scanned.
 * @return A new Scanner object.
 */
extern Scanner newScanner(char *s);

/**
 * Frees the memory associated with a Scanner object.
 * This function should be called to clean up a Scanner once it's no longer needed.
 *
 * @param scan the Scanner object to be freed.
 */
extern void freeScanner(Scanner scan);

/**
 * Retrieves teh next token from the Scanner.
 * Advances the scanner to the next token and returns it.
 *
 * @param scan The Scanner from which to get the next token.
 * @return The next token as a string, or NULL if no more tokens are available.
 */
extern char *nextScanner(Scanner scan);

/**
 * Retrieves the current token from the Scanner without advancing.
 * This frunction is useful for lookahead operations in parsing.
 *
 * @param scan The Scanner from which to get the current token.
 * @return The current token as a string.
 */
extern char *currScanner(Scanner scan);

/**
 * Compares the current token with a specified string.
 * Checks if the current token matches the given string.
 *
 * @param scan The Scanner containing the current token.
 * @param s The string to compare with the current token.
 * @return 1 if the current token matches the string, 0 otherwise.
 */
extern int cmpScanner(Scanner scan, char *s);

/**
 * Consumes the current token if it matches a specified string.
 * If the current token matches the given string, it advances to the next token.
 *
 * @param scan The Scanner containing the current token.
 * @param s The string to be matched and consumed.
 * @return 1 if the token was consumed, 0 otherwise.
 */
extern int eatScanner(Scanner scan, char *s);

/**
 * Retrieves the position of the current token in the input string.
 * 
 * @param scan The Scanner object.
 * @return The position (index) of the current token in the input string.
 */
extern int posScanner(Scanner scan);

#endif
