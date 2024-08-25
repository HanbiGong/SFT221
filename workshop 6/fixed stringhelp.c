#define _CRT_SECURE_NO_WARNINGS
#include "stringhelp.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "log4c.h"
#include <assert.h>
#define DEBUG 0

int nextWhite(const char* str)
{
	int i, result = -1;
	for (i = 0; result < 0 && str[i] != '\0'; i++)
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			result = i;
		}
	}
	return ((result * -1) != result) ? i : result;
}
int isNumber(const char* str, const int len)
{
	// struct Log4cStruct log = l4cOpen("log.txt", 1);
	int result;
	for (result = 1; result <= len && result; result++)
	{
		// Log: To check what type of string is being used
		// l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: isNumber() result: %d, current str: %c\n", __FILE__, __LINE__, result, str[result - 1]);
		if (!isdigit(str[result - 1])) result = -1;
	}

	// l4cClose(&log);
	return result;
}
struct StringIndex indexString(const char* str)
{
	// struct Log4cStruct log = l4cOpen("log.txt", 1);

	// Mistake 1: The number of struct initializations is incorrect.
	// struct StringIndex result = { {0}, {0}, {0}, {0}, 0, 0, 0 };
	struct StringIndex result = { {0}, {0}, {0}, 0, 0, 0 };
	char buf[MAX_WORD_SIZE + 1] = { 0 };
	int i, sp;
	strcpy(result.str, str);
	if (str[0] != '\0')
	{
		result.lineStarts[0] = 0;
		result.numLines = 1;
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		while (str[i] != '\0' && isspace(str[i]))
		{
			// Log: Use log to verify what type of whitespace this string is.
			// l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: indexString() Check if str[%d] is newline or not: %i\n", __FILE__, __LINE__, i, str[i]);
			// Mistake 2: When encountering the '\n' newline character, linestart should be incremented.
			// Origin: if (str[i] == '\0')
			if (str[i] == '\n')
			{
				result.lineStarts[result.numLines++] = i + 1;
			}
			i++;
		}

		for (sp = 0; str[sp + i] != '\0' && !isspace(str[sp + i]); sp++) {
			// Log: Use log to check if non-whitespace characters are being inspected.
			// l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: indexString() start i: %d, end sp: %d, current str: %d(ASCII)\n", __FILE__, __LINE__, i, sp, str[sp + i]);
		}

		if (isNumber(str + i, sp))
		{
			// Log: Used to verify if words composed of numbers are correctly stored in the structure.
			result.numberStarts[result.numNumbers++] = i;
		//	l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: indexString() Start index of %dth Number: %d\n", __FILE__, __LINE__, result.numNumbers - 1, i);
		}
		else
		{
			// Log: Used to verify if words composed of letters are correctly stored in the structure.
			result.wordStarts[result.numWords++] = i;
			// l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: indexString() Start index of %dth Word: %d\n", __FILE__, __LINE__, result.numWords - 1, i);
		}
		i += sp - 1;
	}

