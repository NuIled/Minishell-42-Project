/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:47:38 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:47:46 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
#define CHECK_H
#include "../minishell.h"

#define SYNTAX_ERR 258

// # define OPERATOR -1
// # define PIPE 0
// # define REDIRECTION 1
// # define WORD 2
// # define HEREDOC 3
// # define LIMITER 4
// # define FILE 5

enum op
{
	OP,
	PIPE,
	RED,
	WRD,
	HD,
	DEL,
	FL
};

typedef struct s_tkn
{
	char *token;
	int type;
	struct s_tkn *next;
} t_tkn;

int     check_line(char *line);
t_tkn   *tkn_it(char **arr);
void    add_tkn(t_tkn **head,char *tkn);
t_tkn   *make_tkn(char *tkn);
int     tkn_type(char *tkn);
char    *get_tkn(char *str,int *n);
int     op_index(char *str);
int     is_q(char c);
int     is_op(char c);
char    **split_it(char *line);
char    *word(char *line,int *n);
int     wc(char *line);
int     in_q(char *line , char q,int i);
int     check_tkns(t_tkn *lst);
void    free_tkn_list(t_tkn *head);
#endif
