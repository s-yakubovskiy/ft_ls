//
// Created by Yoshiko Harwyn hoare on 2019-04-04.
//

#include "ft_ls.h"

void	print_ls_one_flag(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (ls->dir[i] != NULL)
	{
		j = 0;
		while (ls->dir[i]->cont[j] != NULL)
		{
			ft_putendl(ls->dir[i]->cont[j]->name);
			j++;
		}
		i++;
	}
	i = 0;
	while (ls->file[i] != NULL)
	{
		ft_putendl(ls->file[i]->name);
		i++;
	}
}

void    display_contents(t_ls_item *ls)
{
	struct stat fileStat;
	char link_read[255];
	ssize_t bytes_read;

    if (lstat(ls->path, &fileStat) == -1)
    {  /* validate stat of file */
//        perror("stat");
        return ;
    }
//	lstat(ls->path, &fileStat);
	if(S_ISLNK(fileStat.st_mode))
	{
//		printf("%s ",ls->path );
		bytes_read = readlink(ls->path, link_read, 254);
		link_read[bytes_read] = '\0';
		f_strcpy(ls->path, " -> ");
		f_strcpy(ls->path, link_read);
//		printf("-> %s\n", link_read);
	}
}

//
//void    display_contents(char * name)
//{
//    struct stat sb;
//    struct tm * t;
//    char link_read[255];
//    ssize_t bytes_read;
//    lstat(name, &sb);
//
////	printf("%c", S_ISDIR(sb.st_mode)?'d':\
////		     S_ISFIFO(sb.st_mode)?'p':\
////		     S_ISLNK(sb.st_mode)?'l':'-');
////
////
////	printf("%c", (S_IRUSR & sb.st_mode) ? 'r' : '-');
////	printf("%c", (S_IWUSR & sb.st_mode) ? 'w' : '-');
////	printf("%c", (S_IXUSR & sb.st_mode) ? 'x' : '-');
////	printf("%c", (S_IRGRP & sb.st_mode) ? 'r' : '-');
////	printf("%c", (S_IWGRP & sb.st_mode) ? 'w' : '-');
////	printf("%c", (S_IXGRP & sb.st_mode) ? 'x' : '-');
////	printf("%c", (S_IROTH & sb.st_mode) ? 'r' : '-');
////	printf("%c", (sb.st_mode & S_IWOTH) ? 'w' : '-');
////	printf("%c  ", (S_IXOTH & sb.st_mode) ? 'x' : '-');
////	printf("%d\t", sb.st_nlink);
////	printf("%s\t", user_from_uid(sb.st_uid,0));
////	printf("%s\t", group_from_gid(sb.st_gid,0));
////	printf("%5.0lu ", sb.st_size);
////	t = localtime(&sb.st_ctime);
////	printf("%s ", lookup[t->tm_mon]);
////	printf("%2.0d %2.0d:%2.0d ", t->tm_mday, t->tm_hour, t->tm_min);
//    if(S_ISLNK(sb.st_mode)){
//        printf("@\033[35m%s ",name );
//        printf("\033[37m");
//        bytes_read = readlink(name, link_read, 254);
//        link_read[bytes_read] = '\0';
//        printf("-> %s\n", link_read);
//    }
////	else if((S_IXUSR & sb.st_mode) || (S_IXGRP & sb.st_mode) || (S_IXOTH & sb.st_mode))
////		printf("%s", name);
////	else if(S_ISFIFO(sb.st_mode))
////		printf("%s", name);
////	else
////		printf("%s", name);
//
//
//}