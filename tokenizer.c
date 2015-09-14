/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


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
};

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
    
    long int streamSize = strlen(ts) + 1;
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
    assert(tk != NULL);

    free(tk->inputStream);
    free(tk->tokenBuffer);
    free(tk);
}


void nextChar(TokenizerT *tk) {
    tk->bufferIter[0] = tk->inputIter[0];  // move new char to end of buffer
    tk->inputIter++;                       // move the input iterator over
    tk->bufferIter++;                      // move the buffer iterator over
    tk->bufferIter[0] = '\0';              // add a null to the end of buffer
    tk->bufferSize++;                      // increase bufferSize accordingly
    if(tk->bufferSize == 999) {
        // TODO: exit gracefully
        exit(1);
    }
}

void clearBuffer(TokenizerT *tk) {
    tk->tokenBuffer[0] = '\0';  // immediately end the string
    tk->bufferSize = 0;
    tk->bufferIter = tk->tokenBuffer;
}


/*
 * Prints either a word or a reserved word
 */
int isReservedWord(char *word) {
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
    
    return isReservedWord;
}


/*
 * Make a token struct from the current state of the tokenizer and the 
 * identified type.
 */
TokenT *makeToken(TokenizerT *tk, char *type) {
    TokenT *token = (TokenT *) malloc(sizeof(TokenT));
    
    token->text = (char *) malloc(sizeof(char) * 1000);
    strcpy(token->text, tk->tokenBuffer);
    
    token->type = (char *) malloc(sizeof(char) * 50);
    strcpy(token->type, type);

    return token;
}


void destroyToken(TokenT *token) {
    free(token->text);
    free(token->type);
    free(token);
}


/*
 * Print a token. Used in main loop.
 */
void printToken(TokenT *token) {
    printf("%s \"%s\"\n", token->type, token->text);
}


/******************************************/
/*************** Token States *************/
/******************************************/


// TODO: remove unnecessary recursion for multiple chars in a row
TokenT *_word(TokenizerT *tk) {
    nextChar(tk);
    if(isalnum(tk->inputIter[0])) {
        return _word(tk);
    } else {  // end of token
        if(isReservedWord(tk->tokenBuffer)) {
            return makeToken(tk, "word");
        } else {
            return makeToken(tk, "reserved word");
        }
    }
}

//function to handle being given a zero as the first char in a new token
TokenT *_zero(TokenizerT *tk) {
    nextChar(tk);
    if((tk->inputIter)>=0 && (tk->inputIter)<=7 ) {
        return _octal(tk);
    }
    if((tk->inputIter)=='x' || (tk->inputIter)=='X'){
        int isFirst = 1;
        return _hex(tk, 1);
    }
    if((tk->inputIter)=='.'){
        return _float(tk);
    }
    else {
        return makeToken(tk, "zero");
    }
}

//function for handling octal numbers
TokenT *_octal(TokenizerT *tk) {

}

//function for handling hex numbers
TokenT *_hex(TokenizerT *tk, int isFirst) {
    nextChar(tk);
    if((isxdigit(tk->inputIter))){
        return _hex(tk);
    }
    else {
        if(isFirst = 1) {
            //TODO: ERROR MESSAGE HERE
        }
        else {
            return makeToken(tk, "hexadecimal number");
        }
    }
}

//function for handling floating point numbers
TokenT *_float(TokenizerT *tk) {

}

//function for handling floating point numbers involving exponents
TokenT *_expofloat(TokenizerT *tk) {

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
    char curr = tk->inputIter[0];
    
    // skip all whitespace before next token
    while(isspace(curr)) {
        nextChar(tk);
        clearBuffer(tk);
    }

    if(curr == '\0') {
        return NULL;
    } else if(isalpha(curr) || curr == '_') {
        return _word(tk);
    //} else if(curr == '0') {
    //    return _zero(tk)
    } else {
        return NULL;
        // TODO: figure out how to handle invalid char
    }
    // TODO: all initial states for tokens
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
    // make sure theres exactly 1 argument
    if(argc != 2) {
        printf("Invalid number of arguments. \n");
        printf("Usage: \n    ./tokenizer <C-code string>\n");
        exit(1);
    }

    TokenizerT *tokenizer = TKCreate(argv[1]);
    
    TokenT *token;
    while((token = TKGetNextToken(tokenizer)) != NULL) {
        printToken(token);
        destroyToken(token);
    }

    TKDestroy(tokenizer);

    return 0;
}

