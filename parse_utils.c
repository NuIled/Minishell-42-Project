#include "minishell.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int dquotes(char *line, int i);
void free_2d_arr(char **arr);
int squotes(char *line, int i);
int var_quotes(char *s, int i, int d);
int count_args(char *line);
int arg_len(char *line);
char *get_arg(char *line, int *i);
char **split_line_to_args(char *line);

int squotes(char *line, int i)
{
    int flag = 0;
    int j = i;

    while (j >= 0)
    {
        if (line[j] == '\'' && flag == 0 && !dquotes(line, j))
            flag = 1;
        else if (line[j] == '\'' && flag == 1 && !dquotes(line, j))
            flag = 0;
        j--;
    }

    return flag;
}

int dquotes(char *line, int i)
{
    int flag = 0;
    int j = i;

    while (j >= 0)
    {
        if (line[j] == '\"' && flag == 0 && !squotes(line, j))
            flag = 1;
        else if (line[j] == '\"' && flag == 1 && !squotes(line, j))
            flag = 0;
        j--;
    }

    return flag;
}

int var_quotes(char *s, int i, int d)
{
    if (squotes(s, i))
        return 1;
    else if (dquotes(s, i))
    {
        if (d && s[i] == '$')
            return 0;
        return 1;
    }
    return 0;
}