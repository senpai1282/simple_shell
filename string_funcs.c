#include "header.h"

/**
 * _strlen - Calculate the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
size_t _strlen(const char *s)
{
	size_t len = 0;
	
	while (s[len] != '\0')
		len++;

	return len;
}

/**
 * _strcpy - Copy a string.
 * @dest: The destination buffer.
 * @src: The source string.
 * Return: A pointer to the destination buffer.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return dest;
}

/**
 * _strcat - Concatenate two strings.
 * @dest: The destination buffer.
 * @src: The source string.
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, const char *src)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return dest;
}
