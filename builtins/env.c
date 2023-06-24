#include "../minishell.h"

void env(void)
{
    t_env *head;

    head = g_vars->env;
    while(head)
    {
        printf("%s=%s\n",head->var,head->value);
        head = head->next;
    }
    g_vars->status = 0;
}