#include "holberton.h"

/**
*_printenv - print env
* @env: pointer contains the list var
* Return: 0
*/
int _printenv(char **env)
{
	int i = 0;

	while (*(env + i) != NULL)
	{
		write(STDOUT_FILENO, *(env + i), _strlen(*(env + i)));
		write(STDOUT_FILENO, "\n", _strlen("\n"));
		i++;
	}
	return (0);
}

/**
 * appenddir - appends the "." and "/" of the commands in env path
 *@cmd: command
 * Return: 0 or 1
 */
int appenddir(char *cmd)
{
	int i = 0;

	while (cmd[i] != '\0')
		i++;
	if (i > 2)
	{
		if (cmd[0] == '.' || cmd[0] == '/')
			return (0);
	}
	return (1);
}

/**
 *_strcmp - compare two strings
 *@s1: string 1
 *@s2: string 2
 *Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}
