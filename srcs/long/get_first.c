/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:39:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/19 23:11:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

char			*get_time(struct timespec modified, char *p)
{
	time_t	*the_time;

	the_time = &modified.tv_sec;
	p = ctime(the_time);
	p += 4;
	p[12] = '\0';
	return (p);
}

char			get_type(mode_t st_mode)
{
	if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else if (S_ISFIFO(st_mode))
		return ('p');
	return ('-');
}

char			get_x3(t_file *paths, mode_t st_mode)
{
	if (st_mode & S_IXOTH)
	{
		if (st_mode & S_ISVTX)
			return ('t');
		return ('x');
	}
	if (Y_DIR(paths))
		return ('x');
	if (st_mode & S_ISVTX)
		return ('T');
	return ('-');
}

char			get_x2(t_file *paths, mode_t st_mode)
{
	if (st_mode & S_IXGRP)
	{
		if (st_mode & S_ISGID)
			return ('s');
		return ('x');
	}
	if (Y_DIR(paths))
		return ('x');
	if (st_mode & S_ISGID)
		return ('S');
	return ('-');
}

char			get_x1(t_file *paths, mode_t st_mode)
{
	if (st_mode & S_IXUSR)
	{
		if (st_mode & S_ISUID)
			return ('s');
		return ('x');
	}
	if (Y_DIR(paths))
		return ('x');
	if (st_mode & S_ISUID)
		return ('S');
	return ('-');
}
