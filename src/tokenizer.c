#include <string.h>
#include <assert.h>
#include "tokenizer.h"

void init_tokenizer(Tokenizer *tokenizer, const char *source) {
	tokenizer->start = source;
	tokenizer->current = source;
	tokenizer->line = 0;
	tokenizer->indent_stack_top = 0;
}

Token scan_token(Tokenizer *tokenizer) {
	Token token;
	token.start = tokenizer->start;
	token.line = tokenizer->line;

	// TODO: figure out how to track DEDENT tokens

	switch (*token.start) {
		case '\0':
			token.type = TOKEN_EOF;
			token.length = 1;
			tokenizer->current += 1;
			break;
		case '(':
			token.type = TOKEN_LEFT_PAREN;
			token.length = 1;
			tokenizer->current += 1;
			break;
		case ')':
			token.type = TOKEN_RIGHT_PAREN;
			token.length = 1;
			tokenizer->current += 1;
			break;
		case ':':
			token.type = TOKEN_COLON;
			token.length = 1;
			tokenizer->current += 1;
			break;
		case '\n':
			token.type = TOKEN_NEWLINE;
			token.length = 1;
			tokenizer->current += 1;
			tokenizer->line += 1;
			break;
		case '"':
			token.type = TOKEN_STRING;
			token.length = 1;
			tokenizer->current += 1;
			while (*tokenizer->current != '"') {
				token.length += 1;
				tokenizer->current += 1;
			}
			// start processing after the "
			tokenizer->current += 1;
			break;
		case '\t':
			token.type = TOKEN_INDENT;
			token.length = 1;
			tokenizer->current += 1;
			break;
		default:
			// ignore white space
			while (*tokenizer->current == ' ') {
				tokenizer->current += 1;
			}
			token.start = tokenizer->current;
			
			// collect the full length of the identifier
			token.length = 0;
			while (*tokenizer->current != ' ') {
				tokenizer->current += 1;
				token.length += 1;
			}
			
			// check if def or identifier
			const char* def_str = "def";
			if (token.length == 3 && strncmp(token.start, def_str, token.length) == 0) {
				token.type = TOKEN_DEF;
			} else {
				token.type = TOKEN_IDENTIFIER;
			}
			
			break;
	}

	return token;
}
