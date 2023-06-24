#include "minishell.h"

int count_words(char *line,char c)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while(line[i])
    {
        while (line[i] == c)
            i++;
        if(((line[i] != c && ((!var_quotes(line, i, 0) &&(line[i] != '\"' &&\
        line[i] != '\'')) || (var_quotes(line ,i ,0) && (line[i] == '\''|| line[i] =='\"'))))) && line[i])
        count++;
        while((line[i] != c || var_quotes(line,i,0)) && line[i])
            i++;
    }
    return count;
}
char *makeWord(char *line,char c)
{
    int i = 0;
    char *s;

    while(line[i] && (line[i] != c || var_quotes(line,i,0)))
    i++;
    s = ft_calloc (i + 1,sizeof(char));
    if (!s)
        return NULL;
    ft_strlcpy(s, line, i + 1);
    return s;
}

char **split_tokens(char *line,char c)
{
    int i;
    int count;
    char **arr;

    i = -1;
    if(!line)
        return NULL;
    count = count_words(line,c);
    arr = ft_calloc(count +1,sizeof(char *));
    if(!arr)
        return NULL;
    while(++i < count)
    {
        while(*line == c && !var_quotes(line,0,0))
            line++;
        arr[i] = makeWord(line,c);
        if(!arr[i])
            return(free_2d_arr(arr),NULL);
        line +=ft_strlen(arr[i]);
    }
    arr[i] = NULL;
    return arr;
}


void tokenize(char *line , t_cmd *command)
{
    int i;
    char **arr;

    i = 0;
    arr = split_tokens(line,'|');
    if(!arr)
        init_command(command),command->argv = malloc(1),command->argv = NULL;
    while(arr[i])
    {
        fill_command(arr[i],command);
        if(arr[i + 1])
        {
            command->next = malloc(sizeof(t_cmd));
            if(!command->next)
                return;
            init_command(command->next);
        }
        command = command->next;
        i++;
    }
    free(arr);
}