#ifndef JOBS_H
#define JOBS_H

// Jobs is a type representing a collection of background or foreground tasks (pipelines).
typedef void *Jobs;

#include "Pipeline.h"

/**
 * Creates a new Jobs structure.
 * This structure is used to manage and keep track of jobs (background or foreground tasks).
 *
 * @return A new Jobs object for tracking jobs.
 */
extern Jobs newJobs();

/**
 * Adds a Pipeline to a Jobs structure.
 * This function is used to add a new task (Pipeline) to the collection of jobs.
 *
 * @param jobs The Jobs structure to which the pipeline will be added.
 * @param pipeline The Pipeline to be added to the Jobs structure.
 */
extern void addJobs(Jobs jobs, Pipeline pipeline);

/**
 * Retrieves the size (number of jobs) in a Jobs structure.
 *
 * @param jobs The Jobs structure whose size is to be determined.
 * @return The number of jobs currently in the Jobs structure.
 */
extern int sizeJobs(Jobs jobs);

/**
 * Frees the memory associated with a Jobs structure.
 * This function cleans up all resources associated with the Jobs strucutre.
 *
 * @param jobs The Jobs structure to be freed.
 */
extern void freeJobs(Jobs jobs);

#endif
