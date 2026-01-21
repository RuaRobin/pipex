#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include "./libft/libft.h"

int read_files(char *argv,int i)
{
    if(i == 0)
        return (open(argv, O_RDONLY));
    else
        return (open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}
char * findcommand(char *cmd,char **envp)
{
    int i;
    char **paths;
    char *add_slash;
    char *path;
    i = 0;
    if (envp == NULL | envp[0] == NULL || cmd == NULL)
        return NULL;
    if (access(cmd, F_OK) == 0)
			return (cmd);
    while (ft_strnstr(envp[i], "PATH",4) ==0)
        i++;
    if (ft_strnstr(envp[i], "PATH",4) == 0)
        return NULL;
    paths = ft_split(envp[i] + 5 , ':');
    i = 0;
    if (paths == NULL || paths[i] == NULL)
    {
        free(paths);
        return NULL;
    }
    while(paths[i])
    {
        add_slash = ft_strjoin(paths[i],'/');
        if (add_slash == NULL)
     {
            free_all(paths);
            return NULL;
    }
        path = ft_strjoin(add_slash, cmd);
        if (!path)
        {
            free_all(paths);
            free(add_slash);
            return NULL;
        }
		free(add_slash);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
    }  
    return NULL;
}
