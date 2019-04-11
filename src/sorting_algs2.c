//
// Created by Yoshiko Harwyn hoare on 2019-04-10.
//

#include "ft_ls.h"

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
            swap_ls_item(ls->file[i], ls->file[i + 1]); //something wrong here
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

//void ft_sort_by_ascii(t_ls *ls)
//{
//    int i;
//
//    bubble_sort_ls_file(ls);
//    i = 0;
//    while (ls->dir[i])
//    {
//        bubble_sort_ls(ls->dir[i]);
//        i++;
//    }
//}

void reverse_ls_output(t_ls_item *ls)
{
    int len;
    int i;

    len = cont_len(ls);
    i = 0;
    while (i <= len)
    {
        swap_ls_item(ls->cont[i++], ls->cont[--len]);
        if (i >= len)
            break ;
    }
}