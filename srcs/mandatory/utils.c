/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:32:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/09 20:32:54 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_slash(char *path, char *cmd)
{
	size_t	pathlen;
	size_t	cmdlen;
	char	*var;
	size_t	i;
	size_t	x;

	pathlen = ft_strlen(path);
	cmdlen = ft_strlen(cmd);
	var = ft_calloc(pathlen + cmdlen + 2, 1);
	if (!var)
		return (NULL);
	i = -1;
	while (path[++i])
		var[i] = path[i];
	var[i++] = '/';
	x = -1;
	while (cmd[++x])
		var[i + x] = cmd[x];
	var[i + x] = '\0';
	return (var);
}
