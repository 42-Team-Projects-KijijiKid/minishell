#include "parsing.h"

/// @brief This function returns a bool wether
/// the current type of the node is possible to exist
/// within a redirection chain (eg. so its not operator)
/// !(T_AND, T_PIPE, T_OR)
/// @param  
/// @return true if typ != operator else falses
static bool	check_if_still_possible_redir(t_token *token)
{
	if (!token)
		return (false);
	if (token->type != T_AND && token->type != T_OR
		&& token->type != T_PIPE)
		return (true);
	return (false);
}

/// @brief Opens or creates the outfile
/// and adds the matching redir token
/// @param token 
static void	handle_out_redir(t_token *token)
{
	int	fd;

	fd = open(*token->left->args_2d, O_CREAT | O_WRONLY, 0644);
	printf("FD: %d\n", fd);
	if(fd == -1)
		ft_error("Open error:", __FILE__, __LINE__, 38);
	assign_redir_node_values(token->back, OUT_FD, fd);
}

/// @brief This function goes through the tokens
/// with back and left pointers
/// @param token first occurrence token of a redirection for a
/// command
static void	handle_in_redir(t_token *token)
{
	t_token	*command_node;
	t_token	*redir_node;
	int		fd;

	command_node = token; // We are storing the command node for the redirection
	while (command_node->back->type != T_TEXT && token)//Could be that the indirection for a command is after various out redirections so to assign to the command we need to go as far as possible to the left
		command_node = command_node->back;
	while (check_if_still_possible_redir(token) && token)
	{
		if (token->type == T_IN_RDR)
		{
			redir_node = token->left;
			fd = ft_open(*redir_node->args_2d, O_RDONLY);
		}
		token = token->left;
	}
	assign_redir_node_values(command_node, IN_FD, fd);
}

void	handle_io_redir(t_token *token)
{
	if (!token->back || !token->left)
		ft_error("I/O redirection error:", __FILE__, __LINE__, 82);
	if (token->type == T_IN_RDR)
		handle_in_redir(token);
	if (token->type == T_OUT_RDR)
		handle_out_redir(token);
}
