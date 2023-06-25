/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:50:22 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:50:25 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_open(int mode, char *filename)
{
	int	o;

	if (mode == 2)
		o = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		o = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (o);
}

void cut_redirect(int *n,char **path,int *i,char *s)
{
	free(*path);
	*path =NULL;
	if(s[*i+1]&&s[*i+1]=='>')
	{
		*n = 2;
		*path = word_after_redir(s,*i+1,0);
		(*i)++;
	}
	else
	{
		*n = 1;
		*path = word_after_redir(s,*i,0);
	}
}