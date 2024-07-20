#ifndef PIPELINE_H
#define PIPELINE_H

// Pipeline is a type representing a series of commands to be executed in a connected sequence.
typedef void *Pipeline;

#include "Command.h"
#include "Jobs.h"

/**
 * Creates a new Pipeline object.
 * A pipeline consists of a series of commands executed sequentially,
 * where the output of one command is the input to the next.
 *
 * @param fg A flag indicating if the pipeline is to be executed in the foreground.
 * @return A new Pipeline object.
 */
extern Pipeline newPipeline(int fg);

/**
 * Adds a Command to a Pipeline.
 * This function appends a new command to the end of the specified pipeline.
 *
 * @param pipeline The Pipeline to which the command will be added.
 * @param command The Command to add to the pipeline.
 */
extern void addPipeline(Pipeline pipeline, Command command);

/**
 * Retrieves the size (number of commands) of the Pipeline.
 *
 * @param pipeline The Pipeline whose size is to be dtermined.
 * @return The number of commands in the Pipeline.
 */
extern int sizePipeline(Pipeline pipeline);

/**
 * Executes the commands in the Pipeline.
 * This function is responsible for executing all commands in teh pipeline,
 * properly setting up pipes for inter-command communication if necessary.
 *
 * @param pipeline The Pipeline to be executed.
 * @param jobs The job control context in which the pipeline is executed.
 * @param eof Pointer to an integer representing the end-of-file condition.
 */
extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof);

/**
 * Frees the memory associated with a Pipeline.
 * This function should be called to clean up a Pipeline once it is no longer needed.
 *
 * @param pipeline The Pipeline to be freed.
 */
extern void freePipeline(Pipeline pipeline);

#endif
