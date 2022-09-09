//Name: Colin Graham
//Last day edited: 4/28/22

/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 

char *global="sh257"; //global that holds "sh257"
void signal_catchfunc(int signal) //function to print out "Caught SIGINT and prints out the next command line in the shell if CTRL C is used.
{
  printf("\nCaught SIGINT");
  printf("\n%s>", global);
  fflush(stdout);
  return;
} //Last day edited: 4/27/22

void help() //Function that prints out 4 printf statements and returns when help is typed into the command line.
{
  printf("The developer's name is Colin Graham.\n");
  printf("To change the shell name, use 'shellex -p <prompt>'\n");
  printf("The built in commands are exit, pid, ppid, help, and cd.\n");
  printf("Please refer to man if further assistance is needed with other commands.\n");
return;
} //Last day edited: 4/27/22

void cd(char* newdir) //Function that determines if the cd can be changed to a new directory if the new directory is more than or equal to zero using an if else statement, and then prints out if a directory has been successfully changed or not.
{
   if (newdir != NULL) {
     int err = chdir(newdir);
     if (err>=0) {
       printf("Sucessfully changed directory to %s\n", newdir);
     }else{
       printf("%s is not a valid directory\n", newdir);
     } 
   } else {
      char cwd[100];
      if (getcwd(cwd, sizeof(cwd))!= NULL){
         printf("The current directory is: %s\n", cwd);
      } else {
         printf("Failed to get current directory.\n");
      }
   }
} //Last day edited: 4/27/22

int main(int argc, char*argv[]) 
{
    char cmdline[MAXLINE]; /* Command line */

    if (argc == 2) //If statement to see if 2 arguments are being passed.
    {
      printf("%s -p <prompt>\n", argv[0]);
      exit(0);
    }

    if (argc == 3) //If statement to see if 3 arguments are being passed.
    {
      if (strcmp(argv[1], "-p"))
      {
        printf("%s -p <prompt>\n", argv[0]);
        exit(0);
      }
      global=argv[2];
    }
    
    signal(SIGINT, signal_catchfunc); //Signal catcher for CTRL C.

    while (1) {
	/* Read */
	printf("%s> ", global);                   
	Fgets(cmdline, MAXLINE, stdin); 
	if (feof(stdin))
	    exit(0);

	/* Evaluate */
	eval(cmdline);
    } 
} //Last day edited: 4/27/22
/* $end shellmain */
  
/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv); 
    if (argv[0] == NULL)  
	return;   /* Ignore empty lines */

    if (!builtin_command(argv)) { 
        if ((pid = Fork()) == 0) {   /* Child runs user job */
            if (execvp(argv[0], argv ) < 0) { //execvp used instead of execv and passes 2 arguement variables instead of 3.
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        } //Last day edited: 4/27/22

	/* Parent waits for foreground job to terminate */
	if (!bg) {
	    int status;
	    if (waitpid(pid, &status, 0) < 0){  
		unix_error("waitfg: waitpid error");
            } else {
                printf("Exit status of child process %d: %d\n", pid, WEXITSTATUS(status));
            }
        }
        else
            printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "exit")){ //Quits the shell if exit is typed in the command line, and uses raise(SIGKILL) to end the process instead of exit().
	raise(SIGKILL);
        return 1;
    }  
    if (!strcmp(argv[0], "pid")){ //strcmp is used to see if the input is pid, and if so, pid is printed with getpid. 
	printf("Process id is %d\n", getpid());
        return 1;
    }
    if (!strcmp(argv[0], "ppid")){ //strcmp is used to see if the input is ppid, and if so, ppid is printed with getppid.
	printf("Parent process id is %d\n", getppid());
        return 1;
    }
    if (!strcmp(argv[0], "cd")){ //strcmp is used to see if the input is cd, and if so, the cd function is called and runs.
        cd(argv[1]);
    }
       
    if (!strcmp(argv[0], "help")) { //strcmp is used to see if the input is help, and if so, the help function is called and runs.
	help();
        return 1;
    } //Last day edited: 4/27/22
        

    return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */


