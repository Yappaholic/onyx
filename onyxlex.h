#ifndef ONYXLEX_H
#define ONYXLEX_H

#include "bh.h"

typedef struct OnyxTokenizer {
	char *start, *curr, *end;

	// TODO: Fix the line number and column count
	char* line_start;
	u64 line_number;

	bh_hash(u16) symbol_count;
} OnyxTokenizer;

typedef enum OnyxTokenType {
	TOKEN_TYPE_UNKNOWN,
	TOKEN_TYPE_END_STREAM,

	TOKEN_TYPE_COMMENT,

	TOKEN_TYPE_KEYWORD_STRUCT,
	TOKEN_TYPE_KEYWORD_USE,
	TOKEN_TYPE_KEYWORD_EXPORT,
	TOKEN_TYPE_KEYWORD_IF,
	TOKEN_TYPE_KEYWORD_ELSE,
	TOKEN_TYPE_KEYWORD_FOR,
	TOKEN_TYPE_KEYWORD_DO,
	TOKEN_TYPE_KEYWORD_RETURN,
	TOKEN_TYPE_KEYWORD_FOREIGN,
	TOKEN_TYPE_KEYWORD_PROC,
	TOKEN_TYPE_KEYWORD_GLOBAL,

	TOKEN_TYPE_RIGHT_ARROW,
	TOKEN_TYPE_LEFT_ARROW,
	TOKEN_TYPE_OPEN_PAREN,
	TOKEN_TYPE_CLOSE_PAREN,
	TOKEN_TYPE_OPEN_BRACE,
	TOKEN_TYPE_CLOSE_BRACE,
	TOKEN_TYPE_OPEN_BRACKET,
	TOKEN_TYPE_CLOSE_BRACKET,
	TOKEN_TYPE_OPEN_ANGLE,
	TOKEN_TYPE_CLOSE_ANGLE,

	TOKEN_TYPE_SYM_PLUS,
	TOKEN_TYPE_SYM_MINUS,
	TOKEN_TYPE_SYM_STAR,
	TOKEN_TYPE_SYM_PERCENT,
	TOKEN_TYPE_SYM_FSLASH,
	TOKEN_TYPE_SYM_BSLASH,
	TOKEN_TYPE_SYM_TYPE_SIGNATURE,
	TOKEN_TYPE_SYM_COLON,
	TOKEN_TYPE_SYM_SEMICOLON,
	TOKEN_TYPE_SYM_COMMA,
	TOKEN_TYPE_SYM_EQUALS,
	TOKEN_TYPE_SYM_GRAVE,
	TOKEN_TYPE_SYM_TILDE,
	TOKEN_TYPE_SYM_BANG,
	TOKEN_TYPE_SYM_CARET,
	TOKEN_TYPE_SYM_AMPERSAND,

	TOKEN_TYPE_SYMBOL,
	TOKEN_TYPE_LITERAL_STRING,
	TOKEN_TYPE_LITERAL_NUMERIC,

	TOKEN_TYPE_COUNT
} OnyxTokenType;

typedef struct OnyxToken {
	OnyxTokenType type;
	char* token;
	isize length;
	u64 line_number, line_column;
} OnyxToken;

const char* onyx_get_token_type_name(OnyxToken tkn);
OnyxToken onyx_get_token(OnyxTokenizer* tokenizer);
bh_arr(OnyxToken) onyx_parse_tokens(bh_file_contents *fc, bh_hash(u16) symcount);

#endif