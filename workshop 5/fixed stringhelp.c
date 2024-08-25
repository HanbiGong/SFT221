#define _CRT_SECURE_NO_WARNINGS
#include "stringhelp.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/*
* Return the index of the next whitespace.
* @param str - the string to search
* @returns the index of the next white space or the position of the
string terminator.
*/
int nextWhite(const char* str)
{
	// initialize the result to -1 and the index to 0
	int i, result = -1;
	// until the end of the string is reached
	for (i = 0; result < 0 && str[i] != '\0'; i++)
	{
		// if the character is a space
		if (isspace(str[i]))
		{
			// set the result to the index
			result = i;
		}	
	}
	// there is a bug in this function
	// it did not return the index of the next white space
	// it only returned -1
	return (result < 0) ? i : result;

}
/**
* Return true if the string contains only digits.
* @param str - the string to check
* @param len - the number of characters to check
* @returns true if the string is only digits.
*/
int isNumber(const char* str, const int len)
{
	// initialize the result to 1 and the index to 0
	int i, result = 1;
	// until the end of the string is reached
	for (i = 0; i < len && result; i++)
	{ 
		// if the character is not a digit
		if (!isdigit(str[i]))
		{
			// set the result to 0
			result = 0;
		}
	}
	return result;
}
/**
* Build an index for a string showing the start of the lines,
* words, and numbers in the string.
* @param str - the string to search
* @returns the index of the next white space or -1 if there is none.
*/
struct StringIndex indexString(const char* str)
{
	// there is a bug in this function
	// it did not initialize to zero the 7 variables of the struct
	// it only did it for 6 variables
	struct StringIndex result = { {0}, {0}, {0}, {0}, 0, 0, 0 };
	int i, sp;
	// copies the string to the struct
	strcpy(result.str, str);
	// not empty string
	if (str[0] != '\0')
	{
		// set the first line start to 0
		result.lineStarts[0] = 0;
		// set the number of lines to 1
		result.numLines = 1;
	}
	// until the end of the string is reached '\n'
	for (i = 0; str[i] != '\0'; i++)
	{
		// while the string is not empty and the character is a space
		while (str[i] != '\0' && isspace(str[i]))
		{
			// if the character is a new line
			if (str[i] == '\n')
			{
				// there is a bug in this function
				// it did not increment the number of lines
				// when it finds a new line
				result.lineStarts[result.numLines++] = i + 1;
			}
			// increment the index
			i++;
		}
		// set the index of the next white space
		sp = nextWhite(str + i);
		// this is a bug in this function
		// if (isNumber(str + i, sp - i + 1)) is wrong because it is not checking the last character it should be if (isNumber(str + i, sp)) 
		// because the function nextWhite is returning the index of the next white space so it should be str + i, sp
		if (isNumber(str + i, sp))
		{
			// set the index of the number start
			result.numberStarts[result.numNumbers++] = i;
		}
		else
		{
			// set the index of the word start
			result.wordStarts[result.numWords++] = i;
		}
		// increment the index
		i += sp - 1;
	}
	return result;
}
/**
* Return the number of lines in the index.
* @param idx - the index to get the number of lines in it
* @returns the number of lines in the index
*/
int getNumberLines(const struct StringIndex* idx)
{
	return idx->numLines;
}
/**
* Return the number of words in the index.
* @param idx - the index to get the number of words in it
* @returns the number of words in the index
*/
int getNumberWords(const struct StringIndex* idx)
{
	return idx->numWords;
}
/**
* Return the number of numbers in the index.
* @param idx - the index to get the number of numbers in it
* @returns the number of numbers in the index
*/
int getNumberNumbers(const struct StringIndex* idx)
{
	return idx->numNumbers;
}
/**
* Return the nth word from the index
* @param word - where the result will be placed
* @param idx - the index to use
* @param wordNum - the index of the word to retrieve
* @returns the word or an empty string if index is invalid
*/
void getWord(char word[], const struct StringIndex* idx, int wordNum)
{
	// there is a bug in this function
	// it did not decrement the number of words
	int i, sp, start;
	word[0] = '\0';
	// if the word number is valid
	if (wordNum < idx->numWords && wordNum >= 0)
	{
		start = idx->wordStarts[wordNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i < sp; i++)
		{
			word[i] = idx->str[i];
		}
		word[sp] = '\0';
		((struct StringIndex*)idx)->numWords--;
	}
}
/**
* Return the nth number from the index
* @param word - where the result will be placed
* @param idx - the index to use
* @param wordNum - the index of the number to retrieve
* @returns the number or an empty string if index is invalid
*/
void getNumber(char word[], const struct StringIndex* idx, int
	numberNum)
{
	int i, sp, start;
	word[0] = '\0';
	if (numberNum < idx->numNumbers && numberNum >= 0)
	{
		start = idx->numberStarts[numberNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i < sp; i++)
		{
			word[i] = idx->str[start + i];
		}
		word[sp] = '\0';
	}
}
/**
* Return a pointer to the start of a line
* @param idx - the index to use
* @param lineNum - the index of the line to retrieve
* @returns a pointer to the start of the line
*/
char* getLine(struct StringIndex* idx, int lineNum)
{
	char* result = NULL;
	if (lineNum < idx->numLines && lineNum >= 0)
	{
		result = idx->str + idx->lineStarts[lineNum];
	}
	return result;
}
/**
* Prints characters until the terminator is found.
* @param s - the string to print
* @param start - the index to start printing
* @param terminator - the character to stop printing at when
encountered.
*/
void printUntil(const char* s, const int start, const char terminator)
{
	int i;
	for (i = start; s[i] != '\0' && s[i] != terminator; i++)
		printf("%c", s[i]);
}
/**
* Prints characters until a space is found.
* @param s - the string to print
* @param start - the index to start printing
*/
void printUntilSpace(const char* s, const int start)
{
	int i;
	for (i = start; s[i] != '\0' && !isspace(s[i]); i++)
		printf("%c", s[i]);
}