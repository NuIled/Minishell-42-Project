#include "../minishell.h"

void free_array(char **array)
{
    size_t i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
char **sort_env(char **env)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (env[i])
    {
        j = i + 1;
        while (env[j])
        {
            if (ft_strcmp(env[i], env[j]) > 0)
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
            j++;
        }
        i++;
    }
    return env;
}

void print_env(char **env)
{
    int i;
    int j;
    int dq;
    i = 0;
    while (env[i])
    {
        dq = 1;
        j = 0;
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        while (env[i][j])
        {
            ft_putchar_fd(env[i][j], STDOUT_FILENO);
            if (env[i][j] == '=' && dq)
            {
                ft_putchar_fd('\"', STDOUT_FILENO);
                dq = 0;
            }
            j++;
        }
        if (!dq)
            ft_putstr_fd("\"\n", STDOUT_FILENO);
        i++;
    }
}

int valid_export(char *s)
{
    int i = 0;
    //int eq = 0;
    if (!ft_isalpha(s[i]) && s[i] != '_')
        return (-1);
    i++;
    while (s[i])
    {
        if (s[i] == '=')
            return (i + 1);
        if (s[i] == '+' && s[i + 1] == '=')
            return (i + 2);
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (-1);
        i++;
    }
    return (i);
}
char *get_var(char *s)
{
    int i = 0;
    char *var;

    if (!s)
        return (NULL);
    var = NULL;
    while (s[i])
    {
        if (s[i] == '=')
            break;
        if (s[i] == '+' && s[i + 1] && s[i + 1] == '=')
            break;
        i++;
    }
    var = ft_calloc(i + 1,sizeof(char));
    ft_memcpy(var, s, i);
    return var;
}
char *get_value(char *s, int i)
{
    int len;
    char *buff;

    len = ft_strlen(s);
    buff = NULL;
    if (!s[i])
        return (NULL);
    if (s[i] == '+')
        i++;
    if (!s[i + 1]) // export gg+=
        return (ft_strdup(""));
    buff = ft_calloc(sizeof(char) , (len - i + 1));
    ft_memcpy(buff, s + i + 1, len - i);
    return buff;
}