/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:00:53 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/05 15:20:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	grab_ls(t_ls *ls, int i)
{
	int             j;
	DIR				*d;
	struct dirent	*dir;
	j = 0;

	d = opendir(ls->dir[i]->path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((a_FLAG) == 0 && dir->d_name[0] != '.')
			{
				ls->dir[i]->cont[j] = create_ls_item(0);
				f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
				f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
				path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
				j++;
			}
			else if (a_FLAG)
			{
				ls->dir[i]->cont[j] = create_ls_item(0);
				f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
				f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
				path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
				j++;
			}
		}
		closedir(d);
	}
}

static void no_args(t_ls *ls, int argc)
{
    if (argc == 1)
    {
        ls->dir[(ls->num_dir)] = create_ls_item(1);
        f_strcpy(ls->dir[ls->num_dir]->name, ".");
        path_cpy(ls->dir[ls->num_dir]->path, ".", ls);
        ++(ls->num_dir);
    }
    else if (ls->dir[0] == NULL && ls->file[0] == NULL)
    {
         ls->dir[(ls->num_dir)] = create_ls_item(1);
         f_strcpy(ls->dir[ls->num_dir]->name, ".");
         path_cpy(ls->dir[ls->num_dir]->path, ".", ls);
         ++(ls->num_dir);
    }
}

void 	get_arguments(int argc, char *argv[], t_ls *ls)
{
	int i;
	int j;
	int k;
//	char *tmp;
	char tmp[256];

	i = 1;
//	tmp = ft_memalloc(sizeof(char) * 256);
	while (i < argc)
	{
		if (argv[i][0] == '-')
		    i++;
		else
		{
			j = 0;
			while(ISSPACE(argv[i][j]))
				j++;
			k = 0;
			if (argv[i][j] == '\0')
            {
                f_strcpy(tmp, ".");
                if (ft_check_open_dir(tmp) == 1)
                {
                    ls->dir[(ls->num_dir)] = create_ls_item(1);
                    f_strcpy(ls->dir[ls->num_dir]->name, tmp);
                    path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
                    ++(ls->num_dir);
                }
//                ft_strdel(&tmp);
                return ;
            }
			while (argv[i][j] != '\0' && argv[i][j] != ' ')
			{
				tmp[k] = argv[i][j];
				j++;
				k++;
			}
			tmp[k] = '\0';
			if (is_dir(tmp) == 1)
			{
				if (ft_check_open_dir(tmp) == 1)
				{
					ls->dir[(ls->num_dir)] = create_ls_item(1);
					f_strcpy(ls->dir[ls->num_dir]->name, tmp);
					path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
					++(ls->num_dir);
				}
			}
			else
			{
				if (ft_check_open_file(tmp) == 1)
				{
					ls->file[(ls->num_file)] = create_ls_item(0);
					f_strcpy(ls->file[ls->num_file]->name, tmp);
					path_cpy(ls->file[ls->num_file]->path, tmp, ls);
					++(ls->num_file);
				}
			}
			ft_bzero(tmp, (size_t)k);
			i++;
		}
	}
//	ft_strdel(&tmp);
	no_args(ls, argc);
}

int		main(int argc, char **argv)
{
	t_ls    *ls;
	int     i;

	i = 0;
	if (arg_checker(argc, argv) == -1)
	{
		ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
             "[file ...]\n");
		return (0);
	}
	ls = create_ls_main();
	ls->flag = Ft_Get_Bit(argc, argv);
	get_arguments(argc, argv, ls);
	get_contents(ls);
	if (R_FLAG)
    {
        while (ls->dir[i] != NULL)
        {
            ls_recoursive(ls->dir[i]->name, ls->flag);
            i++;
        }
    }
	else
        ls_base(ls);
	ft_free_ls(&ls);
}
