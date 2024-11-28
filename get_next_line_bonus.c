/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforte-j <fforte-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:23 by fforte-j          #+#    #+#             */
/*   Updated: 2024/11/28 20:29:48 by fforte-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*read_file[FD_QTY];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_file[fd] = read_fd(fd, read_file[fd]);
	if (!read_file[fd])
		return (NULL);
	line = find_line(read_file[fd]);
	read_file[fd] = prepare_next_call(read_file[fd]);
	return (line);
}

char	*prepare_next_call(char *read_file)
{
	int		i;
	int		i2;
	char	*new_buffer;

	i = 0;
	i2 = 0;
	while (read_file[i] && read_file[i] != '\n')
		i++;
	if (!read_file[i])
	{
		free(read_file);
		read_file = NULL;
		return (NULL);
	}
	new_buffer = ft_calloc(ft_strlen(read_file) - i +1, sizeof(char));
	i++;
	while (read_file[i])
		new_buffer[i2++] = read_file[i++];
	free (read_file);
	read_file = NULL;
	return (new_buffer);
}

char	*find_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*join_free_swap(char *read_fd, char *buffer)
{
	char	*swap_read;

	swap_read = ft_strjoin(read_fd, buffer);
	free(read_fd);
	read_fd = NULL;
	return (swap_read);
}

char	*read_fd(int fd, char *read_fd)
{
	char	*buffer;
	int		bytes;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	if (!read_fd)
		read_fd = ft_calloc(1, 1);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(read_fd);
			return (NULL);
		}
		buffer[bytes] = '\0';
		read_fd = join_free_swap(read_fd, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (read_fd);
}

// int	main(void)
// {
// 	int	fd1;
// 	int	fd2;
// 	int	fd3;
// 	int	fd4;
// 	char	*line_p;

// 	fd1 = open("file1.txt", O_RDONLY);
// 	fd2 = open("file2.txt", O_RDONLY);
// 	fd3 = open("file3.txt", O_RDONLY);
// 	fd4 = open("file4.txt", O_RDONLY);
// 	int one_char = open("1char.txt", O_RDONLY);
// 	int empty = open("empty.txt", O_RDONLY);
// 	int giant_nl = open("giant_line_nl.txt", O_RDONLY);
// 	int giant_line = open("giant_line.txt", O_RDONLY);
// 	int lines_10 = open("lines_around_10.txt", O_RDONLY);
// 	int multiple = open("multiple_nl.txt", O_RDONLY);
// 	int one_no_nl = open("one_no_nl.txt", O_RDONLY);
// 	int only_nl = open("only_nl.txt", O_RDONLY);
// 	int read_error = open("read_error.txt", O_RDONLY);

// 	line_p = get_next_line(fd1);
// 	printf("%s", line_p);
// 	free(line_p);
// 	line_p = get_next_line(fd2);
// 	printf("%s", line_p);
// 	free(line_p);
// 	line_p = get_next_line(fd3);
// 	printf("%s", line_p);
// 	free(line_p);
// 	line_p = get_next_line(fd4);
// 	printf("%s", line_p);
// 	free(line_p);
// 	printf("\nTEST : 1 char ::::::::::::::::::::::::::::::::\n");
// 	line_p = get_next_line(one_char);
// 	printf("0 : %s", line_p);
// 	free(line_p);
// 	printf("\nTEST : EMPTY ::::::::::::::::::::::::::::::::\n");
// 	line_p = get_next_line(empty);
// 	printf("(null) : %s", line_p);
// 	free(line_p);
// 	printf("\nTEST : giant line with nl ::::::::::::::::::::::::::::::::\n");
// 	while ((line_p = get_next_line(giant_nl)))
// 	{
// 		// line_p = get_next_line(one_char);
// 		printf("%s", line_p);
// 		free(line_p);
// 	}
// 	printf("expected as last :   another line!!!\n");
// 	printf("\nTEST : giant line ::::::::::::::::::::::::::::::::\n");
// 	while ((line_p = get_next_line(giant_line)))
// 	{
// 		// line_p = get_next_line(one_char);
// 		printf("%s", line_p);
// 		free(line_p);
// 	}
// 	printf("expected as last : 123456789\n");
// 	printf("\nTEST : lines around 10 ::::::::::::::::::::::::::::::::\n");
// 	for (int i = 0; i < 5; i++)
// 	{
// 		line_p = get_next_line(lines_10);
// 		printf("%s", line_p);
// 		free(line_p);
// 	}
// 	printf("expected as last : xxxx\n");
// 	printf("\nTEST : multiple nl ::::::::::::::::::::::::::::::::\n");
// 	for (int i = 0; i < 5; i++)
// 	{
// 		line_p = get_next_line(multiple);
// 		printf("%s", line_p);
// 		free(line_p);
// 	}
// 	printf("expected 5 new lines with this one\n");
// 	printf("\nTEST : one line no nl ::::::::::::::::::::::::::::::::\n");
// 	line_p = get_next_line(one_no_nl);
// 	printf("should not break 2 lines : %s\n", line_p);
// 	free(line_p);
// 	printf("\nTEST : only one nl ::::::::::::::::::::::::::::::::\n");
// 	line_p = get_next_line(only_nl);
// 	printf("only one line break : %s", line_p);
// 	free(line_p);
// 	printf("\nTEST : read error ::::::::::::::::::::::::::::::::\n");
// 	for (int i = 0; i < 4; i++)
// 	{
// 		line_p = get_next_line(read_error);
// 		printf("%s", line_p);
// 		free(line_p);
// 	}
// 	printf("should print :\naaaaaaaaaa\nbbbbbbbbbb\ncccccccccc\ndddddddddd\n");

// 	// while (1) {
// 	// 	line_p = get_next_line(fd);
// 	// 	if (!line_p)
// 	// 	{
// 	// 		free(line_p);
// 	// 		break;
// 	// 	}
//     //     printf("%s", line_p);
// 	// 	free(line_p);
//     // }

// 	return (0);
// }
