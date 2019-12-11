#pragma once
#include <string>
#include <vector>
#include <cwchar>
#include "WideCharacter.hpp"
#include "Operators.hpp"
#include "Keyword.hpp"
enum class TokenType {
	id, op, keyword, nume, comment, mistake
};

std::wstring to_string(const TokenType type);

class Token {
	TokenType myType;
	Chain content;
	union {
		KeywordType keyword;
		OperatorType op;
	};
	public:
	Token(const TokenType myType, const Chain & content):
		myType(myType),
		content(content)
		{
		analize();
		}
	std::wstring to_string() const;
	void analize();
};

class TokenList {
	std::vector<Token> list;
	public:
	void append(const Token token) {
		list.push_back(token);
	}
	void printTokens() {
		for(auto & token : list) {
			wprintf(L"%ls", (token.to_string() + (wchar_t)'\n').c_str());
		}
	}
	Token last() const {
		return list.at(list.size() - 1);
	}
			
};
