#include <iostream>

#include "LogCommandWithObserver.hpp"


int main() {
#if WIN32
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
	std::cout << "\tПаттерн \"Наблюдатель\"\n\n" << std::endl;

	std::string filename = "out.txt";

	LogCommandWithObserver logCommand;
	Warning warning(std::addressof(logCommand));
	Error error(std::addressof(logCommand), filename);
	FatalError fatalError(std::addressof(logCommand), filename);

	std::cout << "Вывод предупреждения:" << std::endl;
	logCommand.warning("Warning!");
	std::cout << std::endl;

	std::cout << "Вывод ошибки:" << std::endl;
	logCommand.error("Error!");
	std::cout << std::endl;

	std::cout << "Вывод фатальной ошибки:" << std::endl;
	logCommand.fatalError("Fatal Error!");

	std::cin.get();
	return 0;
}
