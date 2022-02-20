# 42-formation-lvl1-6.pipex

### _Project 6: pipex - Sixth project for the formation of software engineers at school 42 São Paulo._

---

```c
#include "./pipex.h"

void	pipex(t_data *data);
void	child_process(t_data *data);
void	parent_process(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		write(2, "Error: Invalid argument\n", 25);
		exit(EINVAL); //invalid input error
	}

    //argv[1] -> infile
    //O_RDONLY -> infile reading
    //0644 -> chmod authorization
	data.fdin = open(argv[1], O_RDONLY, 0644);

    //argv[4] -> outfile
    //O_WRONLY -> infile writing
    //O_CREAT -> if we don't have the outfile, we create it
    //O_TRUNC -> command that overwrites the previous one in the outfile
    //0644 -> chmod authorization
	data.fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (data.fdin == -1 || data.fdout == -1)
		error(errno); //error number. To see, run echo $?
	data.argc = argc;
	data.argv = argv;
	data.envp = envp; //environment path
	pipex(&data);
	return (0);
}

void	pipex(t_data *data)
{
	if (pipe(data->fd) == -1)
		error(errno);

    //pid -> process id
	data->pid = fork(); //child process creation
	if (data->pid == -1)
		error(errno);
	if (data->pid == 0)
	{
		child_process(data);
	}
	else
	{
        //waitpid waits for the child process to run and then executes the parent process
		waitpid(data->pid, NULL, 0);
		parent_process(data);
	}
}

void	child_process(t_data *data)
{
	char	**cmd;
	char	*cmd_path;

    //argv[0] -> ./pipex
    //argv[1] -> infile
    //argv[2] -> command 1
	cmd = ft_split(data->argv[2], ' ');
	cmd_path = get_cmd_path(cmd[0]);
    //dup -> duplicate on next valid fd
    //dup2 -> we choose where we want to duplicate
	dup2(data->fdin, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fdin);
	close(data->fd[1]);
	close(data->fdout);
	//
	execve(cmd_path, cmd, data->envp);
}

void	parent_process(t_data *data)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(data->argv[3], ' ');
	cmd_path = get_cmd_path(cmd[0]);
	close(data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
	dup2(data->fdout, STDOUT_FILENO);
	close(data->fdout);
	execve(cmd_path, cmd, data->envp);
}

char	*get_cmd_path(char *cmd)
{
	char	**path;
	char	*temp;
	int		i;

	if (cmd == NULL)
		return (NULL);
    //splitting the directories
	path = ft_split(PATH, ':');	sbin/bona/bin/ls
	i = 0;
	while (path[i])
	{   
        //concatenating the executable with the path.
		temp = ft_strjoin(path[i], cmd);

        //access -> checks if the directory is existing or not
        //if it is 0, we release the allocation and return the path with the executable command 
		if (access(temp, F_OK) == 0)
		{
			free_matrix(path);
			return (temp);
		}
		free(temp);
		i++;
	}
	free_matrix(path);
	error_cmd_not_found(cmd);

    //126 -> find the command but it gave an error
    //127 -> does not find the given path in the shell
	exit(127);
}

```