#include <clocale>
inline void setLocale() {
	setlocale(LC_ALL, "");
	setlocale(LC_CTYPE, "");
}
