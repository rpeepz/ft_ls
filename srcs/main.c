/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 05:45:06 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				main(int ac, char **av)
{
	char			flags;
	t_file			*paths;

	flags = 0;
	if (ac > 1)
	{
		if ((flags = get_flags(av, 0, 0, 0)) == '~')
			IF_RETURN(write(1, USAGE, 37), 1);
		if (!(paths = get_dirs(av, 1, 0)))
			IF_RETURN(write(1, MALLOC_ERR, 17), 1);
	}
	else
	{
		if (!(paths = t_fileinit(".", "", 0)))
			IF_RETURN(write(1, MALLOC_ERR, 17), 1);
	}
	if (!paths->next)
		paths->index = 0;
	else
		t_file_mergesort(&paths, flags, 1);
	if (ft_ls(paths, flags |= 0x1))
		IF_RETURN(!t_filedel(&paths) && write(1, MALLOC_ERR, 17), 1);
	return (0);
}

char			*define_color(t_file *paths)
{
	IF_RETURN(Y_DIR(paths), BGRN);
	IF_RETURN(S_ISLNK(paths->info.st_mode), MAG);
	IF_RETURN(paths->info.st_mode & S_IEXEC, RED);
	IF_RETURN(get_type(paths->info.st_mode) == 'b', UCYN);
	IF_RETURN(get_type(paths->info.st_mode) == 'c', UYEL);
	return (NOCOL);
}
