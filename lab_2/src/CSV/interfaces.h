#ifndef __CSV_INTERFACES__
#define __CSV_INTERFACES__

#include <vector>
#include <string>
#include <fstream>
#include <map>

/*
 * Файл для описания интрфейсов классов для namespace CSV
 * 
 * Реализуются следующие классы:
 * - CSVReader
 */

namespace CSV {
	typedef int item_id_t;

	template <typename T>
	using db_map_t = std::map<item_id_t, T>;

	/*
	 * Класс для работы с CSV файлом
	 * Используется для считывания данных с файла
	 *
	 * @Template T - структура, в которую будут занесены данные из строки файла
	 */
	template <typename T>
	class ICSVReader {
	public:
		// проверка, что удалось открыть файл
		virtual bool is_open() const = 0;

		// проверка, что прочитан весь файл
		virtual bool is_reading_all() const = 0;

		// метод для принудительного закрытия файла
		virtual void close_file() = 0;

		/*
		 * Функция для считывания очередной строки из CSV файла
		 * под капотом для каждой стоки вызывает метод line_reader для преобразования в нужную структуру
		 */
		virtual T* next() = 0;

		// функция для считвания всех строк сразу
		virtual db_map_t<T*> read_all() = 0;
	private:
		/*
		 * функция обработки каждом считанной строки из csv файла
		 * нужно для того, чтоб каждую строку сразу преобразовать в нужный тип данных
		 */
		virtual T* line_reader(std::vector<std::string>) = 0;

		/*
		 * Функция фильтрации, если это требуется
		 * Если для элемента функция вернет false - элемент не будет сохранен в хранилище
		 */
		virtual bool filter_saving(T item) = 0;

		/*
		 * Функция для получения id элемента. Дальше по этому id можно будет вытащить элемент из хранилища
		 */
		virtual item_id_t get_item_id(T item) = 0;
	};

	class ICSVWriter {
		// проверка, что удалось открыть файл
		virtual bool is_open() const = 0;

		// метод для принудительного закрытия файла
		virtual void close_file() = 0;

		virtual void write_line(std::vector<std::string> line) = 0;
	};
}


#endif // !__CSV_INTERFACES__
