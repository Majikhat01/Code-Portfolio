#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Macro for emitting a warning message.
 * This macro prints a formatted warning message to the standard error stream,
 * including the file name and line number where the warning occurred.
 *
 * @param file The name of the file where the warning occurs.
 * @param line The line number in the file where the warning occurs.
 * @param kind A string label for the type of message
 * @param args Additional args for the warning message.
 */
#define WARNLOC(file,line,kind,args...) do {  \
  fprintf(stderr,"%s:%d: ",file,line);        \
  fprintf(stderr,"%s: ",kind);                \
  fprintf(stderr,args);                       \
  fprintf(stderr,"\n");                       \
  fflush(stderr);                             \
} while (0)

/**
 * Macro for emitting an error message and exiting.
 * This macro prints a formatted error message to the standard error stream and
 * then exits the program. It includes the file name and line number where the error occured.
 *
 * @param file The name of the file where the error occurs.
 * @param line The line number in the file where the error occurs.
 * @param kind A string label for the type of message.
 * @param args Additional args for teh error message.
 */
#define ERRORLOC(file,line,kind,args...) do { \
  WARNLOC(file,line,kind,args);               \
  exit(1);                                    \
} while (0)

/**
 * Convenience macro for emitting a warning.
 * Automatically fills in the __FILE__ and __LINE__ parameters for the WARNLOC macro.
 */
#define WARN(args...) WARNLOC(__FILE__,__LINE__,"warning",args)

/**
 * Conveniece macro for emitting an error and exiting.
 * Automatically fills in the __FILE__ and __LINE__ parametes for the ERRORLOC macro.
 */
#define ERROR(args...) ERRORLOC(__FILE__,__LINE__,"error",args)

#endif
