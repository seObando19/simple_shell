#include "holberton.h"

/**
 * prompt - Prints prompt in color
 *@void: value void
 *Return: void
*/
void prompt(void)
{
	printf("\x1B[1;33m$\x1B[0m ");

}
/**
 * listenread - get char the client terminal & call fn until char is '\n'
 *@buffer: pointer
 * Return: 1 is successful, -1 if error.
 */
int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	ssize_t c;

	fflush(stdin);
	c = getline(&buffer, &bufsize, stdin);
	if (c == EOF)
		return (-1);
	else if (_strcmp(buffer, "exit") == 100)
		return (-1);
	return (0);
}
/**
 * get_simple_args - this fn splits the string when space char is found
 *@argc: argument counter
 *@argv: where the arguments are contained
 *@args: arguments
 *@_path: path
 *@ev: pointer that contain enviroment vars
 * Return: status of execution
 */
int get_simple_args(int argc, char **argv, char *args, char **_path, char **ev)
{
	char delim[] = " \n";
	char **options;
	char *argx;
	int j = 0;
	int args_max = 255, status_pid = 0;
	(void)_path;

	if (argc == 1)
	{
		if ((int)args[0] == 100)
			free(args);
		else
		{
			options = malloc(sizeof(char *) * args_max);
			if (options == NULL)
			{
				free(options);
				exit(111);
			}
			argx = strtok(args, delim);
			while (argx != NULL)
			{options[j] = argx;
				argx = strtok(NULL, delim);
				j++; }
			options[j] = NULL;
			if (_strcmp(options[0], "env") == 0 && options[1] == NULL)
				_printenv(ev);
			else if (options[0] != NULL && _strlen(options[0]) > 0)
				status_pid = pid_launch(options, args, _path);
			free(args);
			free(options);
		}
	}
	else if (argc >= 2)
	{
		args_nval(argv);
		status_pid = pid_launch(argv, NULL, _path);
	}
	return (status_pid);
}
/**
 * _error - allows the error message to be printed in shell
 *
 */
void _error(void)
{
	/* write(STDERR_FILENO, __FILE__, _strlen(__FILE__)); */
	write(STDERR_FILENO, "sh ", 2);
	write(STDERR_FILENO, ": No such file or directory",
	 _strlen("/: No such file or directory"));
	write(STDERR_FILENO, "\n", _strlen("\n"));

}
/**
 * pid_launch - make a fork to create child process who execute the command
 *@args: arguments
 *@_path: path
 *@_argv: argument container
 * Return: exit status
 */
int pid_launch(char **_argv, char *args, char **_path)
{
	pid_t pid;
	char *envp[] = {"", NULL}, *dir = NULL, *file = NULL, *fullpath = NULL;
	int status, j = 0, searchpath = 1, accessfile = 0;
	struct stat fileStat;

	pid = fork();
	if (pid == 0)
	{file =  _argv[0];
		while (*(_path + j) != NULL && searchpath == 1)
		{searchpath = appenddir(file);
			dir = str_concat(NULL, *(_path + j));
			dir = strdup(*(_path + j));
			fullpath = searchpath == 1 ? str_concat(dir, file) : file;
			if (stat(fullpath, &fileStat) == 0)
			{accessfile = 1;
				searchpath = 0; }
			j++;
			free(dir); }
		if (accessfile)
		{
			if (execve(fullpath, _argv, envp) == -1)
			{_error();
				free(args);
				free(_argv);
				exit(EXIT_FAILURE); } }
		else
		{free(args);
			free(_argv);
			_error();
			exit(2); }
	}
	else if (pid < 0)
	{free(args);
		free(_path);
		free(_argv);
		exit(102); }
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status) & 255);
}
