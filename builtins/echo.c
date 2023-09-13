#include "../minishell.h"

void	own_echo(char *input)
{
	char	**args;
	int		i;
	int		n;

	i = 1;
	n = 0;
	args = ft_split(input, ' ');
	if (args[1])
	{
		while (args[i] && (ft_strncmp(args[i], "-n", 2) == 0)
			&& (check_arg(args[i]) != 1))
		{
			n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		printf("\n");
}
