/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdalqa <rabdalqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:15:08 by rabdalqa          #+#    #+#             */
/*   Updated: 2026/01/22 16:15:09 by rabdalqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void clean_all_final(t_pipex *pipex, char *message)
{
    if (!ft_strcmp(message,"close"))
    {
    close(pipex->fd[0]);
    close(pipex->fd[1]);
    close(pipex->outfile);
    }
    else 
    {
    if (pipex->cmd1 )
        free(pipex->cmd1);
    if (pipex->cmd2)
        free(pipex->cmd2); 
    }
}

void clean_all(char * message, t_pipex *pipex)
{
    if (!ft_strcmp(message,"fork"))
    {
        perror("fork");
        close(pipex->fd[0]);
        close(pipex->fd[1]);
    }
    else 
        perror("pipe");
    if (pipex->infile >= 0 )    
        close(pipex->infile);
    close(pipex->outfile);
    if (pipex->id1 > 0 && pipex->id2 == -1)
        waitpid(pipex->id1,NULL,0);
    if (pipex->cmd1)
        free(pipex->cmd1);
    free(pipex->cmd2);
    exit(1);
}
int handle_exit_code(int status)
{
    int final_exit_code;

    final_exit_code = 1;
    if (WIFEXITED(status))
        final_exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        final_exit_code = 128 + WTERMSIG(status);
    else
        final_exit_code = 1;
    return final_exit_code;
    }