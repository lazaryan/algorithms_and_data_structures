#ifndef __DATABASES_STATEMENTS__
#define __DATABASES_STATEMENTS__

#include <string>

#include "../CSV/CSVReader.h"

namespace Databases {
	struct Statement {
		int id;
		std::string name;
		double probability;
	};

	class Statements : public CSV::CSVReader<Statement>
	{
	public:
		Statements(std::string path) : CSV::CSVReader<Statement>(path) {};
		Statements(std::string path, char c) : CSV::CSVReader<Statement>(path, c) {};

		Statement* find_by_id(int id)
		{
			if (this->db.empty())
			{
				return nullptr;
			}

			for (size_t i = 0; i < this->db.size(); i++)
			{
				if (this->db[i]->id == id)
				{
					return this->db[i];
				}
			}

			return nullptr;
		}

	private:
		Statement* line_reader(std::vector<std::string> item)
		{
			if (item.size() != 3) {
				return nullptr;
			}

			Statement* new_item = new Statement {
				std::stoi(item[0]),
				item[1],
				std::stod(item[2].c_str()),
			};

			return new_item;
		}
	};
}

#endif // !__DATABASES_STATEMENTS__
