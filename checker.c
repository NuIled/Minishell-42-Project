#include "minishell.h"

int valid_pipe(char *line,int i)
{
    int j = 1;
    while (line[i - j])
    {
        if(ft_isalnum((int)line[i - j]))
            return 1;
        j++;
    }
    return 0;
}

void pipe_check(char *line,int i,int *error)
{
    int j;
    int flag;

    j = 1;
    flag = 0;
    if(line[i] == '|')
    {
        if(consecutive_char_count(&line[i],'|') > 1)
            *error = 1;
        while (line[i + j])
        {
            if(!ft_strchr("<>|",line[i + j]))
                flag = 1;
            j++;
        }
        if((!*error && !flag) || !(valid_pipe(line,i)))
            *error = 2;
    }
}

void check_pipe(char *line)
{
    int i;
    int error;
    char c;

    i = -1;
    error = 0;
    c = '\0';
    while (line[++i])
    {   
        if(!c && (line[i] =='\''||line[i] == '\"'))
            c = line[i];
        else if(c == line[i])
            c = '\0';
        if(c)
            continue;
        else
            pipe_check(line,i,&error);
    }
    if(!error)
        parse(line);
    else if (error == 1)
        ft_putstr_fd("syntax error: unexpected token ||\n",STDERR_FILENO);
    else if (error == 2)
        ft_putstr_fd("syntax error: unexpected token near '|'\n",STDERR_FILENO);
}
void validate_redirection(char *line ,int *error)
{
    int i;
    int j;
    int flag;

    i = 0;
    flag =0;
    j = (consecutive_char_count(line,'<') + consecutive_char_count(line,'>'));
    if(consecutive_char_count(line,'<') > 2 || consecutive_char_count(line,'>') > 2)
        *error = 1;
    else
    {
        while(line[i + j])
        {
            if(!ft_strchr("<>|",line[i + j]))
                flag = 1;
            j++;
        }
    }
    if(!flag && !*error)
        *error = 2;
}

void check_redirection(char *line)
{
    int i;
    int error;

    i =-1;
    error =0;
    while (line[++i])
       if(line[i] == '<' || line[i]== '>')
            validate_redirection(&line[i],&error);
    if(!error)
        check_pipe(line);
    else if(error == 1)
        ft_putstr_fd("minishell: syntax error ,unexpected redirection op \n",STDERR_FILENO);
    else if(error == 2)
        ft_putstr_fd("minishell: minishell: syntax error\n",STDERR_FILENO);
}

void checker(char *line)
{
    int i;
    char c;

    i = -1;
    c = '\0';

    while (line[++i])
    {
        if (!c && (line[i] == '\'' || line[i] == '\"'))
            c = line[i];
        else if (line[i] == c)
            c = '\0';
    }
    if (c)
        ft_putstr_fd("Syntax error: unclosed quotes\n", STDERR_FILENO);
    else
        check_redirection(line);
}
