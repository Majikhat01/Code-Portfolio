#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "Command.h"
#include "error.h"

/**
 * Structure representing a shell command.
 */
typedef struct {
    char *file;     // The Command to execute
    char **argv;    // Array of args for the command
} *CommandRep;

/**
 * Macros for defining built-in commands.
 */
#define BIARGS CommandRep r, int *eof, Jobs jobs
#define BINAME(name) bi_##name
#define BIDEFN(name) static void BINAME(name) (BIARGS)
#define BIENTRY(name) {#name,BINAME(name)}

static char *owd=0; // Old working directory
static char *cwd=0; // Current working directory

/**
 * Validates the number of args for built-in commands
 */
static void builtin_args(CommandRep r, int n) {
    char **argv=r->argv;
    for (n++; *argv++; n--);
    if (n)
        ERROR("wrong number of arguments to builtin command"); // warn
}

/**
 * Built-in 'exit' command: exits the shell.
 */
BIDEFN(exit) {
    builtin_args(r,0);
    *eof=1;
}

/**
 * Built-in 'pwd' command: prints the current working directory.
 */
BIDEFN(pwd) {
    builtin_args(r,0);
    if (!cwd)
        cwd=getcwd(0,0);
    printf("%s\n",cwd);
}

/**
 * Build-in 'cd' command: changes the current working directory.
 */
BIDEFN(cd) {
    builtin_args(r,1);
    if (strcmp(r->argv[1],"-")==0) {
        char *twd=cwd;
        cwd=owd;
        owd=twd;
    } else {
        if (owd) free(owd);
        owd=cwd;
        cwd=strdup(r->argv[1]);
    }
    if (cwd && chdir(cwd))
        ERROR("chdir() failed"); // warn
}

/**
 * Built-in 'history' command: prints the command history.
 */
BIDEFN(history) {
    builtin_args(r,0);
    HIST_ENTRY **the_list;
    the_list = history_list();
    if (the_list) {
        for (int i = 0; the_list[i]; i++) {
            printf("%d: %s\n", i + history_base, the_list[i]->line);
        }
    }
}

/**
 * Executes a built-in command, if the command is a built-in.
 */
static int builtin(BIARGS) {
    typedef struct {
        char *s;
        void (*f)(BIARGS);
    } Builtin;
    static const Builtin builtins[]={   // List of built-in commands
        BIENTRY(exit),
        BIENTRY(pwd),
        BIENTRY(cd),
        BIENTRY(history),
        {0,0}
    };
    int i;

    // Checks if the command is a built-in command and execute it
    for (i=0; builtins[i].s; i++)
        if (!strcmp(r->file,builtins[i].s)) {
            builtins[i].f(r,eof,jobs);
            return 1;
        }
    return 0;
}

/**
 * Converts a list of words (T_words) to an array of strings (args).
 */
static char **getargs(T_words words) {
    int n=0;
    T_words p=words;
    while (p) {
        p=p->words;
        n++;
    }
    char **argv=(char **)malloc(sizeof(char *)*(n+1));
    if (!argv)
        ERROR("malloc() failed");
    p=words;
    int i=0;
    while (p) {
        argv[i++]=strdup(p->word->s);
        p=p->words;
    }
    argv[i]=0;
    return argv;
}

/**
 * Creates a new Command object.
 */
extern Command newCommand(T_words words) {
    CommandRep r=(CommandRep)malloc(sizeof(*r));
    if (!r)
        ERROR("malloc() failed");
    r->argv=getargs(words);
    r->file=r->argv[0];
    return r;
}

/**
 * Executes a command in a child process.
 */
static void child(CommandRep r, int fg) {
    printf("In child process, executing command: %s\n", r->file);
    int eof=0;
    Jobs jobs=newJobs();
    if (builtin(r,&eof,jobs))
        return;
    execvp(r->argv[0],r->argv);
    ERROR("execvp() failed");
    exit(0);
}

/**
 * Executes a Command, potentially in a separate process.
 * Handles the forking and execution of commands, including built-ins.
 */
extern void execCommand(Command command, Pipeline pipeline, Jobs jobs,
        int *jobbed, int *eof, int fg) {
    CommandRep r=command;
    if (fg && builtin(r,eof,jobs))
        return;
    if (!*jobbed) {
        *jobbed=1;
        addJobs(jobs,pipeline);
    }
    int pid=fork();
    if (pid==-1) {
        ERROR("fork() failed");
    } else if (pid==0) {
        child(r,fg);
    } else {
        if (fg) {
            int status;
            waitpid(pid, &status, 0);
        } else {

        }
    }
}

/**
 * Frees the memory associated with a Command.
 */
extern void freeCommand(Command command) {
  CommandRep r=command;
  char **argv=r->argv;
  while (*argv)
    free(*argv++);
  free(r->argv);
  free(r);
}

/**
 * Frees any global or static state in the Command module.
 */
extern void freestateCommand() {
  if (cwd) free(cwd);
  if (owd) free(owd);
}
