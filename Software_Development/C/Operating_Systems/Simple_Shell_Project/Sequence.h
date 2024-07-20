#ifndef SEQUENCE_H
#define SEQUENCE_H

// Sequence is a type representing a series of commands or pipelines.
typedef void *Sequence;

#include "Jobs.h"
#include "Pipeline.h"

/**
 * Creates a new Sequence object.
 * This function allocates and initializes a new sequence which can hold a series of pipelines.
 *
 * @return A new Sequence object.
 */
extern Sequence newSequence();

/**
 * Adds a Pipeline to a Sequence.
 * This function appends a pipeline to the sequence,
 * indicating that it is a part of the command sequence.
 *
 * @param sequence The Sequence to which the pipeline will be added.
 * @param pipeline The Pipeline to be added to the sequence.
 */
extern void addSequence(Sequence sequence, Pipeline pipeline);

/**
 * Frees the memory associated with a Sequence.
 * This funciton cleans up all resources associated with the Sequence,
 * including any pipelines it contains.
 *
 * @param sequence The Sequence to be freed.
 */
extern void freeSequence(Sequence sequence);

/**
 * Executes the pipelines in the Sequence.
 * This funciton is responsible for executing all pipelines contained in
 * the sequence in the order they were added.
 *
 * @param sequence The Sequence to be executed.
 * @param jobs The job control context for execution.
 * @param eof Pointer to an integer representing the end-of-file condition.
 */
extern void execSequence(Sequence sequence, Jobs jobs, int *eof);

#endif
