#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "Jobs.h"
#include "Parser.h"
#include "Interpreter.h"
#include "error.h"

int main() {
  int eof=0;            // End-of-file flag.
  Jobs jobs=newJobs();  // Initialize job control structure.
  char *prompt=0;

  // Setup for interactive mode
  if (isatty(fileno(stdin))) {
    using_history();            // Enable command history.
    read_history(".history");   // Read hsitory from file.
    prompt="$ ";                // Set shell prompt.
  } else {
    rl_bind_key('\t',rl_insert);            // Disable tab completion.
    rl_outstream=fopen("/dev/null","w");    // Suppress output.
  }
  
  // Main shell loop.
  while (!eof) {
    char *line=readline(prompt);    // Read a line of input.
    if (!line)  // Break loop if no input is received (EOF).
      break;
    if (*line)
      add_history(line);    // Add non-empty lines to history.

    Tree tree=parseTree(line);      // Parse the input line into a syntax tree.
    free(line);                     // Free the read line.

    interpretTree(tree,&eof,jobs);  // Interpret and execute the parsed tree.
    freeTree(tree);                 // Free the syntax tree.
  }

  // Cleanup on shell exit.
  if (isatty(fileno(stdin))) {
    write_history(".history");  // Write history to file.
    rl_clear_history();         // Clear the readline history.
  } else {
    fclose(rl_outstream);       // Close the redirected output stream.
  }
  freestateCommand();           // Free any global command state.
  return 0;
}
