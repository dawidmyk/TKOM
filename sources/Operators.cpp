#include "Operators.hpp"
Operators Operators::instance;
void Operators::add(const Chain & str, const Character & one) {
	auto it = options.find(str);
	if(it == options.end()) options.insert(std::pair(str, Continues(one)));
	else {
		auto cont = it->second;
		cont.addChar(one);
		options.at(str) = cont;
	}
}	

bool Operators::i_joinable(const Chain & str, const Character & i) {
	if(str.size() == 1) {
		/* jeśli jest jedno elementowy
		/* to może siedzieć na liście preceders
		 * i tam go poszukamy najpierw */
		Character one = str.at(0);
		/* konwersja jednoznakowego stringa na znak
		 * i niejawny konstr Charactera */
		auto it = preceders.find(i);
		//zwraca się iterator na tuplę
		if(it->second == one) return true;
		/* preceders jest puste, ale się nie
		 * wywala :0 ;
		 * ta mapa jest "w tył"
		 * następnikowi przypisuje poprzednika */
	}
	auto it = options.find(str);
	/* tu zwraca iterator podobnie jak wyżej */
	if(it == options.end()) return false;
	/* nie ma takiego klucza, on będzie w scanie najpierw
	 * chciał pushować a potem zobaczy przy i=='\0', że dalej
	 * jest false, i wtedy zrozumie, że jest błędny operator */
	if(i == '\0' && it->second.isSolitude()) return true;
	/* jest klucz, Continue jest solitude, to znaczy że 
	 * nie wymaga kontynuacji */
	if(it->second.continuee(i)) return true;
	/* najpostszy przypadek, po prosty dołożony znak,
	 * tworzy nowy operator z dotychczasowego */
	return false;
}

#ifdef WIDE
void Operators::hardcode() {
	Chain defaults(L"=+-←→↓↑*/\\;:·.!¡?#^@¬'«»|");
	//wszystkie jednoznakie tworzące stringi klucze
	//w Operators::instance.options

	addDefaults(defaults);
	Continues modulo;
	//modulo.setNotSolitude();
	//bo jednak sam % jest ok
	modulo.addChain(L"↓↑|");
	//każdy z powyższych znaków może być
	//kontynuacją %
	
	add(L"%", modulo);
	Continues modulo_with;
	modulo_with.setNotSolitude();
	modulo_with.addChain(L"^.");
	add(L"%|", modulo_with);
	
	add(L"-", '>');
	//> może być kontynuacją -
	
	Continues left_arrow;
	left_arrow.setNotSolitude();
	left_arrow.addChain(L"<-");
	//dwa różne znaki
	add(L"<", left_arrow);
	Continues power;
	power.setNotSolitude();
	power.addChar('>');
	add(L">", power);
	
	/* Na końcu dodajemy
	 * możliwe końcówki
	 * sprawnych operatorów
	 * bo jak joinable nie znajdzie ich
	 * w Operators::instance.options
	 * to zwróci false
	 * i potem scan będzie myśleć
	 * że są błędne */
	add(L"->", Continues());
	add(L"<-", Continues());
	add(L"<<", Continues());
	add(L">>", Continues());
	add(L"%|^", Continues());
	add(L"%↑", Continues());
	add(L"%↓", Continues());

	add(L"%|.", Continues());
}
#else
void Operators::hardcode() {

	Chain defaults("=+-*/\\;:.!?#^@'|");
	addDefaults(defaults);
	Continues modulo;
	//modulo.setNotSolitude();
	
	modulo.addChar('|');

	add("%", modulo);
	Continues modulo_with;
	modulo_with.setNotSolitude();
	modulo_with.addChain("^.");
	add("%|", modulo_with);
	
	add("-", '>');
	

		
	Continues left_arrow;
	left_arrow.setNotSolitude();
	left_arrow.addChain("<-");
	//dwa różne znaki
	add("<", left_arrow);
	Continues power;
	power.setNotSolitude();
	power.addChar('>');
	add(">", power);
	add(Character('u'), Character('j'));	
	
	add("->", Continues());
	add("<-", Continues());
	add("<<", Continues());
	add(">>", Continues());
	add("%|^", Continues());
	add("%|.", Continues());
}
#endif

void Continues::pour() {
	printf("%d\n", solitude);
	#ifdef WIDE
	freopen(nullptr, "w", stdout);
	#endif
	for(auto & i : options) {
		#ifdef WIDE
		printf("%c\n", i.getChar());
		#else
		wprintf(L"%lc\n", i.getChar());
		#endif
	}
}

