#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Pipeline.h"
#include "deq.h"
#include "error.h"

/**
 * Structure representing a pipeline in the shell.
 * It consists of a deq of precesses (commands) and a flag indicating foreground execution.
 */
typedef struct {
  Deq processes;    // Deq of commands in the pipeline.
  int fg;			// Flag indicating if the pipeline is executed in the foreground (not "&")
} *PipelineRep;

/**
 * Creates a new Pipeline object.
 * Allocates memory for a new pipeline and initializes its structure.
 *
 * @param fg An integer flag indicating foreground execution (1 for foreground, 0 for background).
 * @return A pointer to the newly created Pipeline object.
 */
extern Pipeline newPipeline(int fg) {
  PipelineRep r=(PipelineRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->processes=deq_new();
  r->fg=fg;
  return r;
}

/**
 * Adds a Command to a Pipeline.
 * This function appends a command to the end of the pipeline's deq of precesses.
 *
 * @param pipeline The Pipeline to which the command is being added.
 * @param command The Command to add to the pipeline.
 */
extern void addPipeline(Pipeline pipeline, Command command) {
  PipelineRep r=(PipelineRep)pipeline;
  deq_tail_put(r->processes,command);
}

/**
 * Retrieves the size of the Pipeline (number of commands).
 *
 * @param pipeline The Pipeline whose size is to be determined.
 * @return The number of commands in the Pipeline.
 */
extern int sizePipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  return deq_len(r->processes);
}

/**
 * Executes each command in the Pipeline.
 * Iterates through the commands and executes them, handling foreground and background execution.
 *
 * @param pipeline The Pipeline being executed.
 * @param jobs The job control context.
 * @param jobbed Pointer to an integer flag indicating if the job has been added to the job list.
 * @param eof Pointer to an integer representing the end-of-file condition.
 */
static void execute(Pipeline pipeline, Jobs jobs, int *jobbed, int *eof) {
  PipelineRep r=(PipelineRep)pipeline;
  for (int i=0; i<sizePipeline(r) && !*eof; i++)
    execCommand(deq_head_ith(r->processes,i),pipeline,jobs,jobbed,eof,1);
}

/**
 * Executes the Pipeline, handling job control and execution flow.
 *
 * @param pipeline The Pipeline to be executed.
 * @param jobs The job control structure.
 * @param eof Pointer to an integer representing the ind-of-file condition.
 */
extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof) {
  int jobbed=0;
  execute(pipeline,jobs,&jobbed,eof);
  if (!jobbed)
    freePipeline(pipeline);	// Freeing the pipeline for fg builtins, and such
}

/**
 * Frees the memory associated with a Pipeline.
 * Cleans up the resources used by the Pipeline, including all its commands.
 *
 * @param pipeline The Pipeline to be freed.
 */
extern void freePipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  deq_del(r->processes,freeCommand);
  free(r);
}
