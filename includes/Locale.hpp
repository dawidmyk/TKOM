#include <clocale>
inline void setLocale() {
	setlocale(LC_ALL, "");
	setlocale(LC_CTYPE, "");
}
/* to musi być wywołane gdy
 * chcemy korzystać z WIDEów
 * przed wywołaniem jakiejkolwiek
 * funkcji "w..." albo użyciem
 * wstringa
 * dlatego nie można było
 * inicjalizować operatorów
 * w konstruktorze obiektu
 * statycznego 
 * Operators::instance */
