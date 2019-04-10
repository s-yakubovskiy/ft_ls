

#include "ft_ls.h"

static void ft_ls_cleaner_string(t_ls_item	*ls)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		ls->time[i] = '\0';
		ls->day[i] = '\0';
		ls->month[i] = '\0';
	}
	i = 0;
	while (i < 256)
		ls->name[i++] = '\0';
	i = 0;
	while (i < 2048)
		ls->path[i++] = '\0';
	i = 0;
	while (i < 16)
		ls->perms[i++] = '\0';
	i = -1;
	while (++i < 64)
	{
		ls->uid[i] = '\0';
		ls->guid[i] = '\0';
	}
	ls->next = NULL;
}

void free_ls_item(t_ls_item	*ls)
{
	int i;

	i = 0;
	if (ls->cont != NULL)
	{
		while (ls->cont[i])
		{
			ft_ls_cleaner_string(ls->cont[i]);
			free(ls->cont[i++]);
		}
	}
	ft_ls_cleaner_string(ls);
	free(ls->cont);
}

void ft_free_ls(t_ls *ls)
{
	int	i;

	i = 0;
	while (ls->dir[i])
	{
		free_ls_item(ls->dir[i]);
		free(ls->dir[i++]);
	}
	free(ls->dir);
	i = 0;
	while (ls->file[i])
	{
		free_ls_item(ls->file[i]);
		free(ls->file[i++]);
	}
	free(ls->file);
	i = 0;
	while (i < 256)
		ls->path[i++] = '\0';
	free(ls);
}