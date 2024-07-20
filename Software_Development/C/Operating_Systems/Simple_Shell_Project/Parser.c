#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Tree.h"
#include "Scanner.h"
#include "error.h"

// Scanner used throughout the parser.
static Scanner scan;

// Redefine the ERROR macro for parser-specific error messages.
#undef ERROR
#define ERROR(s) ERRORLOC(__FILE__,__LINE__,"error","%s (pos: %d)",s,posScanner(scan))

// Forward declarations of parsing functions.
static char *next()       { return nextScanner(scan); }
static char *curr()       { return currScanner(scan); }
static int   cmp(char *s) { return cmpScanner(scan,s); }
static int   eat(char *s) { return eatScanner(scan,s); }

// Utility functions to interact with the scanner.
static T_word p_word();
static T_words p_words();
static T_command p_command();
static T_pipeline p_pipeline();
static T_sequence p_sequence();

/**
 * Parses a single word from the scanner.
 */
static T_word p_word() {
  char *s=curr();
  if (!s)
    return 0;
  T_word word=new_word();
  word->s=strdup(s);
  next();
  return word;
}

/**
 * Parses a sequence of words, handling the basic units of a command.
 */
static T_words p_words() {
  T_word word=p_word();
  if (!word)
    return 0;
  T_words words=new_words();
  words->word=word;
  if (cmp("|") || cmp("&") || cmp(";"))
    return words;
  words->words=p_words();
  return words;
}

/**
 * Parses a command, which is a sequence of words.
 */
static T_command p_command() {
  T_words words=0;
  words=p_words();
  if (!words)
    return 0;
  T_command command=new_command();
  command->words=words;
  return command;
}

/**
 * Parses a pipeline of commands.
 */
static T_pipeline p_pipeline() {
  T_command command=p_command();
  if (!command)
    return 0;
  T_pipeline pipeline=new_pipeline();
  pipeline->command=command;
  if (eat("|"))
    pipeline->pipeline=p_pipeline();
  return pipeline;
}

/**
 * Parses a sequence of commands or pipelines, separated by '&' or ';'.
 */
static T_sequence p_sequence() {
  T_pipeline pipeline=p_pipeline();
  if (!pipeline)
    return 0;
  T_sequence sequence=new_sequence();
  sequence->pipeline=pipeline;
  if (eat("&")) {
    sequence->op="&";
    sequence->sequence=p_sequence();
  }
  if (eat(";")) {
    sequence->op=";";
    sequence->sequence=p_sequence();
  }
  return sequence;
}

/**
 * Parses the entire input string into a tree structure.
 */
extern Tree parseTree(char *s) {
  scan=newScanner(s);
  Tree tree=p_sequence();
  if (curr())
    ERROR("extra characters at end of input");
  freeScanner(scan);
  return tree;
}

// Forward declarations for tree freeing functions.
static void f_word(T_word t);
static void f_words(T_words t);
static void f_command(T_command t);
static void f_pipeline(T_pipeline t);
static void f_sequence(T_sequence t);

/**
 * Frees a T_word structure.
 */
static void f_word(T_word t) {
  if (!t)
    return;
  if (t->s)
    free(t->s);
  free(t);
}

/**
 * Recursively frees a T_words structure.
 */
static void f_words(T_words t) {
  if (!t)
    return;
  f_word(t->word);
  f_words(t->words);
  free(t);
}

/**
 * Frees a T_command structure.
 */
static void f_command(T_command t) {
  if (!t)
    return;
  f_words(t->words);
  free(t);
}

/**
 * Recursively frees a T_pipeline structure.
 */
static void f_pipeline(T_pipeline t) {
  if (!t)
    return;
  f_command(t->command);
  f_pipeline(t->pipeline);
  free(t);
}

/**
 * Recursively frees a T_sequence structure.
 */
static void f_sequence(T_sequence t) {
  if (!t)
    return;
  f_pipeline(t->pipeline);
  f_sequence(t->sequence);
  free(t);
}

/**
 * Frees the entire tree structure
 */
extern void freeTree(Tree t) {
  f_sequence(t);
}
