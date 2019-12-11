#include "Keyword.hpp"

KeywordType key_filtr(const Chain & str) {
	#ifdef WIDE
	if(str == L"loop") return KeywordType::t_loop;
	if(str == L"return") return KeywordType::t_return;
	if(str == L"end") return KeywordType::t_end;
	return KeywordType::t_none;
	#else
	if(str == "loop") return KeywordType::t_loop;
	if(str == "return") return KeywordType::t_return;
	if(str == "end") return KeywordType::t_end;
	return KeywordType::t_none;
	#endif
	//symbole (enumy) sobie można obejrzeć w debugerze
}
