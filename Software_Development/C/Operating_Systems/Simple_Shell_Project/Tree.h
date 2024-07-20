#ifndef TREE_H
#define TREE_H

// Forward declarations for tree structure types.
typedef struct T_sequence *T_sequence;
typedef struct T_pipeline *T_pipeline;
typedef struct T_command  *T_command;
typedef struct T_words    *T_words;
typedef struct T_word     *T_word;

/**
 * Structure representing a sequence in the command tree.
 * A sequence consists of one or more pipelines, separated by operators line ';' or '&'
 */
struct T_sequence {
  T_pipeline pipeline;  // The first pipeline in the sequence.
  char *op;		        // Operator separating this pipeline from the next (';' or '&')
  T_sequence sequence;  // The next sequence in the chain.
};

/**
 * Structure representing a pipeline in the command tree.
 * A pipeline is a series of commands connected by pipes ('|')
 */
struct T_pipeline {
  T_command command;    // The first command in the pipeline.
  T_pipeline pipeline;  // The next pipeline in the chain.
};

/**
 * Structure representing a command in the command tree.
 * A command consists of a series of words, which include the command itself and its args.
 */
struct T_command {
  T_words words;    // The words that make up the command.
};

/**
 * Structure representing a linked list of words.
 * This is used to store both the command and its args.
 */
struct T_words {
  T_word word;      // A single word.
  T_words words;    // The next word in the list.
};

/**
 * Structure representing a single word.
 */
struct T_word {
  char *s;      // The string value of the word.
};

// Function prototypes for creating new instances of each structure.
extern T_sequence new_sequence();
extern T_pipeline new_pipeline();
extern T_command  new_command();
extern T_words    new_words();
extern T_word     new_word();

#endif