	// l4cClose(&log);
	return result;
}
int getNumberLines(const struct StringIndex* idx)
{
	return idx->numLines;
}
int getNumberWords(const struct StringIndex* idx)
{
	return idx->numWords;
}
int getNumberNumbers(const struct StringIndex* idx)
{
	return idx->numNumbers;
}
void getWord(char word[], const struct StringIndex* idx, int wordNum)
{
	// struct Log4cStruct log = l4cOpen("log.txt", 1);
	// l4cCheck(&log, "Error while opening the log.txt file");
	int i, sp, start;
	word[0] = '\0';

	if (wordNum < idx->numWords && wordNum >= 0)
	{
		start = idx->wordStarts[wordNum];
		sp = nextWhite(idx->str + start);

		// Mistake 3: When i == sp, str[sp] is either a whitespace or a string terminator, so there's no need to copy it.
		// Origin: for (i = 0; i <= sp; i++)
		for (i = 0; i < sp; i++)
		{
			// assert: Verify if accessing an index beyond the size of the 'word' array.
			assert(i < sizeof(word));
			if (sizeof(word) <= i) {
				// Log: Error log indicating that an index beyond the size of the 'word' array is being referenced.
				// l4cError(&log, "Referencing an index that exceeds the size of the word array");
				word[i - 1] = '\0';
				break;
			}
			// Log: If referencing whitespace, output a warning log. It's not a serious error -> it's a warning rather than an error.
			if (isspace(idx->str[start + i])) {
				// l4cWarning(&log, "Current idx->str[start+i] is whitespace");
			}
			// Log: Check which string is currently being referenced and what character is being stored in 'word'.
			word[i] = idx->str[start + i];
			// l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: getWord() start index: %d, end index: %d, word index: %d, current str: %c, current word[i]: %c\n", __FILE__, __LINE__, start, start + i, i, idx->str[start + i], word[i]);
		}

		// assert: Check if referencing an index beyond the size of the array.
		assert(sp < sizeof(word));
		if (sizeof(word) <= sp) {
			// Log: Error log indicating that an index beyond the size of the 'word' array is being referenced.
			// l4cError(&log, "Referencing an index that exceeds the size of the word array");
			word[sizeof(word) - 1] = '\0';
		}
		else {
			word[sp] = '\0';
		}
	}
	// l4cClose(&log);
}
void getNumber(char word[], const struct StringIndex* idx, int numberNum)
{
	// struct Log4cStruct log = l4cOpen("log.txt", 1);
	// l4cCheck(&log, "Error while opening the log.txt file");

	int i, sp, start;
	word[0] = '\0';

	if (numberNum < idx->numNumbers && numberNum >= 0)
	{
		start = idx->numberStarts[numberNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i < sp; i++)
		{
			// assert: Ensure that an index beyond the size of the 'word' array is not being referenced.
			assert(i < sizeof(word));
			if (sizeof(word) <= i) {
				// Log: Error log indicating that an index beyond the size of the 'word' array is being referenced.
				// l4cError(&log, "Referencing an index that exceeds the size of the word array");
				word[i - 1] = '\0';
				break;
			}
			// Log: If referencing whitespace, output a warning log. It's not a serious error -> so it's a warning rather than an error.
			if (isspace(idx->str[start + i])) {
				// l4cWarning(&log, "Current idx->str[start+i] is whitespace");
			}
			
			// Mistake 4: It should be str[start+i] instead of str[sp+i].
			// Origin: word[i] = idx->str[sp + i];
			word[i] = idx->str[start + i];
			// Log: Check which string is currently being referenced and which character is being stored in 'word'.
			// l4cPrintf(&log, L4C_INFO, "File:%s Line:%d Function: getNumber() start index: %d, end index: %d, word index: %d, current str: %c, current word[i]: %c\n", __FILE__, __LINE__, start, start + i, i, idx->str[start + i], word[i]);
		}

		// assert: Verify if referencing an index beyond the size of the array.
		assert(sp < sizeof(word));
		if (sizeof(word) <= sp) {
			// Log: Error log indicating that an index beyond the size of the 'word' array is being referenced.
			// l4cError(&log, "Referencing an index that exceeds the size of the word array");
			word[sizeof(word) - 1] = '\0';
		}
		else {
			word[sp] = '\0';
		}
	}
	// l4cClose(&log);
}
char* getLine(struct StringIndex* idx, int lineNum)
{
	char* result = NULL;
	if (lineNum < idx->numLines && lineNum >= 0)
	{
		result = idx->str + idx->lineStarts[lineNum];
	}
	return result;
}
void printUntil(const char* s, const int start, const char terminator)
{
	// assert: An index cannot be negative, so start >= 0 must hold true.
	assert(start >= 0);
	int i;
	for (i = start; s[i] != '\0' && s[i] != terminator; i++)
		printf("%c", s[i]);
}
void printUntilSpace(const char* s, const int start)
{
	// assert: An index cannot be negative, so start >= 0 must be true.
	assert(start >= 0);
	int i;
	for (i = start; s[i] != '\0' && !isspace(s[i]); i++)
		printf("%c", s[i]);
}