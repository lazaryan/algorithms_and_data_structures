#include <iostream>
#include <string>

#include "./Databases/Graph.h"

std::string read_line() {
	std::string read_line = "";
	bool is_error = true;

	while (is_error) {
		std::cout << "Введите последовательность нулей и единиц:" << std::endl;

		std::cin >> read_line;

		is_error = false;

		for (int i = 0; i < read_line.length(); i++) {
			int c = read_line[i] - '0';

			if (!(c == 0 || c == 1)) {
				std::cerr << "Error: Строка содержит некорректные данные. Введите строку, содержащую только 0 и 1!" << std::endl;
				is_error = true;
				break;
			}
		}
	}

	return read_line;
}

bool read_result(std::string line, Databases::Graph* graph, CSV::item_id_t root_id, int* result) {
	Databases::GraphNode* active_node = (*graph)[root_id];

	for (int i = 0; i < line.length(); i++)
	{
		int c = line[i] - '0';

		std::string type = c == 0 ? active_node->left_type : active_node->right_type;
		int value = c == 0 ? active_node->left_value : active_node->right_value;

		if (type == "v")
		{
			*result = value;
			return true;
		}
		else
		{
			active_node = (*graph)[value];
		}
	}

	std::cerr << "Error: Введено недостаточно значений для считывания результата! Повторите попытку:" << std::endl;

	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	const CSV::item_id_t root_id = 0;

	Databases::Graph graph("./database/graph.csv");
	graph.read_all();

	int result = 0;

	while (true)
	{
		std::string line = read_line();
		if (read_result(line, &graph, root_id, &result)) break;
	}

	std::cout << "Результат: " << result << std::endl;
	
	return 0;
}
