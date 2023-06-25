#include "minishell.h"

int     contain_char(char *s,char c)
{
    if(!s)
        return (0);
    while(*s)
    {
        if(*s == c)
            return (1);
        s++;
    }
    return (0);
}

char *get_path(char *cmd)
{
    char **paths;
    int i;
    char *envPath;
    char *tmp;
    
    i = 0;
    if(contain_char(cmd,'/'))
        return(ft_strdup(cmd));
    envPath = get_env_value("PATH"); 
    if(!envPath)
        return (NULL);
    paths = ft_split(envPath,':');
    if(!paths)
        return (NULL);
    while(paths[i])
    {
        tmp = str_char_str(paths[i],cmd,'/');
        if(!access(tmp, X_OK))//0 is good
        {
            free_2d_arr(paths);
            return (tmp);
        }
        free(tmp);
        i++;
    } 
    free_2d_arr(paths);
    return (cmd);
}
char *get_path2(char *cmd)
{
    char **paths;
    int i;
    char *envPath;
    char *tmp;
    
    i = 0;
    if(contain_char(cmd,'/'))
        return(ft_strdup(cmd));
    envPath = get_env_value("PATH"); 
    if(!envPath)
        return (NULL);
    paths = ft_split(envPath,':');
    if(!paths)
        return (NULL);
    while(paths[i])
    {
        tmp = str_char_str(paths[i],cmd,'/');
        if(!access(tmp, X_OK))//0 is good
        {
            free_2d_arr(paths);
            return (tmp);
        }
        free(tmp);
        i++;
    } 
    free_2d_arr(paths);
    return (NULL);
}

void	 free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_2d_arr(tmp->argv);
		if (tmp->in)
			free(tmp->in);
		if (tmp->out)
			free(tmp->out);
		free(tmp);
	}
}

int is_builtin(char *cmd)
{
    if(!cmd)
        return 0;
    if(!ft_strcmp(cmd,"echo"))
        return (1);
    else if(!ft_strcmp(cmd,"cd"))
        return (1);
    else if(!ft_strcmp(cmd,"pwd"))
        return (1);
    else if(!ft_strcmp(cmd,"export"))
        return (1);
    else if(!ft_strcmp(cmd,"unset"))
        return (1);
    else if(!ft_strcmp(cmd,"env"))
        return (1);
    else if(!ft_strcmp(cmd,"exit"))
        return (1);
    return 0;
}

void exec_builtin(t_cmd *cmd)
{
    if(!ft_strcmp(cmd->argv[0],"echo"))
        echo(cmd);
    else if(!ft_strcmp(cmd->argv[0],"cd"))
        cd(cmd);
    else if(!ft_strcmp(cmd->argv[0],"pwd"))
        pwd();
    else if(!ft_strcmp(cmd->argv[0],"export"))
        export(cmd);
    else if(!ft_strcmp(cmd->argv[0],"unset"))
        unset(cmd);
    else if(!ft_strcmp(cmd->argv[0],"env"))
        env();
    else if(!ft_strcmp(cmd->argv[0],"exit"))
        ft_exit(cmd);
    update_last_cmd(cmd->argv[0]);
}

void update_last_cmd(char *last_cmd)
{
    if(!access(last_cmd, X_OK))
    {
    remove_env_node("_");
    add_to_env("_",last_cmd);
    free(last_cmd);
    }
}