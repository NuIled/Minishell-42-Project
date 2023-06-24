#include "../minishell.h"
static int nflag(char *arg);
static void echo_args(char **argv,int fd);

void echo(t_cmd *cmd)
{
    int nl = 1;
    int i = 1;
    if(!cmd->argv[i])
    {
        ft_putstr_fd("\n",STDOUT_FILENO);
        return;
    }
    while(cmd->argv[i] && nflag(cmd->argv[i]))
    {
        nl = 0;
        i++;
    }
    echo_args(&cmd->argv[i],STDOUT_FILENO);
    if(nl)
        ft_putstr_fd("\n",STDOUT_FILENO);
    g_vars->status = 0;
}

static int nflag(char *arg)
{
    int i = 1;
    if(!strcmp(arg ,"-n"))
        return (1);
    if(arg[0] != '-')
        return 0;
    while(arg[i])
    {
        if(arg[i]!='n')
            return 0;
        i++;
    }
    return 1;
}
static void echo_args(char **argv,int fd)
{
    int i = 0;
    while(argv[i])
    {
        ft_putstr_fd(argv[i],fd);
        if(argv[i + 1])
            ft_putstr_fd(" ",fd);
        i++;
    }
}