#include "minishell.h"



int     cmd_list_size(t_cmd *head)
{
    int i = 0;

    while (head)
    {
        i++;
        head = head->next;
    }
    return i;
}

void dupping(void)
{
    dup2(g_vars->in,STDIN_FILENO);
    dup2(g_vars->out,STDOUT_FILENO);
    dup2(g_vars->err,STDERR_FILENO);
}

void free_cmd_list(t_cmd *head)
{
    t_cmd *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free_array(tmp->argv);
        if(tmp->in)
            free(tmp->in);
        if(tmp->out)
            free(tmp->out);
        free(tmp);
    }
}
void exc_dup(t_cmd *cmd)
{
    int fd_in;
    int fd_out;

    if(cmd->in && !cmd->heredoc)
    {
        fd_in = open(cmd->in,O_RDONLY,0777);
        if(fd_in < 0)
            exit (1);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if(cmd->out)
    {
        fd_out = open(cmd->out, O_WRONLY | O_CREAT | (
					O_TRUNC * (cmd->append != 2)) | (
					O_APPEND * (cmd->append == 2)), 0777);
        if(fd_out < 0)
            exit(1);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}
void exc_err(char *s,char *msg)
{
    ft_putstr_fd("minishell: ",STDERR_FILENO);
    ft_putstr_fd(s,STDERR_FILENO);
    ft_putchar_fd(':',STDERR_FILENO);
    ft_putstr_fd(msg,STDERR_FILENO);
    ft_putchar_fd('\n',STDERR_FILENO);
}
void x_cmd(t_cmd *cmd)
{
    char **env_arr;
    char *path;
    if(!cmd->argv || !cmd->argv[0])
        exit(0);
    if(is_builtin(cmd->argv[0]))
    {
        exec_builtin(cmd);
        exit(g_vars->status);
    }
    env_arr = lst_to_arr_env(g_vars->env);
    path = get_path(cmd->argv[0]);
    update_last_cmd(path);
    if(!path)
        path = cmd->argv[0];
    execve(path,cmd->argv,env_arr);
    if(errno != 14 || ft_strchr(cmd->argv[0],'/'))
        exc_err(cmd->argv[0],strerror(errno));
    else
        exc_err(cmd->argv[0],"command not found");
    free(path);
    free_array(env_arr);
    if(errno == 2 || errno == EACCES)
        exit((errno == 2) * 127 + (errno == EACCES) * 126);
    exit (1);
}

pid_t exc_one(t_cmd *command,int i)
{
    pid_t id;
    if(i == 0 && is_builtin(command->argv[0]))
    {
        exc_dup(command);
        exec_builtin(command);
        dupping();
        return (-1);
    }
    id = fork();
    if(id < 0)
        return -1;
    if(id)
        return id;
    
    exc_dup(command);
    x_cmd(command);
    return (id);
}

pid_t exc_heredoc(t_cmd *cmd)
{
    pid_t pid;
    int p[2];

    if(pipe(p) < 0)
        return (-1);
    pid = fork();
    if(pid)
    {
        dup2(p[0],STDIN_FILENO);
        close(p[0]);
        close(p[1]);
        return (pid);
    }
    if(!cmd->in)
        cmd->in = ft_strdup("");
    pid = write(p[1],cmd->in,ft_strlen(cmd->in));
    close(p[0]);
    close(p[1]);
    exit(pid);
    return(pid);
}

pid_t	exc_pipe(t_cmd *cmd)
{
	pid_t	pid;
	int		files[2];

	if (pipe(files) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
	{
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		close(files[1]);
		return (pid);
	}
	dup2(files[1], STDOUT_FILENO);
	close(files[0]);
	close(files[1]);
	exc_dup(cmd);
	x_cmd(cmd);
	return (pid);
}

int exc(t_cmd *cmd,int i)
{
    int id;
    if(cmd->heredoc)
        id = exc_heredoc(cmd);
    if(!cmd->next)
    {
        dup2(g_vars->out,STDOUT_FILENO);
        id = exc_one(cmd,i); 
        dup2(g_vars->in,STDIN_FILENO);
        return (id);
    }
    return(exc_pipe(cmd));
}

void exc_wait(t_cmd *cmd, int n)
{
	int	status;
    int	i;

	if (n > 1 || (cmd && !is_builtin(cmd->argv[0])))
	{
		i = -1;
		while (++i < n)
			waitpid(g_vars->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_vars->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			printf("%d\n", WTERMSIG(status));
			g_vars->status = 128 + WTERMSIG(status);
		}
	}
	g_vars->pid_count = 0;
	free(g_vars->pids);
}

void execute(t_cmd *cmd)
{
    int i,n;
    t_cmd *head;
    head = cmd;
    i = -1;
    n = cmd_list_size(cmd);
    g_vars->pids = ft_calloc(n , sizeof(int));
    if(!cmd || !n || !g_vars->pids)
        return;
    while (++i < n)
    {  
        g_vars->pids[i] = exc(cmd,i);
        if(cmd->next)
            cmd = cmd->next;    
    }
    update_last_cmd(get_path(cmd->argv[0]));
    exc_wait(cmd,n);
    free_cmd_list(head);
    dupping();
}