void Operators::pour(const Chain & str) {
	#ifdef WIDE
	wprintf(L"For %ls:\n\n", str.c_str());
	#else
	printf("For %s:\n\n", str.c_str());
	#endif
	Continues a = instance.options.at(str);
	//on tu wyjątek rzuci jeśli nie ma
	a.pour();
}

void Operators::pour() {
	printf("Oto wszystkie:\n");
	#ifdef WIDE
	/* podobno między użyciem strumienia
	 * metodami "w..." a zwykłymi
	 * trzeba zrobić reotwarcie strumienia */
	freopen(nullptr, "w", stdout);
	#endif
	for(auto i : instance.options) {
		#ifdef WIDE
		wprintf(L"%ls\n", i.first.c_str());
		#else
		printf("%s\n", i.first.c_str());
		#endif
	}
	#ifdef WIDE
	freopen(nullptr, "w", stdout);
	#endif
	printf("Oto pary znak - znak:\n");
	for(auto i : instance.preceders) {
		#ifdef WIDE
		printf("%c%c\n", i.first.getChar(), i.second.getChar());
		#else
		wprintf(L"%lc%lc\n", i.first.getChar(), i.second.getChar());
		#endif
	}
}

OperatorType operator_filtr (const Chain & str) {
	#ifdef WIDE
	if(str == L"+") return OperatorType::op_plus;
	if(str == L"-") return OperatorType::op_minus;
	if(str == L"=") return OperatorType::op_equal;
	if(str == L"*") return OperatorType::op_multiply;
	if(str == L"/") return OperatorType::op_divide;
	if(str == L">>" || str == L"»") return OperatorType::op_power;
	if(str == L"'") return OperatorType::op_sqrt;
	if(str == L"%" || str == L"%|." || str == L"%↓") return OperatorType::op_modulo_down;
	if(str == L"%|^" || str == L"%↑") return OperatorType::op_modulo_up;
	if(str == L"%↑" || str == L"%|.") return OperatorType::op_modulo_down;
	if(str == L"|^" || str == L"↑") return OperatorType::op_higher;
	if(str == L"|." || str == L"↓") return OperatorType::op_lower;
	if(str == L"|") return OperatorType::op_abs;
	if(str == L"?") return OperatorType::op_bool;
	if(str == L"!") return OperatorType::op_neg_bool;
	if(str == L"->" || str == L"→" ) return OperatorType::op_right;
	if(str == L"<-" || str == L"←" ) return OperatorType::op_left;
	if(str == L".") return OperatorType::op_dot;
	if(str == L"#") return OperatorType::op_signum;
	if(str == L"<<" || str == L"«") return OperatorType::op_shift;
	if(str == L",") return OperatorType::op_comma;
	if(str == L";") return OperatorType::op_ins;
	if(str == L"@") return OperatorType::op_decl;
	if(str == L"$") return OperatorType::op_default;
	if(str == L"_") return OperatorType::op_concrete;
	if(str == L"{") return OperatorType::op_brace_open;
	if(str == L"}") return OperatorType::op_brace_close;
	if(str == L"(") return OperatorType::op_parenth_open;
	if(str == L")") return OperatorType::op_parenth_close;
	
	#else
	if(str == "+") return OperatorType::op_plus;
	if(str == "-") return OperatorType::op_minus;
	if(str == "=") return OperatorType::op_equal;
	if(str == "*") return OperatorType::op_multiply;
	if(str == "/") return OperatorType::op_divide;
	if(str == ">>") return OperatorType::op_power;
	if(str == "'") return OperatorType::op_sqrt;
	if(str == "%"||str == "%|.") return OperatorType::op_modulo_down;
	if(str == "%|^") return OperatorType::op_modulo_up;
	if(str == "%"||str == "%|.") return OperatorType::op_modulo_down;
	if(str == "|^"||str == "%|.") return OperatorType::op_higher;
	if(str == "|.") return OperatorType::op_lower;
	if(str == "|") return OperatorType::op_abs;
	if(str == "?") return OperatorType::op_bool;
	if(str == "!") return OperatorType::op_neg_bool;
	if(str == "->") return OperatorType::op_right;
	if(str == "<-") return OperatorType::op_left;
	if(str == ".") return OperatorType::op_dot;
	if(str == "#") return OperatorType::op_signum;
	if(str == ",") return OperatorType::op_comma;
	if(str == ";") return OperatorType::op_ins;
	if(str == "@") return OperatorType::op_decl;
	if(str == "$") return OperatorType::op_default;
	if(str == "_") return OperatorType::op_concrete;
	if(str == "{") return OperatorType::op_brace_open;
	if(str == "}") return OperatorType::op_brace_close;
	if(str == "(") return OperatorType::op_parenth_open;
	if(str == ")") return OperatorType::op_parenth_close;
	
	#endif
	
	return OperatorType::op_unspec;

}
