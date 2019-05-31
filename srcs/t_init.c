/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:58:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/30 18:03:06 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file			*t_filedel(t_file *file)
{
	if (file->path != NULL)
	{
		free(file->path);
		file->path = NULL;
	}
	if (file->name != NULL)
	{
		free(file->name);
		file->name = NULL;
	}
	if (file->full_path != NULL)
	{
		free(file->full_path);
		file->full_path = NULL;
	}
	if (file->next != NULL)
		t_filedel(file->next);
	free(file);
	return (NULL);
}

t_file			*t_fileinit(char *param)
{
	t_file		*file;

	if (!(file = ft_memalloc(sizeof(t_file))))
		return (NULL);
	file->next = NULL;
	if (!(file->path = ft_strdup(param)) ||
		!(file->name = ft_strdup(param)) ||
		!(file->full_path = ft_strdup(param)))
		return (t_filedel(file));
	file->index = 1;
	return (file);
}

int				t_fileadd(t_file **apath, char *dir)
{
	t_file	*head;
	t_file	*to_add;

	if (!(to_add = ft_memalloc(sizeof(t_file))))
		return (1);
	to_add->next = NULL;
	if (!(to_add->path = ft_strdup(dir)) ||
		!(to_add->name = ft_strdup(dir)) ||
		!(to_add->full_path =
							(char *)ft_memalloc(sizeof(char) * (LEN(dir) + 1))))
		return (1);
	head = *apath;
	while (head->next)
		head = head->next;
	to_add->index = head->index + 1;
	to_add->full_path = ft_strcpy(to_add->full_path, dir);
	head->next = to_add;
	return (0);
}

void			t_filedelone(t_file **apath, int index)
{
	t_file		*tmp;
	t_file		*prev;

	tmp = *apath;
	if (tmp->index == index)
	{
		*apath = tmp->next;
		ft_pipewrench("-s-s-s", tmp->path, tmp->name, tmp->full_path);
		free(tmp);
		return ;
	}
	while (tmp && tmp->index != index)
	{
		prev = tmp;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (tmp && tmp->index == index)
	{
		prev->next = tmp->next;
		ft_pipewrench("-s-s-s", tmp->path, tmp->name, tmp->full_path);
		free(tmp);
	}
}

t_file			*t_filepushfront(t_file **apath, int index)
{
	t_file		*tmp;
	t_file		*prev;

	tmp = *apath;
	IF_RETURN(tmp->index == index, tmp);
	while (tmp && tmp->index != index)
	{
		prev = tmp;
		IF_THEN_CONTINUE(tmp->next, tmp = tmp->next);
		IF_BREAK(!tmp->next);
	}
	prev->next = tmp->next;
	tmp->next = *apath;
	*apath = tmp;
	return (prev);
}
