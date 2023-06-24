#include "../minishell.h"

extern int g_exit_status;

void pwd(void)
{
    char pwd[MAX_PATH_LEN];

    getcwd(pwd,MAX_PATH_LEN);
    ft_putstr_fd(pwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    g_vars->status = 0;
}