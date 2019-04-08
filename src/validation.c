//
// Created by Yoshiko Harwyn hoare on 2019-04-08.
//

#include "ft_ls.h"


int	arg_checker(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc && argv[i][0] == '-')
    {
        j = 1;
        while (argv[i][j])
        {
            if (argv[i][j] != 'l' && argv[i][j] != 'R' && argv[i][j] != 'a'
                && argv[i][j] != 'r' && argv[i][j] != 't' && argv[i][j] != '1')
            {
                ft_putstr("ls: illegal option -- ");
                ft_putchar(argv[i][j]);
                return (-1);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int	Check_On_Consist(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (-1);
}

static int ft_get_count_flags(int argc, char **argv)
{
    int a;
    int i;
    int j;

    i = 1;
    a = 0;
    while (i < argc && argv[i][0] == '-')
    {
        j = 1;
        while (argv[i][j])
        {
            a++;
            j++;
        }
        i++;
    }
    return (a);
}

char	*Ft_Get_Str_Options(int argc, char **argv)
{
    int		i;
    int		j;
    int 	a;
    char	*str;

    i = 1;
    a = ft_get_count_flags(argc, argv);
    str = (char *)malloc(sizeof(char) * a);
    str[a] = '\0';
    while (i < argc && argv[i][0] == '-')
    {
        j = 1;
        a = 0;
        while (argv[i][j])
        {
            if (Check_On_Consist(str, argv[i][j]) == -1)
            {
                str[a++] = argv[i][j];
                str[a] = '\0';
            }
            j++;
        }
        i++;
    }
    return (str);
}

int ft_check_open_dir(char *tmp)
{
//	DIR				*d;
//	struct dirent	*dir;

    if (opendir(tmp) == NULL)
    {
        printf("%s: %s: No such file or directory\n", tmp, tmp);
        return (-1);
    }
    return (1);
}

int ft_check_open_file(char *tmp)
{
    if (fopen(tmp, "r") == NULL)
    {
        printf("%s: %s: No such file or directory\n", tmp, tmp);
        return (-1);
    }
    return (1);
}