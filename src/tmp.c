//
// Created by Yoshiko Harwyn hoare on 2019-04-02.
//

//int main(int argc, char **argv)
//{
//	if(argc != 2)
//		return 1;
//
//	struct stat fileStat;
//	if(stat(argv[1],&fileStat) < 0)
//		return 1;
//
//	printf("Information for %s\n",argv[1]);
//	printf("---------------------------\n");
//	printf("File Size: \t\t%d bytes\n",fileStat.st_size);
//	printf("Number of Links: \t%d\n",fileStat.st_nlink);
//	printf("File inode: \t\t%d\n",fileStat.st_ino);
//
//	printf("File Permissions: \t");
//	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
//	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
//	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
//	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
//	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
//	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
//	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
//	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
//	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
//	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
//	printf("\n\n");
//
//	printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
//
//	return 0;
//}

//static void	ft_print_dir_file(t_ls_item **ls, int a, int len)
//{
//    int i;
//    int j;
//    int m;
//    int br;
//    int ws;
//    int col;
//
//    i = 0;
//    br = 0;
//    ws = get_terminal_width();
//    ws = 80;
//    col = ws / a;
//
////	printf("\nbreaker %d len: %d ws: %d a: %d\n ", br, len, ws, a);
//    while (ls[i])
//    {
//        m = a - (int)ft_strlen(ls[i]->name);
//        printf("%s", ls[i]->name);
//        if (ls[i + 1] != NULL)
//        {
//            j = -1;
//            while (++j < m)
//                printf("%c", ' ');
//        }
//        i++;
//    }
//    printf("\n");
//}