#include "minishell.h"

void free_env_list(t_env *env)
{
    t_env *head;

    while (env)
    {
        head = env;
        env = env->next;
        free(head->var);
        free(head->value);
        free(head);
    }
}

void end_it(void)
{
    free_env_list(g_vars->env);
    free(g_vars);
    ft_putstr_fd("exit",STDOUT_FILENO);
    exit(0);
}

void shlvl(void)
{
    char *lvl;

    lvl = get_env_value("SHLVL");
    if(lvl) 
        update_env("SHLVL",ft_itoa(ft_atoi(lvl) + 1));
    else
        add_to_env("SHLVL","1");
}

void add_to_history(char *line)
{
    int i = 0;
    
    while(line[i] && ft_isspace(line[i]) )
        i++;
    if(*line && i < (int)ft_strlen(line))
    {
        add_history(line);
        checker(line);
    } 
    else 
        free(line);
}
void init_g_var(char **env)
{
    g_vars = malloc(sizeof(t_shell));
    g_vars->in  = dup(STDIN_FILENO);
    g_vars->out = dup(STDOUT_FILENO);
    g_vars->err = dup(STDERR_FILENO);
    g_vars->env = getEnv(env);
    g_vars->status = 0;
    shlvl();
    main_signal();
}

void minishell(void)
{
    int i;
    char *line;
    
    i = 0;
    while(1)
    {
        line = readline("minishell>");
        if(!line)
            end_it();
        add_to_history(line);
    }

}

int main(int ac,char **av,char **env)
{
    (void)av;
    if(ac == 1 )
    {
        init_g_var(env);
        minishell();
    }
    else
    {
        printf("Try : ./minishell\n");
        return (1);
    }
}   