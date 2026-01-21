#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
if (argc != 5)
{
    write(2,"Not enough arguments \n ./pipex file1 cmd1 cmd2 file2 \n", 56);
    return 1;
}
int fd[2];
int infile = read_files(argv[1],0);
int outfile = read_files(argv[3],1);
char *cmd1 = findcommand(argv[2], envp);
char * cmd2 = findcommand(argv[4],envp);
if (!cmd2)
{
    write(2,"Command doesnt exist \n",27);
    return 127;
}
if (!cmd1)
    write(2,"Command doesnt exist \n",27);
if(pipe(fd) == -1)
{
    perror("pipe");
    close(infile);
    close(outfile);
    return;
}
if (infile > 0)
{
int id = fork();
if (id == -1 )
{
    perror("fork");
    close(infile);
    close(outfile);
    close(fd[0]);
    close(fd[1]);
    return;
}
if (id == 0)
{
    close(fd[0]);    // close readig end of the pipe
    dup2 (infile, 0);
    dup2 (fd[1], 1);
    if (execve(cmd1, infile,envp) == -1)
        write(2,"An error has occured \n",23);
}
}
else 
    write(2, "Error: cannot open infile\n", 27);
int id2 = fork();
if (id2==-1)
{
    perror();
    close(infile);
    close(outfile);
    close(fd[0]);
    close(fd[1]);
    return;
}
if (id2 ==0)
{
    close(fd[1]);    // close reading end of the pipe
    dup2 (fd[0] , 0);
    dup2 (outfile , 1);
    if (execve(cmd2, infile,envp) == -1)
        write(2,"An error has occured \n",23);}
//close the write end of the pipe 
close(fd[0]);
close(fd[1]);
waitpid(id);
waitpid(id2);
// take status
// the exit code should be the secound cmd exit code meaning the secoind status, use wifexit
return 0;
}
