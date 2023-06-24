#include "minishell.h"

void init_command(t_cmd *command)
{
    command->in = NULL;
    command->out = NULL;
    command->heredoc = 0;
    command->append = 0;
    command->argv = NULL;
    command->next =NULL;
}

t_cmd *line_to_cmd(char *line)
{
    t_cmd *command;
    command = malloc(sizeof(t_cmd));
    if(!command)
        return NULL;
    init_command(command);
    tokenize(line,command);
    return command; 
} 

void parse(char *line)
{
    t_cmd *command;
    command = line_to_cmd(line);
    if(!command)
        ft_putstr_fd("malloc failed in parse()\n",STDERR_FILENO);
   else
      execute(command);
}