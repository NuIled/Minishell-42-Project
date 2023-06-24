#include "./minishell.h"

int set_stdin(char **dlmtr,t_cmd *cmd,char *path,int n)
{
    char *tmp;

    if(dlmtr && !path)
    {
        tmp = heredoc(dlmtr,cmd,NULL);
        if(!tmp)
            return -2;
        cmd->in = tmp; 
    }
    else
    {
        cmd->in = path;
        cmd->append = n;
        cmd->heredoc = 0;
    }
    return n;
}

int actual_file(int *n,char **path,int *o,char **tmp)
{
    *n = 1;
    *path = remove_quotes(*tmp);
    *o = open(*path,O_RDONLY);
    if(*o < 0)
    {
        ft_putstr_fd(*path,STDERR_FILENO);
        ft_putstr_fd(" : cannot access file or directory\n", STDERR_FILENO);
        return (-1);
    }
    return (0);
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

int redir_input(char *s,t_cmd *command , char *tmp,int mode)
{
    t_heredoc *hd;
    int err;

    hd = init_h();
    err = mode;
    while(s[++(hd->i)])
    {
        if(hd->is_open > 0)
            close(hd->is_open);
        if(s[hd->i] == '<' && !var_quotes(s,hd->i,0))
        {
            if(is_heredoc(tmp, &hd->heredoc, &hd->i, &hd->path))
                err = set_stdin(hd->heredoc,command,hd->path,mode);
            else
            {
                hd->temp = word_after_redir(s, hd->i, 0);
                if(actual_file(&mode,&hd->path,&hd->is_open,&hd->temp) == -1)
                    return -1;
                err = set_stdin(hd->heredoc,command,hd->path,mode);
            }
        }
    }
    free(hd);
    return (err);
}

int	ft_open(int mode, char *filename)
{
	int	o;

	if (mode == 2)
		o = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		o = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (o);
}

int redir_output(char *s,t_cmd *command,char *path,int n)
{
    int i;
    int o;

    i = 0;
    o = -1;
    while (s[i])
    {
        if(o > 0)
            close(o);
        if(s[i]== '>' && !var_quotes(s,i,0))
        {
            cut_redirect(&n, &path , &i, s);
            o = ft_open(n,path);
            if(o < 0)
            {
                ft_putstr_fd(path, STDERR_FILENO);
				ft_putstr_fd(" : cannot access file or directory\n", STDERR_FILENO);
				return (-1);

            }
        }
        i++;
    }
    command->append = n;
    command->out = path;
    return (n);
}