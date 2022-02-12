#ifndef __CSV_READER__
#define __CSV_READER__

#include <string>
#include <vector>
#include <istream>
#include <fstream>
#include <iostream>

#include "interfaces.h"

namespace CSV {
	template <typename T>
	class CSVReader : ICSVReader<T> {
	public:
		CSVReader(std::string path_to_file)
		{
			this->file_stream = std::ifstream(path_to_file);

			if (!this->file_stream.is_open())
			{
				std::cerr << "ERROR::CSVReader => open " << path_to_file << " for reading" << std::endl;
			}
		}
		~CSVReader()
		{
			if (this->file_stream.is_open())
			{
				this->file_stream.close();
			}
		}

		size_t size() const { return this->db.size(); };

		T next() { return T{}; };

		std::vector<T> read_all() { return std::vector<T>(); };
		virtual const void line_reader() {};
	private:

		std::vector<T> db;
		std::ifstream file_stream;
	};
}

#endif // !__CSV_READER__
