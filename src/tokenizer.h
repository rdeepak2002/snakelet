#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>
typedef enum {
	TOKEN_DEF,              // 'def' part of defining a function
	TOKEN_IDENTIFIER, 	// ex: print, main, x, foo, bar, etc. (cannot start with num)
	TOKEN_LEFT_PAREN, 	// ex: (
	TOKEN_COLON,		// ex: :
	TOKEN_STRING,	    	// ex: "Hello World"
	TOKEN_NUMBER,           // ex: 123
	TOKEN_RIGHT_PAREN,  	// ex: )
	TOKEN_PLUS,             // ex: +
	TOKEN_MINUS,	        // ex: -
	TOKEN_NEWLINE,          // new line
	TOKEN_INDENT, 	        // indentation
	TOKEN_DEDENT, 	        // undoing indentation
	TOKEN_EOF               // end of file
} TokenType;

typedef struct {
	TokenType type;
	const char *start;
	int length;
	int line;
} Token;

typedef struct {
	const char *start;
	const char *current;
	int line;
	int indent_stack[256];
	int indent_stack_top;
	int cur_indent_stack_pointer;
	int bol;
} Tokenizer;

void init_tokenizer(Tokenizer *tokenizer, const char *source);

Token scan_token(Tokenizer *tokenizer);

#endif // TOKENIZER_H

