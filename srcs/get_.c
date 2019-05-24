/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 01:54:58 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/23 22:14:11 by rpapagna         ###   ########.fr       */
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

static int		t_fileadd(t_file **apath, char *dir)
{
	t_file	*head;
	t_file	*to_add;

	if (!(to_add = ft_memalloc(sizeof(t_file))))
		return (1);
	to_add->next = NULL;
	if (!(to_add->path = (char *)ft_memalloc(sizeof(char) * (LEN(dir) + 1))) ||
		!(to_add->name = (char *)ft_memalloc(sizeof(char) * (LEN(dir) + 1))) ||
		!(to_add->full_path =
							(char *)ft_memalloc(sizeof(char) * (LEN(dir) + 1))))
		return (1);
	head = *apath;
	while (head->next)
		head = head->next;
	to_add->index = head->index + 1;
	to_add->path = ft_strcpy(to_add->path, dir);
	to_add->name = ft_strcpy(to_add->name, dir);
	to_add->full_path = ft_strcpy(to_add->full_path, dir);
	head->next = to_add;
	return (0);
}

t_file			*get_dirs(char **av, char flags, int i, int j)
{
	t_file	*paths;

	if (!(paths = t_fileinit()))
		return (t_filedel(paths));
	while (av[i])
	{
		if (av[i][j] == '-')
			i++;
		else
			break ;
	}
	while (av[i])
	{
		if (t_fileadd(&paths, av[i]))
			return (t_filedel(paths));
		i++;
	}
	return (paths);
}
