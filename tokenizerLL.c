/*
 * tokenizer.c
 */
#include <stdio.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {

	int numTokens; //number of total tokens in the tokenizer 
	TokenT * firstToken; //pointer to the first token from left to right; "head" of the linked list of tokens
	TokenT * currentToken; //keeps track of where the current token being used by the program is, so can easily get to the next one. needs to be updated each switch.
};

/* 
 * Struct for individual tokens contains information 
 * about the type of token, its content, 
 * and a pointer to the next token from left to right.
 */

struct TokenT_ {
	char[] tokenType; //the type of the individual token-- word, decimal integer, octal integer, hexadecimal integer, or keyword.
	char[] tokenContent; //actual string content of the token itself
	char * nextToken; //pointer to the next token of the linked list
}

typedef struct TokenizerT_ TokenizerT;
typedef struct TokenT_ TokenT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

	return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

	return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

	//Make sure the program has been given input as exactly one string
	if(argc==0)
		printf("ERROR: No input given.\n");
		printf("Usage: tokenizer \"input string\"\n");
		return 1;
	if(argc>1)
		printf("Error: this program is designed to take one string of tokens as input at a time.\n");
		printf("Usage: tokenizer \"input string\"\n");
		return 1;

	//Create the tokens in TokenizerT struct
	TokenizerT tokens = TKCreate(*argv[1]);

	return 0;
}

/* Notes. 
-The tokenizer program will take in a string of input and break it down into tokens, checking along the way to make sure all the input is valid. 
	It will put each token into a single node of a linked list of tokens, the tokenizer 'object.' 
	The program can then easily read through the tokens one by one and print the type and content on separate lines. 
-The trickiest part of the tokenizer will be breaking the string into its component tokens properly.
	It needs to identify the tokens start and stop points by its type? 
*/
