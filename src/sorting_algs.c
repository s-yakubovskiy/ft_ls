#include "ft_ls.h"

void		bubble_sort_ls(t_ls_item *ls)
{
	int	sw;
	int	i;

	sw = 0;
	i = 0;
	if (ls == NULL)
		return ;
	while (ls->cont[i + 1] != NULL)
	{
		if (ft_strcmp(ls->cont[i]->name, ls->cont[i + 1]->name) > 0)
		{
			swap_ls_item(ls->cont[i], ls->cont[i + 1]);
			sw++;
		}
		i++;
		if (ls->cont[i + 1] == NULL && sw != 0)
		{
			sw = 0;
			i = 0;
		}
	}
}

static void	ft_body_sort_time(t_ls_item *ls)
{
	struct stat s1;
	struct stat s2;
	int			j;

	j = 0;
	while (ls->cont[j] && ls->cont[j + 1])
	{
		lstat(ls->cont[j]->path, &s1);
		lstat(ls->cont[j + 1]->path, &s2);
		if (s1.st_mtimespec.tv_sec < s2.st_mtimespec.tv_sec)
			swap_ls_item(ls->cont[j], ls->cont[j + 1]);
		if (s1.st_mtimespec.tv_sec == s2.st_mtimespec.tv_sec)
		{
			if (ft_strcmp(ls->cont[j]->name, ls->cont[j + 1]->name) > 0)
				swap_ls_item(ls->cont[j], ls->cont[j + 1]);
		}
		j++;
	}
}

static void	ft_sorting_by_time(t_ls_item *ls)
{
	int	i;
	int	l;

	l = 0;
	i = 0;
	while (ls->cont[l])
		l++;
	while (i < l)
	{
		ft_body_sort_time(ls);
		i++;
	}
}

void		ft_tsort(t_ls *ls)
{
	int	i;

	if (T_FLAG)
	{
		i = 0;
		while (ls->dir[i])
			ft_sorting_by_time(ls->dir[i++]);
	}
}

static void	ft_sort_dir_ls(t_ls *ls)
{
	int	i;
	int	sw;

	i = 0;
	sw = 0;
	while (ls->dir[i + 1] != NULL)
	{
		if (ft_strcmp(ls->dir[i]->name, ls->dir[i + 1]->name) > 0)
		{
			swap_ls_item(ls->dir[i], ls->dir[i + 1]);
			sw++;
		}
		i++;
		if (ls->dir[i + 1] == NULL && sw != 0)
		{
			sw = 0;
			i = 0;
		}
	}
}

void		ft_sort_by_ascii_all_dir_file(t_ls *ls)
{
	int i;
	int sw;

	i = 0;
	sw = 0;
	ft_sort_dir_ls(ls);
	while (ls->file[i + 1] != NULL)
	{
		if (ft_strcmp(ls->file[i]->name, ls->file[i + 1]->name) > 0)
		{
			swap_ls_item(ls->file[i], ls->file[i + 1]);
			sw++;
		}
		i++;
		if (ls->file[i + 1] == NULL && sw != 0)
		{
			sw = 0;
			i = 0;
		}
	}
	i = 0;
	while (ls->dir[i])
		bubble_sort_ls(ls->dir[i++]);
}
