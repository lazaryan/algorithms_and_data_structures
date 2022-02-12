#ifndef __CSV_INTERFACES__
#define __CSV_INTERFACES__

#include <vector>
#include <string>
#include <fstream>

/*
 * Файл для описания интрфейсов классов для namespace CSV
 * 
 * Реализуются следующие классы:
 * - CSVReader
 */

namespace CSV {
	/*
	 * Класс для работы с CSV файлом
	 * Используется для считывания данных с файла
	 *
	 * @Template T - структура, в которую будут занесены данные из строки файла
	 */
	template <typename T>
	class ICSVReader {
	public:
		// получить колличество строк
		virtual size_t size() const = 0;

		// проверка, что удалось открыть файл
		virtual bool is_open() const = 0;

		/*
		 * Функция для считывания очередной строки из CSV файла
		 * под капотом для каждой стоки вызывает метод line_reader для преобразования в нужную структуру
		 */
		virtual T* next() = 0;

		// функция для считвания всех строк сразу
		virtual std::vector<T*> read_all() = 0;
	private:
		/*
		 * функция обработки каждом считанной строки из csv файла
		 * нужно для того, чтоб каждую строку сразу преобразовать в нужный тип данных
		 */
		virtual T* line_reader(std::vector<std::string>) = 0;
	};
}


#endif // !__CSV_INTERFACES__
