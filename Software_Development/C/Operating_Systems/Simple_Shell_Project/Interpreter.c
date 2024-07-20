#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Interpreter.h"
#include "Sequence.h"
#include "Pipeline.h"
#include "Command.h"

static Command i_command(T_command t);
static void i_pipeline(T_pipeline t, Pipeline pipeline);
static void i_sequence(T_sequence t, Sequence sequence);

/**
 * Converts a parsed command tree node to a Command object.
 * This serves as a bridge between the parsing phase and the execution phase.
 *
 * @param t The tree node representing a command.
 * @return A Command object ready for execution or NULL if the tree node is NULL.
 */
static Command i_command(T_command t) {
  if (!t)
    return 0;
  Command command=0;
  if (t->words)
    command = newCommand(t->words);
  return command;
}

/**
 * Builds a pipeline from a parsed pipeline tree.
 * Recursively adds commands to the pipeline.
 *
 * @param t The tree node representing a pipeline.
 * @param pipeline The pipeline to which commands will be added.
 */
static void i_pipeline(T_pipeline t, Pipeline pipeline) {
  if (!t)
    return;
  addPipeline(pipeline,i_command(t->command));
  i_pipeline(t->pipeline,pipeline);
}

/**
 * Builds a sequence from a parsed sequence tree.
 * Recursively adds pipelines to the sequence.
 *
 * @param t The tree node representing a sequence.
 * @param sequence The sequence to which piplines will be added.
 */
static void i_sequence(T_sequence t, Sequence sequence) {
  if (!t)
    return;
  Pipeline pipeline=newPipeline(1);
  i_pipeline(t->pipeline,pipeline);
  addSequence(sequence,pipeline);
  i_sequence(t->sequence,sequence);
}

/**
 * Interprets a parsed command tree and executes it.
 * This is the entry point for executing a parsed command.
 *
 * @param t The root of the parsed command tree.
 * @param eof Pointer to an integer representing end-of-file condition.
 * @param jobs The structure holding job information for job control.
 */
extern void interpretTree(Tree t, int *eof, Jobs jobs) {
  if (!t)
    return;
  Sequence sequence=newSequence();
  i_sequence(t,sequence);
  execSequence(sequence,jobs,eof);
}
