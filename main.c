/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdalqa <rabdalqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:15:11 by rabdalqa          #+#    #+#             */
/*   Updated: 2026/01/22 16:15:11 by rabdalqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc != 5)
    {
        ft_putendl_fd("Not enough arguments, please follow the input format as following: \n./pipex file1 cmd1 cmd2 file2",2);
        return 1;
    }
    init_pipe(&pipex,argv,envp);
    pipex.id1 = -1;
    if(pipe(pipex.fd) == -1)
        clean_all("pipe", &pipex);
    if (pipex.infile >= 0 && pipex.cmd1)
    {
        pipex.id1 = fork();
        execute_cmd1(&pipex,argv[2],envp);
        close(pipex.infile);
    }
    pipex.id2 = fork();
    execute_cmd2(&pipex,argv[4],envp);
    clean_all_final(&pipex,"close");
    if (pipex.id1 >0)
        waitpid(pipex.id1, &(pipex.status1),0);
    waitpid(pipex.id2, &(pipex.status2),0);
    clean_all_final(&pipex,"free");
    return handle_exit_code(pipex.status2);
}


