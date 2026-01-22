/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdalqa <rabdalqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:15:03 by rabdalqa          #+#    #+#             */
/*   Updated: 2026/01/22 17:05:02 by rabdalqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void init_pipe_files(t_pipex *pipex,char **argv)
{
    pipex->infile = read_files(argv[1],0);
    if (pipex->infile < 0)
        ft_putendl_fd("Error: cannot open infile\n", 2);
    pipex->outfile = read_files(argv[4],1);
    if (pipex->outfile < 0)
    {
        ft_putendl_fd("Permission denied ", 2);
        if (pipex->infile >= 0)
            close(pipex->infile);
        exit(1);
    }
}
void init_pipe_commands(t_pipex *pipex,char **argv,char ** envp)
{
    char *cmd_name;
    
    cmd_name = extract_cmd_name(argv[2]);
    pipex->cmd1 = findcommand(cmd_name, envp);
    free(cmd_name);
    if (!pipex->cmd1)
        ft_putendl_fd("Command doesnt exist \n",2);
    cmd_name = extract_cmd_name(argv[3]);
    pipex->cmd2 = findcommand(cmd_name, envp);
    free(cmd_name); 
     if (!pipex->cmd2)
    {
        ft_putendl_fd("Command doesnt exist \n",2);
        if (pipex->cmd1)
            free(pipex->cmd1);
        if (pipex->infile >= 0)    
            close(pipex->infile);
        close(pipex->outfile);
        exit(127);
    }
}
void init_pipe(t_pipex *pipex,char **argv,char ** envp)
{
    init_pipe_files(pipex,argv);
    init_pipe_commands(pipex,argv,envp);
}
char *extract_cmd_name(char *full_cmd)
{
    int i;
    char *cmd_name;

    i = 0;
    if (!full_cmd)
        return NULL;
    while (full_cmd[i] && full_cmd[i] != ' ')
        i++;
    cmd_name = malloc(i + 1);
    if (!cmd_name)
        return NULL;
    i = 0;
    while (full_cmd[i] && full_cmd[i] != ' ')
    {
        cmd_name[i] = full_cmd[i];
        i++;
    }
    cmd_name[i] = '\0';
    return cmd_name;
}

int read_files(char *argv,int i)
{
    if(i == 0)
        return (open(argv, O_RDONLY));
    else
        return (open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

char ** findpaths(char ** envp)
{
    int i;
    char **paths;

    i = 0;
    if (envp == NULL || envp[0] == NULL)
        return NULL;
    while (envp[i] && !ft_strnstr(envp[i], "PATH",4))
        i++;
    if (!envp[i] || !ft_strnstr(envp[i], "PATH",4))
        return NULL;
    paths = ft_split(envp[i] + 5 , ':');
    if (!paths)
        return NULL;
    return paths;
}

char *findcommand_inner(char *path,char **paths,char *cmd)
{
        char *add_slash;
        char   *fullpath;

        add_slash = ft_strjoin(path,"/");
        if (add_slash == NULL)
            return (free_all(paths));
        fullpath = ft_strjoin(add_slash, cmd);
        if (!fullpath)
        {
            free(add_slash);
            return free_all(paths);
        }
		free(add_slash);
		if (access(fullpath, X_OK) == 0)
			return (fullpath);
		free(fullpath);
        return NULL;
}

char * findcommand(char *cmd,char **envp)
{
    int i;
    char **paths;
    char *result;

    i = 0;
    if (!cmd)
        return (NULL);
    if (access(cmd, X_OK) == 0)
        return ft_strdup(cmd);
    paths = findpaths(envp);
    if (paths == NULL || paths[i] == NULL)
        return NULL;
    while(paths[i])
    {
        result = findcommand_inner(paths[i],paths,cmd);
        if (result)
        {
            free_all(paths);
            return result;
        }
		i++;
    }
    return (free_all(paths)); 
}

