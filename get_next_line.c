/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforte-j <fforte-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:23 by fforte-j          #+#    #+#             */
/*   Updated: 2024/11/28 20:39:37 by fforte-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*read_file = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_file = read_fd(fd, read_file);
	if (!read_file)
		return (NULL);
	line = find_line(read_file);
	read_file = prepare_next_call(read_file);
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

char	*join_free_swap(char *read_file, char *buffer)
{
	char	*swap_read;

	swap_read = ft_strjoin(read_file, buffer);
	free(read_file);
	read_file = NULL;
	return (swap_read);
}

char	*read_fd(int fd, char *read_file)
{
	char	*buffer;
	int		bytes;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	if (!read_file)
		read_file = ft_calloc(1, 1);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(read_file);
			return (NULL);
		}
		buffer[bytes] = '\0';
		read_file = join_free_swap(read_file, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (read_file);
}

// int	main(void)
// {
// 	int	fd;
// 	char	*line_p;

// 	fd = open("read_error.txt", O_RDONLY);
// 	printf("file descriptor 1st run: %d\n", fd);
// 	while (1) {
// 		line_p = get_next_line(fd);
// 		if (!line_p)
// 		{
// 			free(line_p);
// 			break;
// 		}
//         printf("%s", line_p);
// 		free(line_p);
//     }
// 	line_p = get_next_line(fd);
// 	printf("%s", line_p);
// 	free(line_p);

// 	close(fd);

// 	fd = open("read_error.txt", O_RDONLY);
// 	printf("file descriptor 1st run: %d\n", fd);

// 	while (1) {
// 		line_p = get_next_line(fd);
// 		if (!line_p)
// 		{
// 			free(line_p);
// 			break;
// 		}
//         printf("%s", line_p);
// 		free(line_p);
//     }
// 	// line_p = get_next_line(fd);
// 	// printf("%s", line_p);
// 	// free(line_p);
// 	return (0);
// }
