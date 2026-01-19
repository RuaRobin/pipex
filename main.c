
//infile -> 3

infile = open("infile", FLAG);
outfile = open("infile", FLAG);
int fd[2];
//[4,5]
if(pipe(fd) == -1)
{
  //  perror()
    return;
}
int id = fork();
//if id==-1
if (id==0)
{
    if(cmd1 == NULL)
    {
        // write error message
        // exite
    }
    // close readig end of the pipe
    // dup2 (infile, 0)
    // dup2 (fd[1], 1)
    // execve (cmd1)
}
int id2 = fork();

if (id2 ==0)
{
    if(cmd2 == NULL)
    {
        // write error message
        // exite
    }
    // close writin end of the pipe
    // dup2 (fd[0] , 0)
    // dup2 (outfile , 1)
    // execve (cmd1) 
}
//close the write end of the pipe 
waitpid(id1)
waitpid(id2)
// take status
// the exit code should be the secound cmd exit code meaning the secoind status, use wifexit