/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:58:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/05 22:02:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file			*t_filedel(t_file **apath)
{
	if ((*apath)->name != NULL)
	{
		free((*apath)->name);
		(*apath)->name = NULL;
	}
	if ((*apath)->full_path != NULL)
	{
		free((*apath)->full_path);
		(*apath)->full_path = NULL;
	}
	if ((*apath)->next != NULL)
		t_filedel(&(*apath)->next);
	if ((*apath))
	{
		free((*apath));
		(*apath) = NULL;
	}
	return (NULL);
}

t_file			*t_fileinit(char *param, char *fullpath, int type)
{
	t_file		*file;

	if (!(file = ft_memalloc(sizeof(t_file))))
		return (NULL);
	file->next = NULL;
	if (type == 0)
	{
		if (!(file->name = ft_strdup(param)))
			return (t_filedel(&file));
		lstat(param, &(file->info));
	}
	else if (type == 1)
	{
		if (!(file->name = ft_strdup(param)) ||
			!(file->full_path = ft_strdup(fullpath)))
			return (t_filedel(&file));
		lstat(fullpath, &(file->info));
	}
	file->index = 1;
	return (file);
}

int				t_fileadd(t_file **apath, char *param, char *fullpath, int type)
{
	t_file	*head;
	t_file	*to_add;

	if (!(to_add = ft_memalloc(sizeof(t_file))))
		return (1);
	to_add->next = NULL;
	if (type == 0)
	{
		IF_RETURN((!(to_add->name = ft_strdup(param))), 1);
		lstat(param, &(to_add->info));
	}
	else if (type == 1)
	{
		if (!(to_add->name = ft_strdup(param)) ||
			!(to_add->full_path = ft_strdup(fullpath)))
			return (1);
		lstat(fullpath, &(to_add->info));
	}
	head = *apath;
	while (head->next)
		head = head->next;
	to_add->index = head->index + 1;
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
		ft_pipewrench("-s-s", tmp->name, tmp->full_path);
		free(tmp);
		return ;
	}
	while (tmp && tmp->index != index)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp->index == index)
	{
		prev->next = tmp->next;
		ft_pipewrench("-s-s", tmp->name, tmp->full_path);
		free(tmp);
	}
}
