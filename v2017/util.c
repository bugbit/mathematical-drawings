#include "pch.h"

#include "dibuixos.h"

int exist_dir(char *pathname)
{
	struct stat sb;

	return (stat(pathname, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void getfiledata(char *filedest,char *filename)
{
	sprintf(filedest,"%s%c%s",path_data,kPathSeparator,filename);
}