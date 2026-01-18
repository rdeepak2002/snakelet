#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../src/tokenizer.h"

int validate_token(Token actual, TokenType expected_type, char *expected_value) {
	if (actual.type != expected_type) {
		printf("Expected token type: %d, Actual token type: %d\n", expected_type, actual.type);
		return 0;
	}
	
	size_t expected_length = strlen(expected_value);
	
	if (actual.length != expected_length) {
		printf("Expected token length: %d, Actual token length: %d\n", (int) expected_length, actual.length);
		return 0;
	}

	if (strncmp(actual.start, expected_value, expected_length)) {

		printf("Expected token: %s\n", expected_value);
		return 0;
	}

	return 1;
}

int main() {
	Tokenizer tokenizer;
	char* source = "def main():\n\tprint(\"Hello world\")\n\tprint(-1 + 29 - 103)\n\n";
	init_tokenizer(&tokenizer, source);
	assert(validate_token(scan_token(&tokenizer), TOKEN_DEF, "def"));
	assert(tokenizer.line == 0);
	assert(validate_token(scan_token(&tokenizer), TOKEN_IDENTIFIER, "main"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_LEFT_PAREN, "("));
	assert(validate_token(scan_token(&tokenizer), TOKEN_RIGHT_PAREN, ")"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_COLON, ":"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NEWLINE, "\n"));

	assert(tokenizer.line == 1);
	assert(validate_token(scan_token(&tokenizer), TOKEN_INDENT, "\t"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_IDENTIFIER, "print"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_LEFT_PAREN, "("));
	assert(validate_token(scan_token(&tokenizer), TOKEN_STRING, "\"Hello world\""));
	assert(validate_token(scan_token(&tokenizer), TOKEN_RIGHT_PAREN, ")"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NEWLINE, "\n"));


	assert(tokenizer.line == 2);
	assert(validate_token(scan_token(&tokenizer), TOKEN_IDENTIFIER, "print"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_LEFT_PAREN, "("));
	assert(validate_token(scan_token(&tokenizer), TOKEN_MINUS, "-"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NUMBER, "1"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_PLUS, "+"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NUMBER, "29"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_MINUS, "-"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NUMBER, "103"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_RIGHT_PAREN, ")"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NEWLINE, "\n"));


	assert(tokenizer.line == 3);
	assert(tokenizer.indent_stack_top == 1);
	assert(tokenizer.indent_stack[tokenizer.indent_stack_top - 1] == 4);
	assert(validate_token(scan_token(&tokenizer), TOKEN_DEDENT, ""));
	assert(validate_token(scan_token(&tokenizer), TOKEN_NEWLINE, "\n"));

	assert(tokenizer.line == 4); 
	// end of file returns the same token if called repeatedly
	assert(validate_token(scan_token(&tokenizer), TOKEN_EOF, "\0"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_EOF, "\0"));
	assert(validate_token(scan_token(&tokenizer), TOKEN_EOF, "\0"));
	return 0;
}
