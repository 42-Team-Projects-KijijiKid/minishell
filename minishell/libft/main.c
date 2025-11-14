#include "libft.h"

int main(void)
{
    int fds[2];
    int array_len;
	int index;
	// static int loops = 0;
	char *line = NULL;

    array_len = sizeof(fds) / sizeof(fds[0]);
    index = 0;
	fds[0] = open("nextline.txt", O_RDONLY);
	fds[1] = open("multiple_nl.txt", O_RDONLY);
	if (fds[0] == -1 || fds[1] == -1)
	{
		perror("Error opening file");
		return (1);
	}
    while (index < array_len)
    {
        while ((line = get_next_line(fds[index])))
        {
            printf("%s", line);
            free(line);
        }
        printf("\n");    
        index++;
    }
    printf("\n");    
	close(fds[0]);
	close(fds[1]);
	return (0);
}
