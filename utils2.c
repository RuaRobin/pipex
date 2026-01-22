/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdalqa <rabdalqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:15:06 by rabdalqa          #+#    #+#             */
/*   Updated: 2026/01/22 16:41:47 by rabdalqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_cmd2(t_pipex *pipex,char *argv, char **envp)
{
    char **ppoutfile;

    if (pipex->id2 == -1)
        clean_all("fork",pipex);
    if (pipex->id2 ==0)
    {
        close(pipex->fd[1]);   
    if (dup2 (pipex->fd[0] , STDIN_FILENO) == -1)
        dup_errors(pipex,"dup2 pipe",2);
    close(pipex->fd[0]);
    if (dup2 (pipex->outfile , 1)== -1)
        dup_errors(pipex,"dup2 outfile",2);
    close(pipex->outfile);
    ppoutfile= ft_split(argv, ' ');
    if (!ppoutfile)
    {
        ft_putendl_fd("A memory error has occured ",2);
        exit(1);
    }
    if (execve(pipex->cmd2, ppoutfile ,envp) == -1)
        excev_errors("exceve cmd2",ppoutfile);
}
}

char	*free_all(char **ptr)
{
    int i;

    i = 0;
	if (!ptr)
        return NULL;
    while(ptr[i])
    {
		free(ptr[i]);
		i++;
	}
    free(ptr);
    return NULL;
}

void execute_cmd1(t_pipex *pipex,char *argv, char **envp)
{
    char **ppinfile;

    if (pipex->id1 == -1 )
            clean_all("fork",pipex);
    if (pipex->id1 == 0)
        {
            close(pipex->fd[0]);
            if (dup2 (pipex->infile, STDIN_FILENO) == -1)
                dup_errors(pipex,"dup2 infile",1);
            close(pipex->infile);
            if (dup2 (pipex->fd[1], STDOUT_FILENO)== -1)
                dup_errors(pipex,"dup2 pipe",1);
            close(pipex->fd[1]);
            ppinfile = ft_split(argv, ' ');
            if (!ppinfile)
            {
                ft_putendl_fd("A memory error has occured ",2);
                exit(1);
            }
            if (execve(pipex->cmd1, ppinfile ,envp) == -1)
                excev_errors("exceve cmd1", ppinfile);
        }
}

void excev_errors(char *message, char **args)
{
        if (!ft_strcmp("exceve cmd1",message))
            perror("exceve cmd1");
        else
            perror("exceve cmd2");
        free_all(args);
        exit(127);
}
void dup_errors(t_pipex *pipex, char *message, int cmd)
{
    if (cmd == 1)
    {
    if (!ft_strcmp("dup2 infile",message))
    {
        close(pipex->infile);
        perror("dup2 infile");
    }
    else if(!ft_strcmp("dup2 pipe",message)) 
        perror("dup2 pipe");
    close(pipex->fd[1]);
    }
    else
    {
        if(!ft_strcmp("dup2 outfile",message))
            perror("dup2 outfile");
        else if(!ft_strcmp("dup2 pipe",message)) 
        {
            perror("dup2 pipe");
            close(pipex->fd[0]);
        }
        close(pipex->outfile);
    }
    exit(1);
}
