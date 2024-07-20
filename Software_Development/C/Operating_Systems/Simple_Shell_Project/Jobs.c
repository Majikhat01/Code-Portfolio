#include "Jobs.h"
#include "deq.h"
#include "error.h"

/**
 * Creates and initializes a new Jobs strucure.
 * This function uses a deq (double-ended queue) to represent the collection of jobs.
 *
 * @return A pointer to the newly created Jobs structure
 */
extern Jobs newJobs() {
  return deq_new();
}

/**
 * Adds a Pipeline to the specified Jobs structure.
 * This function inserts the pipeline at the tail of the deq representing the jobs.
 *
 * @param jobs The Jobs structure where the pipeline will be added.
 * @param pipeline The Pipeline object to add to the jobs.
 */
extern void addJobs(Jobs jobs, Pipeline pipeline) {
  deq_tail_put(jobs,pipeline);
}

/**
 * Gets the size (numver of elements) of the Jobs structure.
 * This function returns the length of the deq, which represents the number of jobs.
 *
 * @param jobs The Jobs structure whose size is to be determined.
 * @return The number of elements (jobs) in the Jobs structure.
 */
extern int sizeJobs(Jobs jobs) {
  return deq_len(jobs);
}

/**
 * Frees the Jobs structure and all its associated resources.
 * This funciton deletes the deq and frees the memory used by each Pipeline in the jobs.
 *
 * @param jobs The Jobs structure to be freed.
 */
extern void freeJobs(Jobs jobs) {
  deq_del(jobs,freePipeline);
}
