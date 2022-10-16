#ifndef __DATABASES_GRAPH__
#define __DATABASES_GRAPH__

#include <string>
#include <vector>

#include "../CSV/CSVReader.h"

namespace Databases
{
	struct GraphNode
	{
		CSV::item_id_t id;
		CSV::item_id_t real_id;
		std::string left_type;
		int left_value;
		std::string right_type;
		int right_value;
	};

	class Graph : public CSV::CSVReader<GraphNode>
	{
	public:
		Graph(std::string path) : CSV::CSVReader<GraphNode>(path) {};
		Graph(std::string path, char separator) : CSV::CSVReader<GraphNode>(path, separator) {};
	private:
		GraphNode* line_reader(std::vector<std::string> item)
		{
			if (item.size() != 6)
			{
				return nullptr;
			}

			GraphNode* new_item = new GraphNode
			{
				std::stoi(item[0]),
				std::stoi(item[1]),
				item[2],
				std::stoi(item[3]),
				item[4],
				std::stoi(item[5]),

			};

			return new_item;
		}

		CSV::item_id_t get_item_id(GraphNode item) { return item.id; }
	};
}

#endif // !__DATABASES_GRAPH__
