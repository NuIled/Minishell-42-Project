#include "../minishell.h"

static int is_digit(char *s)
{
    while(*s)
    {
        if(!ft_isdigit(*s))
            return (0);
        s++;
    }
    return (1);
}

void ft_exit(t_cmd *cmd)
{
    ft_putstr_fd("exit\n",STDERR_FILENO);
    if(!cmd->argv[1])
       g_vars->status = 0, exit(g_vars->status); 
   else if(cmd->argv[1] && !is_digit(cmd->argv[1]))
    {
        ft_putstr_fd("minishell: exit:",STDERR_FILENO);
        ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required", STDERR_FILENO);
        g_vars->status = 255;
        exit(g_vars->status);
    }
    else if(cmd->argv[2])
    {
        ft_putstr_fd("minishell: ",STDERR_FILENO);
        ft_putstr_fd("exit: ",STDERR_FILENO);
        ft_putstr_fd("too many arguments\n", STDERR_FILENO);
        g_vars->status = 1;
    }
    else 
        g_vars->status = ft_atoi(cmd->argv[1]), exit(g_vars->status);
}