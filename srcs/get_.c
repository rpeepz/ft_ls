/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 01:54:58 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/18 03:52:24 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		copy_print(char *buf, char *msg, char attach, int len)
{
	ft_strncpy(buf, msg, (len = LEN(msg)));
	ft_strncpy(buf + len++, &attach, 1);
	ft_strncpy(buf + len++, "\n", 1);
	ft_putnstr(buf, len);
	return (1);
}

char			get_flags(char **av, char mask, int i, int j)
{
	char	buf[30];

	while ((av[++i]) && av[i][0] == '-' && (j = 1))
	{
		while (IS_FLAG(av[i][j]))
		{
			IF_THEN(av[i][j] == 'R' && (j++), mask |= 1UL << 0);
			IF_THEN(av[i][j] == 'a' && (j++), mask |= 1UL << 1);
			IF_THEN(av[i][j] == 'l' && (j++), mask |= 1UL << 2);
			IF_THEN(av[i][j] == 'r' && (j++), mask |= 1UL << 3);
			IF_THEN(av[i][j] == 't' && (j++), mask |= 1UL << 4);
			IF_RETURN(av[i][j] == '-' && copy_print(buf,
			"ft_ls: illigal option -- ", av[i][j], 0), mask |= 1UL << 6);
		}
		while (ISNT_FLAG(av[i][j]))
		{
			IF_BREAK(!av[i][j]);
			IF_BREAK(av[i][j] == '-' && !av[i][j + 1]);
			IF_RETURN(av[i][j] == '-' && av[i][j + 1] && copy_print(buf,
			"ft_ls: illigal option -- ", '-', 0), mask |= 1UL << 6);
			IF_RETURN(ISNT_FLAG(av[i][j]) && copy_print(buf,
			"ft_ls: illigal option -- ", av[i][j], 0), mask |= 1UL << 6);
		}
	}
	return (mask);
}

t_file			*t_filedel(t_file *file)
{
	if (file->path != NULL)
		free(file->path);
	if (file->name != NULL)
		free(file->name);
	if (file->full_path != NULL)
		free(file->full_path);
	if (file->next != NULL)
		t_filedel(file->next);
	else
		free(file);
	return (NULL);
}

t_file			*t_fileinit(void)
{
	t_file	*file;

	if (!(file = ft_memalloc(sizeof(t_file))))
		return (NULL);
	if (!(file->path = (char *)ft_memalloc(sizeof(char) * 2)) ||
		!(file->name = (char *)ft_memalloc(sizeof(char) * 2)) ||
		!(file->full_path = (char *)ft_memalloc(sizeof(char) * 3)))
		return (t_filedel(file));
	file->path = ft_strcpy(file->path, ".");
	file->name = ft_strcpy(file->name, ".");
	file->full_path = ft_strcpy(file->full_path, "./");
	file->next = NULL;
	return (file);
}

t_file			*get_dirs(char **av, char flags, int i, int j)
{
	t_file	*paths;

	if (flags)
		while (av[i])
		{
			if (av[i][j] == '-')
				i++;
			else
				break ;
		}
	if (!(paths = t_fileinit()))
		return (t_filedel(paths));
	return (paths);
}
/*
** TODO ^
** grab all paths excluding .
*/
