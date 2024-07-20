#include "Sequence.h"
#include "deq.h"
#include "error.h"

/**
 * Creates a new Sequence object.
 * This funciton initializes a new sequence,
 * which is essentially a deq (double-ended queue) of pipelines.
 *
 * @return A pointer to the newly created Sequence object.
 */
extern Sequence newSequence() {
  return deq_new();
}

/**
 * Adds a Pipeline to a Sequence.
 * This function appends a pipeline to the end of the sequence's deq of pipelines.
 *
 * @param sequence The Sequence to which the pipeline will be added.
 * @param pipeline The Pipeline object to add to the sequence.
 */
extern void addSequence(Sequence sequence, Pipeline pipeline) {
  deq_tail_put(sequence,pipeline);
}

/**
 * Frees the memory associated with a Sequence.
 * This function cleans up all resources associated with the Sequence,
 * including all its pipelines.
 *
 * @param sequence The Sequence to be freed.
 */
extern void freeSequence(Sequence sequence) {
  deq_del(sequence,freePipeline);
}

/**
 * Executes each Pipeline in the Sequence.
 * This function iterates through the pipelines in the sequence and executes them,
 * handling the end-of-file flag.
 *
 * @param sequence The Sequence to be executed.
 * @param jobs The job control context.
 * @param eof Pointer to an integer representing the end-of-file condition.
 */
extern void execSequence(Sequence sequence, Jobs jobs, int *eof) {
  while (deq_len(sequence) && !*eof)
    execPipeline(deq_head_get(sequence),jobs,eof);
  freeSequence(sequence);
}
