#include "./minishell.h"


char *word_after_redir(char *s,int i,int rd )
{
    int j;
    int k;

    k = i + rd;
    if(!s[k])
        return NULL;
    while(s[k] && ft_isspace(s[k]))
        k++;
    while(s[k] && (s[k] == '<' || s[k] == '>') && !var_quotes(s,k,0))
        k++;
    j = k;
    while(s[j] && !ft_isspace(s[j]))
        j++;
    return (ft_substr(s, k, j - k));
}

char **get_delimiter(char *delimiter)
{
    char **arr;
    arr = malloc(sizeof(char *) * 2);
    if(!arr)
        return NULL;
    arr[0]= remove_quotes(delimiter);
    arr[1] = NULL;
    return arr;
}

t_heredoc *init_h(void)
{
    t_heredoc *hd = malloc(sizeof(t_heredoc));
    if(!hd)
        return (perror("malloc error\n"),NULL);
   hd->path= NULL;
   hd->i=-1;
   hd->heredoc=NULL;
   hd->temp =NULL;
   hd->is_open =-1;
return hd;
}

int is_heredoc(char *s,char ***hd,int *i,char **delimiter)
{
   // if(*delimiter)
        //free(*delimiter),*delimiter = NULL;
    if(s[*i + 1] && s[*i + 1] == '<')
    {
        *hd = get_delimiter(word_after_redir(s, *i + 1, 1));
        *i += 2;
        return 1;
    }
    return 0;
}
int	quote_heredoc(char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
void bool_heredoc(char **del,int i,int *q,char **tmp)
{
    if(!del[i]&& !*tmp)
        *tmp = ft_strdup("");
    if(!del[i])
        *q = quote_heredoc(del[i]);
    else
        *q = 0; 
}

char *expand_heredoc(char *s,char *prev,int in_q)
{
    char *tmp1;
    char *tmp2;
    char *str;

    tmp1= NULL;
    tmp2 =NULL;
    str =NULL;
    if(!in_q)
    {
        tmp2 = expand(s);
        tmp1 = ft_strjoin(tmp2,"\n");
    }
    else
        tmp1 = ft_strjoin(s,"\n");
    if(prev)
        str = ft_strjoin(prev,tmp1);
    else 
        str = ft_strdup(tmp1);
    free(tmp1);
    if(tmp2)
        free(tmp2);
    if(prev)
        free(prev);
    return str;
}

char *heredoc(char **del,t_cmd *cmd,char *s)
{
    int i,q;
    char *line;
    q =1;
    i = 0;
    char *tmp;
    while(del[i])
    {
        line = readline("> ");
        if(!line)
            break;
        tmp = remove_quotes(del[i]);
        if(!ft_strcmp(line, tmp))
            i++;
        if(del[i])
            s = expand_heredoc(line,s,q);
        free(line);
        free(tmp);
    }
    free_2d_arr(del);
    cmd->heredoc = 1;
    return s;
}