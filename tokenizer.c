/*
 * tokenizer.c
 */
#include <stdio.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    char *inputStream;
    char *tokenBuffer;
};

typedef struct TokenizerT_ TokenizerT;

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
    // TODO: use strcpy to copy input stream ts
    TokenizerT *newTokenizer = malloc(sizeof(TokenizerT));
    
    streamSize = strlen(ts);
    newTokenizer->inputStream = malloc(sizeof(char) * streamSize);
    newTokenizer->tokenBuffer = malloc(sizeof(char)*1000);
    
    return newTokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk->inputStream);
    free(tk->tokenBuffer);
    free(tk);
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

char *TKGetNextToken(TokenizerT *tk) {
    // TODO: initial states
    return NULL;
}

/******************************************/
/*************** Token States *************/
/******************************************/

void _zero(*tk)


/******************************************/
/************ End Token States ************/
/******************************************/

/*
 * Prints either a word or a reserved word
 */

void printWord(char *word) {
    const char *reservedWords[28];
    reservedWords[0] = "auto";
    reservedWords[1] = "break";
    reservedWords[2] = "case";
    reservedWords[3] = "char";
    reservedWords[4] = "continue";
    reservedWords[5] = "default";
    reservedWords[6] = "do";
    reservedWords[7] = "double";
    reservedWords[8] = "else";
    reservedWords[9] = "entry";
    reservedWords[10] = "extern";
    reservedWords[11] = "float";
    reservedWords[12] = "for";
    reservedWords[13] = "goto";
    reservedWords[14] = "if";
    reservedWords[15] = "int";
    reservedWords[16] = "long";
    reservedWords[17] = "register";
    reservedWords[18] = "return";
    reservedWords[19] = "short";
    reservedWords[20] = "sizeof";
    reservedWords[21] = "static";
    reservedWords[22] = "struct";
    reservedWords[23] = "switch";
    reservedWords[24] = "typedef";
    reservedWords[25] = "union";
    reservedWords[26] = "unsigned";
    reservedWords[27] = "while";
    
    int 
    int rWordIndex = 0;
    for(; rWordIndex < 28; rWordIndex++) {
        if(strcmp(word, reservedWords[rWordIndex]) == 0) {
            // TODO: compare, make bool isReserved, then print word
        }
    }
}


/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

  return 0;
}
