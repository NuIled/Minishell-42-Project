#include "minishell.h"
int list_size(t_env *head);
void free_2d_arr(char **arr);
t_env *createNode(char *var, char *val);

void addNode(t_env **head, t_env *node);
t_env *getEnv(char **env);

void free_2d_arr(char **arr)
{
    size_t i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

t_env* createNode(char* var, char* value)
{
    t_env* newNode = (t_env*)malloc(sizeof(t_env));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    newNode->var = var;
    newNode->value = value;
    newNode->next = NULL;
    
    return newNode;
}

void addNode(t_env** head, t_env* newNode)
{
    t_env* temp;
    if (*head == NULL)
        *head = newNode;
    else {
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

t_env *getEnv(char **env)
{
    int     i;
    t_env   *e;
    char    **arr;

    e   = NULL;
    arr = NULL;
    i = -1;

    while (env[++i])
    {
        arr = ft_split(env[i], '=');
        if (!arr)
            return NULL;
        if (arr[1])
            addNode(&e, createNode(ft_strdup(arr[0]),  ft_strdup(arr[1])));
        else
            addNode(&e, createNode(ft_strdup(arr[0]),  ft_strdup("")));
        free_2d_arr(arr);
    }
    return (e);
}
char *get_env_value(char *var)
{
    t_env *tmp;

    tmp = g_vars->env;
    if(!tmp)
        return NULL;
    while (tmp)
    {
        if(!ft_strcmp(tmp->var,var))
            return (tmp->value);
        tmp= tmp->next;
    }
    return NULL;
}