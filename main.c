/* main.c - main function file
 * Copyright (C) 2014 Adrian Alonso <aalonso00@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with self library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

/* Modified by Hugo Ivan Romo Villaseñor */

#define DATA_LENGTH 16u
#define NULL_VALUE 0u

int
main(int argc, char **argv)
{
    int fd, index, dir;
    char *file = NULL;
    unsigned char buff[DATA_LENGTH];
    struct stat file_info;
    size_t* length;
    dir = NULL_VALUE;
    if(argc != 2)
    {
        printf ("Usage: %s <file>\n", argv[0]);
        exit (1);
    }

    file = argv[1];

    fd = open(file, O_RDONLY);

    if(fd < 0)
    {
        printf ("Error");
        exit(1);
    }
       /* Print complete file content following od hex format */
       /* od -A x -t x1z -v file.dat */
       /* Get information about the file.  */
       fstat (fd, &file_info);
       /* Get length of the file.  */
       *length = file_info.st_size;
	/*dir will check for all data*/
	while (dir<*length)
       {
	/* Read 16 characters per lap */
	read(fd,buff,DATA_LENGTH);
	/* Print direction with 6 digits */
	printf("%06x ",dir);
	/* Check if is not the last 16 bytes */
	if((*length - dir) >= DATA_LENGTH)
	{
		for(index=NULL_VALUE;index<DATA_LENGTH;index++)
		{
			/* Print 16 hex values*/
			printf("%02x ",buff[index]);
		}
	}
	else
	{
		for(index=NULL_VALUE;index<(*length - dir);index++)
		{
			/* Print valid values only */
			printf("%02x ",buff[index]);
		}
		for(index=(*length - dir);index<DATA_LENGTH;index++)
		{
			/* Print spaces instead of invalid values */
			printf("   ");
			/* Set spaces instead of invalid values */
			buff[index] = 0; /* " " */
		}
	}
		for(index=NULL_VALUE;index<DATA_LENGTH;index++)
		{
			/* Replace "Backspace"(0x0A) with "dots"(46) */
			if(0x0A  == buff[index]) 
			{
				buff[index] = 46; /* "." */
			}
		}
		/* Print characters*/
		printf(">%s<\n",buff);
		dir += DATA_LENGTH;
        }
	close (fd);

    return NULL_VALUE;
}
