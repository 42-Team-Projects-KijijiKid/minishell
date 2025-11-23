#include "minishell.h"

static int	env_cmp(char *s1, char *s2)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if (len_1 < len_2)
		return (ft_strncmp(s1, s2, len_2));
	else
		return (ft_strncmp(s1, s2, len_1));
}

static char	**sort_env(t_minishell *shell)
{
	char	**env_array;
	char	**sorted_env;
	int		inside_idx;
	int		outside_idx;
	int		x;

	env_array = env_list_to_2d();
	sorted_env = fti_malloc(sizeof(char *) * shell->env.size, TEMPORARY);
	outside_idx = 0;
	while (env_array[outside_idx] != NULL)
	{
		x = 0;
		inside_idx = 0;
		while (env_array[inside_idx] != NULL)
		{
			if (env_cmp(env_array[outside_idx], env_array[inside_idx]) > 0)
				x++;
			inside_idx++;
		}
		sorted_env[x] = env_array[outside_idx];
		outside_idx++;
	}
	return (sorted_env);
}

	// int		in_idx;
	// int		out_idx;
	// int		count;
	// char	**sorted;

	// sorted = gc_calloc(env_get_size(env) + 1, sizeof(char *));
	// out_idx = 0;
	// while (env[out_idx] != NULL)
	// {
	// 	count = 0;
	// 	in_idx = 0;
	// 	while (env[in_idx] != NULL)
	// 	{
	// 		if (h_env_cmp(env[out_idx], env[in_idx]) > 0)
	// 			count++;
	// 		in_idx++;
	// 	}
	// 	sorted[count] = env[out_idx];
	// 	out_idx++;
	// }
	// return (sorted);

void	print_sorted_exported(void)
{
	t_minishell	*shell;
	char		**sorted_env;

	shell = minishell_get();
	sorted_env = sort_env(shell);
	while (*sorted_env)
	{
		printf("declare -x %s\n", *sorted_env);
		sorted_env++;
	}
}
