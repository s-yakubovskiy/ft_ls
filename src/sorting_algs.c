//
// Created by Yoshiko Harwyn hoare on 2019-04-08.
//

#include "ft_ls.h"

void    bubble_sort_ls(t_ls_item *ls)
{
    int sw;
    int i;

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

static void ft_sorting_by_time(t_ls_item *ls)
{
    struct stat s1, s2;
    int i;
    int j;
    int l;
    int t1,t2;

    l = 0;
    i = 0;
    while (ls->cont[l])
        l++;
    while (i < l)
    {
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
        i++;
    }
}

void ft_tsort(t_ls	*ls)
{
    int i;

    //	i = 0;
    //	while (ls->dir[i])
    //		sort_bubble(ls->dir[i++]);
    if (t_FLAG)
    {
        i = 0;
        while (ls->dir[i])
            ft_sorting_by_time(ls->dir[i++]);
    }
    //	if (r_FLAG)
    //	{
    //		i = 0;
    //		while (ls->dir[i])
    //			ft_revers(ls->dir[i++]);
    //	}
}

static void bubble_sort_ls_file(t_ls *ls)
{
    int sw;
    int i;

    sw = 0;
    i = 0;
    while (ls->file[i + 1] != NULL)
    {
        if (ft_strcmp(ls->file[i]->name, ls->file[i + 1]->name) > 0)
        {
            swap_ls_item(ls->file[i]->name, ls->file[i + 1]->name);
            sw += 1;
        }
        i++;
        if (ls->file[i + 1] == NULL && sw != 0)
        {
            i = 0;
            sw = 0;
        }
    }
}

void ft_sort_by_ascii(t_ls *ls)
{
    int i;

    bubble_sort_ls_file(ls);
    i = 0;
    while (ls->dir[i])
    {
        bubble_sort_ls(ls->dir[i]);
        i++;
    }
}


//void    bubble_sort_ls(t_ls_item *ls)
//{
//    int sw;
//    int i;
//    int j;
//
//    sw = 0;
//    i = 0;
//    while (ls->cont[i] != NULL)
//    {
//        j = 0;
//        while (ls->cont[j] != NULL)
//        {
//            if (ft_strcmp(ls->cont[j]->name, ls->cont[j + 1]->name) > 0)
//            {
//                swap_ls_item(ls->cont[j], ls->cont[i + 1]);
//                sw++;
//            }
//        }
//    }
//}