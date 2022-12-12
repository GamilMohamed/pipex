/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:11:04 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/09 20:43:35 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_firstword(char *s)
{
	int	i;
	int	start;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	start = i;
	while (s[i] && ft_isalpha(s[i]))
		i++;
	return (ft_substr(s, start, i));
}

void	ft_printstruct(t_args *args)
{
	int		i;
	int		j;
	char	**cmd;

	i = -1;
	ft_printf("env=");
	while (args->env[++i])
		ft_printf("%g%s%0:", args->env[i]);
	ft_printf("\n");
	ft_printf("infile=%y\t\t%s%0\n", args->infile);
	i = -1;
	while (args->cmds[++i])
	{
		cmd = ft_split(args->cmds[i], ' ');
		j = 0;
		ft_printf("cmd[%i]=%m\t\t%s%0\n", i, cmd[0]);
		while (cmd[++j])
			ft_printf("flags[%i]=%m\t%s%0\n", j, cmd[j]);
		ft_freetab((void **)cmd);
	}
	ft_printf("outfile=%y\t%s%0\n", args->outfile);
}
