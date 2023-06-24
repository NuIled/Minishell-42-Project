#include "../minishell.h"

void update_env(char *var ,char *new_value)
{
    t_env *head;
    head = g_vars->env;
    if(!head || !var || !new_value)
        return ;
    
    while(head)
    {
        if(!ft_strcmp(var,head->var))
        {
            free(head->value);
            head->value = ft_strdup(new_value);
        }
        head = head->next;
    }
}

void add_to_env(char *var ,char *value)
{
    if(!g_vars->env || !var || !value)
        return ;
    addNode(&g_vars->env,createNode(ft_strdup(var),ft_strdup(value)));
}

void append_to_env(char *var ,char *value)
{
    t_env *head;
    head = g_vars->env;
    char *new_value;
    if(!head || !var || !value)
        return ;
    
    while(head)
    {
        if(!ft_strcmp(var,head->var))
        {
            new_value = ft_strjoin(head->value,value);
            free(head->value);
            head->value = new_value;
        }
        head = head->next;
    }
}
int list_size(t_env *head)
{
    int count;
    t_env *ptr;

    if (!head)
        return (0);
    ptr = head;
    count = 0;
    while (ptr)
    {
        count++;
        ptr = ptr->next;
    }
    return (count);
}

char *str_char_str(char *path, char *cmd,char c)
{
    char *s;
    int len;
    int i = -1;
    int j;
    if (!path || !cmd)
        return NULL;
    len = strlen(path) + strlen(cmd) + 2;
    s = (char *)malloc(sizeof(char) * len);
    if(!s)
    {
        perror("malloc failed\n");
        return NULL;
    }
    while (path[++i])
        s[i] = path[i];
    s[i] = c;
    j = i + 1;
    i = -1;
    while (cmd[++i])
        s[j++] = cmd[i];
    s[j] = '\0';
    return s;
}