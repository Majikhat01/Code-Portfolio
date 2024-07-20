#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Scanner.h"
#include "error.h"

/**
 * Structure representing the state of a scanner.
 * This structure holds the current position, the original string,
 * and other relevant information for scanning.
 */
typedef struct {
  int eos;      // Flag indicating end of string.
  char *str;    // the original string being scanned.
  char *pos;    // Current position in the string.
  char *curr;   // The current token.
} *ScannerRep;

/**
 * Creates a new Scanner object.
 * Allocates memory and initializes a scanner for the given string.
 *
 * @param s The string to be scanned.
 * @return A pointer to the newly created Scanner object.
 */
extern Scanner newScanner(char *s) {
  ScannerRep r=(ScannerRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->eos=0;
  r->str=strdup(s);
  r->pos=r->str;
  r->curr=0;
  return r;
}

/**
 * Frees the memory associated with a Scanner object.
 *
 * @param scan The Scanner object to be freed.
 */
extern void freeScanner(Scanner scan) {
  ScannerRep r=scan;
  free(r->str);
  if (r->curr)
    free(r->curr);
  free(r);
}

// Helper functions for scanning.
static char *thru(char *p, char *q) {
  for (; *p && strchr(q,*p); p++);
  return p;
}

static char *upto(char *p, char *q) {
  for (; *p && !strchr(q,*p); p++);
  return p;
}

static char *wsthru(char *p) { return thru(p," \t"); }
static char *wsupto(char *p) { return upto(p," \t"); }

/**
 * Moves to the next token in the scanner.
 *
 * @param scan The Scanner object.
 * @return The next token as a string, or NULL if the end of the string is reached.
 */
extern char *nextScanner(Scanner scan) {
  ScannerRep r=scan;
  if (r->eos)
    return 0;
  char *old=wsthru(r->pos);
  char *new=wsupto(old);
  int size=new-old;
  if (size==0) {
    r->eos=1;
    return 0;
  }
  if (r->curr)
    free(r->curr);
  r->curr=(char *)malloc(size+1);
  if (!r->curr)
    ERROR("malloc() failed");
  memmove(r->curr,old,size);
  (r->curr)[size]=0;
  r->pos=new;
  return r->curr;
}

/**
 * Gets the current token from the scanner without advancing.
 *
 * @param scan The Scanner object.
 * @return The current token as a string, or NULL if the end of the string is reached.
 */
extern char *currScanner(Scanner scan) {
  ScannerRep r=scan;
  if (r->eos)
    return 0;
  if (r->curr)
    return r->curr;
  return nextScanner(scan);
}

/**
 * Compares the current token with a specified string.
 *
 * @param scan The Scanner object.
 * @param s The string to compare with the current token.
 * @return 1 if the current token matches the string, 0 otherwise.
 */
extern int cmpScanner(Scanner scan, char *s) {
  ScannerRep r=scan;
  currScanner(scan);
  if (r->eos)
    return 0;
  if (strcmp(s,r->curr))
    return 0;
  return 1;
}

/**
 * Consumes the current token if it matches the specified string.
 *
 * @param scan The Scanner object.
 * @param s The string to match and consume.
 * @return 1 if the token was consumed, 0 otherwise.
 */
extern int eatScanner(Scanner scan, char *s) {
  int r=cmpScanner(scan,s);
  if (r)
    nextScanner(scan);
  return r;
}

/**
 * Gets the current position in the original string.
 *
 * @param scan The Scanner object.
 * @return The position as an integer.
 */
extern int posScanner(Scanner scan) {
  ScannerRep r=scan;
  return (r->pos)-(r->str);
}
