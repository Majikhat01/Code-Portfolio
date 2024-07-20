#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tree.h"
#include "error.h"

/**
 * Macro for allocating and initializing tree structure instances.
 * It allocates memory for the specified type and initializes it to zero.
 * If memory allocation fails, it raises an error.
 */
#define ALLOC(t) \
  t v=malloc(sizeof(*v)); \
  if (!v) ERROR("malloc() failed"); \
  return memset(v,0,sizeof(*v));

/**
 * Creates a new T_sequence instance.
 * Allocates memory for a T_sequence and initializes it to zero.
 *
 * @return A pointer to the newly created T_sequence.
 */
extern T_sequence new_sequence() {ALLOC(T_sequence)}

/**
 * Creates a new T_pipeline instance.
 * Allocates memory for a T_pipeline an dinitializes it to zero.
 *
 * @return A pointer to the newly created T_pipeline.
 */
extern T_pipeline new_pipeline() {ALLOC(T_pipeline)}

/**
 * Creates a new T_cmomand instance.
 * Allocates memory for a T_command and initializes it to zero.
 *
 * @return A pointer to the newly created T_command.
 */
extern T_command  new_command()  {ALLOC(T_command)}

/**
 * Creates a new T_words instance.
 * Allocates memory for a T_words and initializes it to zero.
 *
 * @return A pointer to the newly created T_words.
 */
extern T_words    new_words()    {ALLOC(T_words)}

/**
 * Creates a new T_word instance.
 * Allocates memory for a T_word and initializes it to zero.
 *
 * @return A pointer to the newly created T_word.
 */
extern T_word     new_word()     {ALLOC(T_word)}
