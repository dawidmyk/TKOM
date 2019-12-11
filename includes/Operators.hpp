#pragma once
#include <set>
#include <map>
#ifdef WIDE
#include "WideCharacter.hpp"
#else
#include "Character.hpp"
#endif

enum class OperatorType {
	op_plus, //+
	op_minus, //-
	op_equal,//=
	op_multiply, //* ew. ·
	op_divide, // /
	op_power, // >> »
	op_sqrt, // '
	op_log, // ¡
	op_modulo_down, // % %↓ %|. ew. %.
	op_modulo_up, // %↑ %|^ ew. %^
	op_lower, // ↓ |.
	op_higher, // ↑ |^ ew. ^
	op_abs, // | chodzi o to że: |expression|
	op_neg, // ¬
	op_bool, // ?
	op_neg_bool, // !
	op_right, // → ->
	op_left, // ← <-
	op_dot, // .
	op_signum, // #
	op_shift, // << « zdejmowanie argumentów
	//ze "stosu"
	op_decl, // @ deklaracja zmiennych
	//@ zmienna1, zmienna2;
	op_default, // $ domyślny argument wywołania
	op_concrete, // _ nieokreślony argument
	/* wywołania, przy przerabianiu obiektu-funkcji na bardziej
	 * wyspecyfikowaną */
	op_comma, // , dzieli argumenty wywołania
	op_ins, // ; dzieli instrukcje
	op_brace_open, // '{' do grupowania instrukcji
	//i tworzenia funkcji-obiektów
	op_brace_close, // '}' jak wyżej
	op_parenth_open, // '(' do grupowania wyrażeń
	//zmienianie kolejności działań
	op_parenth_close, // ')' jak wyżej
	op_unspec,
	op_none
	//nie wiem czy wszystkie będą użyte
};
class Continues {
	/* obudowuje zbiór możliwych kontynuacji
	 * budowanego operatora */
	bool solitude;
	/* czy sam jest ok, czy musi być jakoś
	 * skontynuowany */
	std::set<Character> options; //obudowany zbiór
	//kontynuacje tylko o jeden znak wprzód
	public:
	Continues(): solitude(true) {}
	Continues(const Character & one): solitude(true) {
		options.insert(one);
	}
	bool continuee(const Character & i) {
		return (options.find(i) != options.end());
	}
	/* Następujące metody
	 * służą do budowania "drzewa" czy "grafu"
	 * rozpoznawania operatorów
	 * co musi nastąpić na początku aplikacji 
	 * jak widać drzewo to może by budowane
	 * na różne sposoby */
	void addChar(const Character & i) {
		options.insert(i);
	}
	void addChain(const Chain & str) {
		for(auto i : str) {
			options.insert(Character(i));
		}
	}
	void setNotSolitude() {
		solitude = false;
	}
	/* skoro w konstruktorze
	 * jest true, to my potrzebujemy tylko 
	 * setter na false */
	bool isSolitude() {
		return solitude;
	}
	void pour(); //informacja "debugująca"
	//o tym obiekcie
	
};
class Operators {
	static Operators instance;
	std::map<Chain, Continues> options;
	std::map<Character, Character> preceders;
	//tego preceders nie użyto w obecnej wersji
	public:
	Operators() {
	}
	/* metody add tak jak w Continues */
	void add(const Chain & str, const Continues & c) {
		auto i = options.insert(std::pair(str, c));
		if(!i.second) options.at(str) = c;
	}
	void add(const Chain & str, const Character & one);
	void add(const Character & former, const Character & later) {
		preceders.insert(std::pair(later, former));
	}
	void addDefaults(const Chain & str) {
		for(auto i : str) {

			options.insert(std::pair(Chain(i), Continues()));
		}
	}
	
	//trzeba było zmienić nazwę bo nie można było
	//przeciążyć statycznego joinable
	bool i_joinable(const Chain & str, const Character & i);
	
	static bool joinable(const Chain & str, const Character & i) {
		return instance.i_joinable(str, i);
	}
	
	static void start() {
		instance.hardcode();
	} //to jest właśnie to czego nie można było zrobić w konstruktorze
	
	void hardcode();
	static void pour(const Chain & str);
	static void pour(); //także ma metody debugujące
};
	
OperatorType operator_filtr(const Chain & str);
//zwraca symbol na podstawie napisu




