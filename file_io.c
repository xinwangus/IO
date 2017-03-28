/* 
 * File I/O
 * Unix specific, not portable to other platforms
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char data1[] = "ABCDEF"; /* c string has \0 ending */
char data2[] = "abcdefg"; /* c string has \0 ending */

char file1[] = "./test";

int main() {
	int n1, n2;

	/* create a new file, or truncate an old file */
	int fd1 = open(file1, O_RDWR|O_CREAT|O_TRUNC);
	if (fd1 < 0 ) {
		printf("file create error\n");
		return -1;
	}

	/* current offset, showing file starts with offset 0. */
        int offset = lseek(fd1, 0, SEEK_CUR);	
	printf("file current offset %d\n", offset);

	/* write */
	n1 = sizeof(data1);
	if (write(fd1, data1, n1) != n1) {
		printf("file write error: %s\n", data1);
		return -1;
	} else {
		printf("file written bytes %d\n", n1);
	}

	/* lseek get the current offset. */
        offset = lseek(fd1, 0, SEEK_CUR);	
	printf("file current offset %d\n", offset);

        offset = lseek(fd1, 100, SEEK_CUR);	
	printf("file current offset %d\n", offset);

	/* write */
	n2 = sizeof(data2);
	if (write(fd1, data2, n2) != n2) {
		printf("file write error: %s\n", data2);
		return -1;
	} else {
		printf("file written bytes %d\n", n2);
	}
	
        offset = lseek(fd1, 0, SEEK_CUR);	
	printf("file current offset %d\n", offset);

	/* no need to call close() */
}

