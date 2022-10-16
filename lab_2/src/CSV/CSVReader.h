#ifndef __CSV_READER__
#define __CSV_READER__

#include <string>
#include <vector>
#include <map>
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
			if (!this->init_file_stream(path_to_file))
			{
				std::cerr << "ERROR::CSVReader => create class" << std::endl;
			}
		}

		CSVReader(std::string path_to_file, char separator)
		{
			if (!this->init_file_stream(path_to_file))
			{
				std::cerr << "ERROR::CSVReader => create class" << std::endl;
			}

			this->separator = separator;
		}

		~CSVReader()
		{
			this->close_file();
			this->db.clear();
		}

		T* operator[](CSV::item_id_t id)
		{
			return this->db.count(id) ? this->db.at(id) : nullptr;
		}

		size_t size() const { return this->db.size(); }

		bool is_open() const { return this->file_stream.is_open(); }

		bool is_reading_all() const { return !this->file_stream.is_open() || this->file_stream.eof(); }

		db_map_t<T*> get_data() { return this->db; }

		void close_file()
		{
			if (this->file_stream.is_open())
			{
				this->file_stream.close();
			}
		}

		T* next()
		{
			if (this->file_stream.eof())
			{
				return nullptr;
			}
			
			std::string line = "";
			std::getline(this->file_stream, line, '\n');

			if (line.length() == 0)
			{
				return nullptr;
			}

			size_t position_separator = 0;
			std::string item;
			std::vector<std::string> list;

			while ((position_separator = line.find(this->separator)) != std::string::npos) {
				item = line.substr(0, position_separator);
				list.push_back(item);
				line.erase(0, position_separator + 1);
			}

			if (line.length() != 0)
			{
				list.push_back(line);
			}

			T* new_item = this->line_reader(list);

			if (new_item == NULL)
			{
				std::cerr << "ERROR::CSVReader => error creating new item" << std::endl;
				return nullptr;
			}

			if (this->filter_saving(*new_item))
			{
				this->db.emplace(this->get_item_id(*new_item), new_item);
				return new_item;
			}

			return nullptr;
		}

		CSV::db_map_t<T*> read_all()
		{
			while (!this->file_stream.eof())
			{
				this->next();
			}

			return this->db;
		};

	protected:
		CSV::db_map_t<T*> db;

	private:
		std::ifstream file_stream;
		char separator = ';';

		virtual T* line_reader(std::vector<std::string> item) { return new T{}; }
		virtual bool filter_saving(T item) { return true; }
		virtual item_id_t get_item_id(T item) { return 0; }

		bool init_file_stream(std::string path_to_file)
		{
			this->file_stream = std::ifstream(path_to_file);

			if (!this->file_stream.is_open())
			{
				std::cerr << "ERROR::CSVReader => init_file_stram " << path_to_file << " for reading" << std::endl;

				return false;
			}

			return true;
		}
	};
}

#endif // !__CSV_READER__
