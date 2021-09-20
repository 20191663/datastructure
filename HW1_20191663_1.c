#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1000

// check c if it's Open Parenthesis (, {, [
int IsOpenParen(char c)
{
	if (c == '(' || c == '{' || c == '[')
		return 1;
	else
		return 0;
}

// check c if it's Close Parenthesis ), }, ]
int IsCloseParen(char c)
{
	if (c == ')' || c == '}' || c == ']')
		return 1;
	else
		return 0;
}

// add char into newstr
void AddChar(char* newstr, char c)
{
	int len = strlen(newstr);
	newstr[len] = c;
}

// get Open Parenthesis from matched Close Parenthesis(paren)
char GetMatchingOpenParen(char paren)
{
	switch (paren)
	{
	case ')':
		return '(';
	case '}':
		return '{';
	case ']':
		return '[';
	}
}

// get Close Parenthesis from matched Open Parenthesis(paren)
char GetMatchingCloseParen(char paren)
{
	switch (paren)
	{
	case '(':
		return ')';
	case '{':
		return '}';
	case '[':
		return ']';
	}
}

// insert parenthesis into well performed paranthesis.
void InsertParen(char* str, char* newstr, int index)
{
	if (IsCloseParen(str[index]))
		AddChar(newstr, GetMatchingOpenParen(str[index]));
	AddChar(newstr, str[index]);
	if (IsOpenParen(str[index]))
		AddChar(newstr, GetMatchingCloseParen(str[index]));
}

void Max(int* pair, int* first, int* last) {
	if (pair[1] - pair[0] > *last - *first) {
		*last = pair[1];
		*first = pair[0];
	}
}

// find biggest pair of parenthesis form start to end, save location into first and last.
void BigPair(char* str, int start, int end, int* first, int* last)
{
	int l[2], m[2], s[2], b[2];	//large, mideum, small, big_pair [] {} ()
	l[0] = l[1] = m[0] = m[1] = s[0] = s[1] = -1;
	for (int i = start; i <= end; i++) {
		switch (str[i]) {
		case '[': if (l[0] == -1) { l[0] = i; } break;
		case '{': if (m[0] == -1) { m[0] = i; } break;
		case '(': if (s[0] == -1) { s[0] = i; } break;
		case ']': if (l[0] != -1) { l[1] = i; } break;
		case '}': if (m[0] != -1) { m[1] = i; } break;
		case ')': if (s[0] != -1) { s[1] = i; }
		default: continue;
		}
	}

	Max(l, first, last);
	Max(m, first, last);
	Max(s, first, last);
}

void FindPair(char* str, char* newstr, int start, int end)
{
	if (start > end)
		return;
	int first = -1, last = -1;
	BigPair(str, start, end, &first, &last);
	if (last == -1)	//pair isn't exists where start to end.
	{
		for (int i = start; i <= end; i++)
			InsertParen(str, newstr, i);
	}
	else
	{
		FindPair(str, newstr, start, first - 1);
		AddChar(newstr, str[first]);
		FindPair(str, newstr, first + 1, last - 1);
		AddChar(newstr, str[last]);
		FindPair(str, newstr, last+1, end);
	}
}

int main()
{
	char str[MAX_STRING_LENGTH] = { 0 };			//input string
	char openParens[MAX_STRING_LENGTH / 2] = { 0 };	//get open parenthesis only
	char newstr[MAX_STRING_LENGTH * 2] = { 0 };		//output string
	int numOP = 0;			//checking number of open parenthesis
	int index = 0;			//checking input string index

	//get string and save length
	scanf("%s", str);
	int startLength = strlen(str);

	//recursive function to fix string from start to end.
	FindPair(str, newstr, 0, strlen(str)-1);

	//print whether well formed or not(if not, also print fixed string)
	if ((int)strlen(newstr) == startLength)
		printf("well formed string\n");
	else
		printf("not well formed string\n추가되는 괄호 수 : %d\n%s\n", (int)strlen(newstr) - startLength, newstr);
	return 0;
}
