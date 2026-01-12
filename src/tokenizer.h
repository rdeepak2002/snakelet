#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>
typedef enum {
	DEF,            // 'def' part of defining a function
	IDENTIFIER, 	// ex: print, main, etc.
	LEFT_PAREN, 	// ex: (
	COLON,		// ex: :
	STRING,	    	// ex: "Hello World"
	RIGHT_PAREN,  	// ex: )
	NEWLINE,
	INDENT, 	// indentation
	DEDENT, 	// undoing indentation
	EOF
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
} Tokenizer;

void init_tokenizer(Tokenizer *tokenizer, const char *source);

Token scan_token(Tokenizer *tokenizer);

#endif // TOKENIZER_H

