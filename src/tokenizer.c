#include <string.h>
#include <assert.h>
#include "tokenizer.h"

void init_tokenizer(Tokenizer *tokenizer, const char *source) {
	tokenizer->start = source;
	tokenizer->current = source;
	tokenizer->line = 0;
	tokenizer->indent_stack_top = 0;
	tokenizer->cur_indent_stack_pointer = 0;
	tokenizer->bol = 1;
}

Token scan_token(Tokenizer *tokenizer) {
	Token token;
	token.line = tokenizer->line;

	// ignore white space
	while (*tokenizer->current == ' ') {
		tokenizer->current += 1;
	}

	// no tabs in middle of line
	if (!tokenizer->bol) {
		assert(*tokenizer->current != '\t');
	}

	while (*tokenizer->current == '\t' && tokenizer->cur_indent_stack_pointer < tokenizer->indent_stack_top) {
		tokenizer->cur_indent_stack_pointer += 1;
		tokenizer->current += 1;
	}

	token.start = tokenizer->current;

	if (*token.start != '\t' && tokenizer->cur_indent_stack_pointer < tokenizer->indent_stack_top) {
		tokenizer->indent_stack_top -= 1;
		token.type = TOKEN_DEDENT;
		token.length = 0;
		return token;
	}

	tokenizer->bol = 0;

	int max_indent_stack_size = sizeof(tokenizer->indent_stack) / sizeof(tokenizer->indent_stack[0]);
	
	switch (*token.start) {
		// whitespace
		case '\t':
			assert(tokenizer->indent_stack_top <= max_indent_stack_size - 1);
			tokenizer->bol = 1; 
			token.type = TOKEN_INDENT;
			token.length = 1;
			tokenizer->current += 1;
			tokenizer->indent_stack[tokenizer->indent_stack_top] = 4;
			tokenizer->indent_stack_top += 1;
			tokenizer->cur_indent_stack_pointer += 1;
			break;
		case '\0':
			tokenizer->bol = 1;
			token.type = TOKEN_EOF;
			token.length = 0;
			break;
		case '\n':
			tokenizer->bol = 1;
			token.type = TOKEN_NEWLINE;
			token.length = 1;
			tokenizer->current += 1;
			tokenizer->line += 1;
			tokenizer->cur_indent_stack_pointer = 0;
			break;
		// non-whitespace
		case '+':
			token.type = TOKEN_PLUS;
			token.length = 1;
			tokenizer->current += 1;
			break;
		case '-':
			token.type = TOKEN_MINUS;
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
		case '"':
			token.type = TOKEN_STRING;
			token.length = 1;
			tokenizer->current += 1;
			while (*tokenizer->current != '"') {
				assert(*tokenizer->current != '\0');
				assert(*tokenizer->current != '\n');
				token.length += 1;
				tokenizer->current += 1;
			}

			// include closing "
			token.length += 1;
			tokenizer->current += 1;

			break;
		default:	
			// collect the full length of the identifier
			token.length = 0;
			int only_numbers = 1;
			int first_val_is_num = 0;
			int first_val_is_zero = 0;
			

			if (*tokenizer->current >= '0' && *tokenizer->current <= '9') {
				first_val_is_num = 1;
				if (*tokenizer->current == '0') {
					first_val_is_zero = 1;
				}
			}

			while (*tokenizer->current != ' ' && *tokenizer->current != '\n' && *tokenizer->current != '(' && *tokenizer->current != ')' && *tokenizer->current != ':' && *tokenizer->current != '"' && *tokenizer->current != '\t' && *tokenizer->current != '\0' && *tokenizer->current != '+' && *tokenizer->current != '-') {
				if (*tokenizer->current < '0' || *tokenizer->current > '9') {
					only_numbers = 0;
				}
				tokenizer->current += 1;
				token.length += 1;
			}
			
			// check if def or identifier
			const char* def_str = "def";
			if (token.length == 3 && strncmp(token.start, def_str, token.length) == 0) {
				token.type = TOKEN_DEF;
			} else if (only_numbers) {
				assert(!first_val_is_zero);
				token.type = TOKEN_NUMBER;
			} else {
				assert(!first_val_is_num);
				token.type = TOKEN_IDENTIFIER;
			}
			
			break;
	}

	return token;
}
