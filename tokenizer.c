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
    
    long int streamSize = strlen(ts) + 2;
    newTokenizer->inputStream = (char *) malloc(sizeof(char) * streamSize);
    strcpy(newTokenizer->inputStream, ts);
    newTokenizer->inputIter = newTokenizer->inputStream;

    newTokenizer->bufferSize = 0;
    newTokenizer->tokenBuffer = (char *) malloc(sizeof(char) * 1000);
    strcpy(newTokenizer->tokenBuffer, "");  // end the buffer with this null byte
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
    tk->bufferIter[0] = tk->inputIter[0];  // copy new char to end of buffer
    tk->inputIter++;                       // move the input iterator over
    tk->bufferIter++;                      // move the buffer iterator over
    tk->bufferIter[0] = '\0';              // add a null to the end of buffer
    tk->bufferSize++;                      // increase bufferSize accordingly
    if(tk->bufferSize == 999) {
        // TODO: exit gracefully
        exit(1);
    }
    //printf("BI:%s   TB:%s   II:%s   IS:%s\n", tk->bufferIter, tk->tokenBuffer, tk->inputStream, tk->inputIter);
    assert(strlen(tk->bufferIter) == 0);
}

void clearBuffer(TokenizerT *tk) {
    tk->bufferSize = 0;
    tk->bufferIter = tk->tokenBuffer;
    tk->bufferIter[0] = '\0';  // immediately end the string
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

// ***** HUGE TODO: make sure to handle if the input stream ends abruptly *****


TokenT *_invalid(TokenizerT *tk) {
    nextChar(tk);
    return makeToken(tk, "invalid token");
}

// TODO: remove unnecessary recursion for multiple chars in a row
TokenT *_word(TokenizerT *tk) {
    nextChar(tk);
    if(isalnum(tk->inputIter[0])) {
        return _word(tk);
    } else {  // end of token
        if(isReservedWord(tk->tokenBuffer)) {
            return makeToken(tk, "reserved word");
        } else {
            return makeToken(tk, "word");
        }
    }
}

TokenT *_neq(TokenizerT *tk) {
    nextChar(tk);
    if(tk->inputIter[0] == '=') {
        nextChar(tk);
        return makeToken(tk, "not-equals operator");
    } else {
        nextChar(tk);
        return _invalid(tk);
    }
}

TokenT *_double_quote(TokenizerT *tk) {
    nextChar(tk);
    while(tk->inputIter[0] != '"') {
        if(tk->inputIter[0] == '\\') {
            nextChar(tk);
        }
        nextChar(tk);
    }
    nextChar(tk);
    return makeToken(tk, "string");
}

TokenT *_mod(TokenizerT *tk) {
    nextChar(tk);
    if(tk->inputIter[0] == '=') {
        nextChar(tk);
        return makeToken(tk, "mod-equals operator");
    } else {
        return makeToken(tk, "mod operator");
    }
}

TokenT *_bit_and(TokenizerT *tk) {
    nextChar(tk);
    if(tk->inputIter[0] == '=') {
        nextChar(tk);
        return makeToken(tk, "and-equals operator");
    } else if(tk->inputIter[0] == '&') {
        nextChar(tk);
        return makeToken(tk, "logical-and operator");
    } else {
        return makeToken(tk, "bitwise-and operator");
    }
}

TokenT *_single_quote(TokenizerT *tk) {
    nextChar(tk);
    if(tk->inputIter[0] != '\\') {
        nextChar(tk);
        if(tk->inputIter[0] == '\'') {
            nextChar(tk);
            return makeToken(tk, "");
        } else {
            nextChar(tk);
            return 0;  // TODO: finish this whole function from here down
        }
        return makeToken(tk, "");
    } else if(tk->inputIter[0] == '&') {
        nextChar(tk);
        return makeToken(tk, "");
    } else {
        return makeToken(tk, "");
    }
}

TokenT *_open_paren(TokenizerT *tk) {
    return 0;
}

TokenT *_close_paren(TokenizerT *tk) {
    return 0;
}

TokenT *_mult(TokenizerT *tk) {
    return 0;
}

TokenT *_plus(TokenizerT *tk) {
    return 0;
}

TokenT *_comma(TokenizerT *tk) {
    return 0;
}

TokenT *_minus(TokenizerT *tk) {
    return 0;
}

TokenT *_dot(TokenizerT *tk) {
    return 0;
}

TokenT *_div(TokenizerT *tk) {
    return 0;
}

TokenT *_ternary_colon(TokenizerT *tk) {
    return 0;
}

TokenT *_semicolon(TokenizerT *tk) {
    return 0;
}

TokenT *_lt(TokenizerT *tk) {
    return 0;
}

TokenT *_eq(TokenizerT *tk) {
    return 0;
}

TokenT *_gt(TokenizerT *tk) {
    return 0;
}

TokenT *_ternary_qmark(TokenizerT *tk) {
    return 0;
}

TokenT *_open_bracket(TokenizerT *tk) {
    return 0;
}

TokenT *_close_bracket(TokenizerT *tk) {
    return 0;
}

TokenT *_bit_xor(TokenizerT *tk) {
    return 0;
}

TokenT *_open_brace(TokenizerT *tk) {
    return 0;
}

TokenT *_bit_or(TokenizerT *tk) {
    return 0;
}

TokenT *_close_brace(TokenizerT *tk) {
    return 0;
}

TokenT *_bit_not(TokenizerT *tk) {
    return 0;
}

//function for handling floating point numbers involving exponents
TokenT *_expofloat(TokenizerT *tk, int isFirst, int lastWasSign) {
  nextChar(tk);
  if(isdigit(tk->inputIter)) {
    return _expofloat(tk, 0, 0);
  }
  else if((tk->inputIter) == '+' || (tk->inputIter) == '-') {
    if(isFirst == 1){
      return _expofloat(tk, 0, 1);
    }
    else if(lastWasSign == 1) {
      //TODO ERROR MESSAGE HERE
    }
    else {
      return makeToken(tk, "floating point number with exponent");
    }
  }
  else {
    if(isFirst==1) {
      //TODO ERROR MESSAGE HERE
    }
    else if(lastWasSign == 1) {
      //TODO ERROR MESSAGE HERE
    }
    else {
      return makeToken(tk, "floating point number with exponent");
    }
  }
}

//function for handling floating point numbers
TokenT *_float(TokenizerT *tk, int isFloat) {
  nextChar(tk);
  if(isdigit(tk->inputIter)){
    return _float(tk, 0);
  }
  else if((tk->inputIter) == 'e' || (tk->inputIter) == 'E') {
    return _expofloat(tk, 1, 0);
  }
  else {
    if(isFirst == 1){
      //TODO: ERROR MESSAGE HERE
    }
    else{
      return makeToken(tk, "floating point number");
    }
  }
}

//function for handling octal numbers
TokenT *_octal(TokenizerT *tk) {
  nextChar(tk);
  if((tk->inputIter)>='0' && (tk->inputIter)<='7' ) {
      return _octal(tk);
  }
  else {
    return makeToken(tk, "octal number");
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
    clearBuffer(tk);
    char curr = tk->inputIter[0];

    // skip all whitespace before next token
    while(isspace(curr)) {
        nextChar(tk);
        clearBuffer(tk);
        curr = tk->inputIter[0];
    }

    if(curr == '\0') {
        return NULL;
    } else if(isalpha(curr) || curr == '_') {
        return _word(tk);
    //} else if(curr == '0') {
    //    return _zero(tk)
    } else if(curr == '!') { // neq
        return _neq(tk);
    } else if(curr == '"') { // double_quote
        return _double_quote(tk);
    } else if(curr == '#') { // INVALID
        return _invalid(tk);
    } else if(curr == '$') { // INVALID
        return _invalid(tk);
    } else if(curr == '%') { // mod, mod_eq
        return _mod(tk);
    } else if(curr == '&') { // bit_and, log_and, address (?)
        return _bit_and(tk);
    } else if(curr == '\'') { // single_quote
        return _single_quote(tk);
    } else if(curr == '(') { // open_paren
        return _open_paren(tk);
    } else if(curr == ')') { // close_paren
        return _close_paren(tk);
    } else if(curr == '*') { // mult, mult_eq, pointer (?)
        return _mult(tk);
    } else if(curr == '+') { // plus, plus_eq, inc
        return _plus(tk);
    } else if(curr == ',') { // comma
        return _comma(tk);
    } else if(curr == '-') { // minus, minus_eq, dec, struct_pointer
        return _minus(tk);
    } else if(curr == '.') { // dot
        return _dot(tk);
    } else if(curr == '/') { // div, div_eq
        return _div(tk);
    } else if(curr == ':') { // ternary_colon
        return _ternary_colon(tk);
    } else if(curr == ';') { // semicolon
        return _semicolon(tk);
    } else if(curr == '<') { // lt, lshift, lt_eq
        return _lt(tk);
    } else if(curr == '=') { // eq, assign
        return _eq(tk);
    } else if(curr == '>') { // gt, rshift, gt_eq
        return _gt(tk);
    } else if(curr == '?') { // ternary_qmark
        return _ternary_qmark(tk);
    } else if(curr == '@') { // INVALID
        return _invalid(tk);
    } else if(curr == '[') { // open_bracket
        return _open_bracket(tk);
    } else if(curr == '\\') { // backslash (?)
        return _invalid(tk);
    } else if(curr == ']') { // close_bracket
        return _close_bracket(tk);
    } else if(curr == '^') { // bit_xor
        return _bit_xor(tk);
    } else if(curr == '`') { // INVALID
        return _invalid(tk);
    } else if(curr == '{') { // open_brace
        return _open_brace(tk);
    } else if(curr == '|') { // bit_or, log_or
        return _bit_or(tk);
    } else if(curr == '}') { // close_brace
        return _close_brace(tk);
    } else if(curr == '~') { // bit_not
        return _bit_not(tk);
    } else {
        return _invalid(tk);
        // TODO: figure out how to handle invalid char
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
