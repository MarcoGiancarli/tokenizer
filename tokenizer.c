/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
    char *inputStream;
    char *tokenBuffer;
    char *inputIter;
    char *bufferIter;
    int bufferSize;
};

struct TokenT_ {
    char *text;
    char *type;
}

typedef struct TokenT_ TokenT;
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
TokenizerT *TKCreate(char *ts) {
    // TODO: use strcpy to copy input stream ts
    TokenizerT *newTokenizer = (TokenizerT *) malloc(sizeof(TokenizerT));
    
    streamSize = strlen(ts);
    newTokenizer->inputStream = (char *) malloc(sizeof(char) * streamSize);
    strcpy(newTokenizer->inputStream, ts);
    newTokenizer->inputIter = newTokenizer->inputStream;
    
    newTokenizer->bufferSize = 0;
    newTokenizer->tokenBuffer = (char *) malloc(sizeof(char) * 1000);
    strcpy(newTokenizer->tokenBuffer, "");  // empty string means this just puts '\0' as the first char
    newTokenizer->bufferIter = newTokenizer->tokenBuffer;
    
    return newTokenizer;
}


/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */
void TKDestroy(TokenizerT *tk) {
    assert(tk != NULL)

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
TokenT *TKGetNextToken(TokenizerT *tk) {
    char curr = &tk->inputIter;

    if(isalpha(curr) || curr == '_') {
        return _word(tk)
    }
    // TODO: initial states
}

void nextChar(TokenizerT *tk) {
    //  1. add one char to buffer, move the bufferIter over by one, move back \0 by one, increment bufferSize
    //  2. if buffer size is 999, exit the program gracefully
    //  3. move the inputIter over by one
    //  4. if the inputIter pointer points to '\0', end the TKGetNextToken call gracefully
    tk->bufferIter[0] = tk->[0];
    tk->bufferIter[1] = '\0';
    tk->bufferSize++;
    if(tk->bufferSize == 999) {
        // TODO: exit gracefully
    }
    tk->inputIter++;
}

void clearBuffer(TokenizerT *tk) {
    tk->tokenBuffer = "";  // empty string means this just puts '\0' as the first char
    tk->bufferSize = 0;
    tk->bufferIter = tk->tokenBuffer;
}


/*
 * Prints either a word or a reserved word
 */
void isReservedWord(TokenizerT *tk) {
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
    
    int isReservedWord = 0;
    int rWordIndex = 0;
    for(; rWordIndex < 28; rWordIndex++) {
        if(strcmp(word, reservedWords[rWordIndex]) == 0) {
            isReservedWord = 1;
        }
    }
    
    return isReservedWord
}


/*
 * Make a token struct from the current state of the tokenizer and the 
 * identified type.
 */
TokenT *makeToken(TokenizerT *tk, char *type) {
    TokenT *token = malloc(sizeof(TokenT));
    
    token->text = malloc(sizeof(char) * 1000);
    strcpy(token->text, tk->tokenBuffer);
    
    token->type = malloc(sizeof(char) * 50);
    strcpy(token->type, type);

    return token
}


/******************************************/
/*************** Token States *************/
/******************************************/


TokenT *_word(TokenizerT *tk) {
    nextChar(tk);
    if(isalnum(tk->inputIter)) {
        return _word(tk);
    } else {
        // TODO: return a token struct type with a string for type and a string for the text of it.
        // TODO: make that token struct type
        if(isReservedWord(tk->tokenBuffer)) {
            return makeToken(tk, "word");
        } else {
            return makeToken(tk, "reserved word");
        }
    }
}


/******************************************/
/************ End Token States ************/
/******************************************/


/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */
int main(int argc, char **argv) {

    return 0;
}

