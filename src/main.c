#include "ft_ls.h"

//int main (int c, char *v[]) {
//    int len;
//    struct dirent *pDirent;
//    DIR *pDir;
//
//    if (c < 2) {
//        printf ("Usage: testprog <dirname>\n");
//        return 1;
//    }
//    pDir = opendir (v[1]);
//    if (pDir == NULL) {
//        printf ("Cannot open directory '%s'\n", v[1]);
//        return 1;
//    }
//
//    while ((pDirent = readdir(pDir)) != NULL) {
//        printf ("%-30s", pDirent->d_name);
//    }
//    closedir (pDir);
//    return 0;



//	int a;
//
//	a = 0;
//	a = a >> 4;
//	a++;
//	a = a << 4;
//	a = a >> 2;
//	a++;
//	a = a << 2;
//	a = a >> 0;
//	a++;
//	a = a << 0;
//	printf("%i\n", a & 16);
//}

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	struct stat fileStat;
	if(stat(argv[1],&fileStat) < 0)
		return 1;

	printf("Information for %s\n",argv[1]);
	printf("---------------------------\n");
	printf("File Size: \t\t%d bytes\n",fileStat.st_size);
	printf("Number of Links: \t%d\n",fileStat.st_nlink);
	printf("File inode: \t\t%d\n",fileStat.st_ino);

	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");

	printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

	return 0;
}