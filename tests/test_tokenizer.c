#include <assert.h>
#include <string.h>
#include "../src/tokenizer.h"

int validate_token(Token actual, TokenType expected_type, char *expected_value) {
	if (actual.type != expected_type) {
		return 0;
	}
	
	size_t expected_length = strlen(expected_value);
	
	if (actual.length != expected_length) {
		return 0;
	}

	if (strncmp(actual.start, expected_value, expected_length)) {
		return 0;
	}

	return 1;
}

int main() {
	Tokenizer tokenizer;
	char* source = "def main():\n\tprint(\"Hello world\")\n";
	init_tokenizer(&tokenizer, source);
	// TODO: also check token.start and token.length
	assert(validate_token(scan_token(&tokenizer), DEF, "def"));
	assert(validate_token(scan_token(&tokenizer), IDENTIFIER, "main"));
	assert(validate_token(scan_token(&tokenizer), LEFT_PAREN, "("));
	assert(validate_token(scan_token(&tokenizer), RIGHT_PAREN, ")"));
	// TODO: finish implementing this test
	// TODO: figure out DEDENT and implement the tests for that
	return 0;
}
