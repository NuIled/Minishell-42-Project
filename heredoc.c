/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:51:09 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:51:12 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while(s[k] && ft_isspace(s[k]))
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
	arr[0]= delimiter;
	arr[1] = NULL;
	return (arr);
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
// void bool_heredoc(char **del,int i,int *q,char **tmp)
// {
//     if(!del[i]&& !*tmp)
//         *tmp = ft_strdup("");
//     if(!del[i])
//         *q = quote_heredoc(del[i]);
//     else
//         *q = 0; 
// }

// char *expand_heredoc(char *s,char *prev,int in_q)
// {
//     char *tmp1;
//     char *tmp2;
//     char *str;

//     tmp1= NULL;
//     tmp2 =NULL;
//     str =NULL;
//     if(!in_q)
//     {
//         tmp2 = expand(s);
//         tmp1 = ft_strjoin(tmp2,"\n");
//     }
//     else
//         tmp1 = ft_strjoin(s,"\n");
//     if(prev)
//         str = ft_strjoin(prev,tmp1);
//     else 
//         str = ft_strdup(tmp1);
//     free(tmp1);
//     if(tmp2)
//         free(tmp2);
//     if(prev)
//         free(prev);
//     return str;
// }

int xpnd(char **del)
{
	if(contain_char(*del,'\'') || contain_char(*del ,'\"'))
	{
		*del = remove_quotes(*del);
		return (0);
	}
	return (1);
}

char *heredoc(char **del,t_cmd *cmd,char *s)
{
	int i;
	int exp;
	char *line= NULL;
	char *line_nl=NULL;
	char *joined =NULL;

	i = 0;
	exp = xpnd(del);
	while(del[i])
	{
		line = readline("> ");
		if(!line)
			break;
		if(exp && *line)
			line = expand(line);
		line_nl = ft_strjoin(line ,"\n");
		if(!ft_strcmp(line, del[i]))
			i++;
		if(del[i])
			joined = store_line(joined,line_nl);
		free(line);
		free(line_nl);
	}
	free_array(del);
	cmd->heredoc = 1;
	return joined;
}
