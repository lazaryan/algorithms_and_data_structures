#ifndef __RANDOM_RANDOM__
#define __RANDOM_RANDOM__

#include <iostream>
#include <vector>
#include <random>

namespace Random {
	/*
	 * Класс для получения случайного элемента исходя из его вероятности выподания
	 * Если вероятность всех событий != 1, то она будет приведена к данному значению автоматически
	 */
	template <typename T>
	class IRandom {
	public:
		/*
		 * Метод для загрузки данных в класс и дальнейшая их обработка
		 * Число элементов и их верятностей должны совпадать
		 * 
		 * @params
		 * - data - массив данных, которые будут возвращаться случайным образом
		 * - statements - массив вероятностей выпадания каждого элемента
		 * @return bool - успешность занесения данных
		 */
		virtual bool set_data(std::vector<T> data, std::vector<double> statements) = 0;

		// получить, сколько элементов в выборке
		virtual size_t get_size_database() = 0;

		/*
		 * Метод для получения случайного элемента
		 * Данный метод можно вызывть только после загрузки данных, иначе будет возвращен nullptr
		 */
		virtual T* random() = 0;
	private:
		/*
		 * Функция для приведения массива вероятностей к 1
		 * Если все вероятности в сумме дают 1, то с ними ничего не происходит
		 *
		 * Иначе вычисляется общее отклонение = (persentage^-1) * 0.1
		 * И дальше все вероятности умножаются на это отклонение
		 * Если сумма < 1, то это отклонение > 1 и наоборот
		 * В итоге так мы получаем 1 в сумме всех вероятностей
		 */
		virtual std::vector<double> prepare_statements(std::vector<double> statements) = 0;
	};

	template <typename T>
	class Random: IRandom<T> {
	public:
		Random()
		{
			std::random_device rd;

			this->mersen_random_generator = std::mt19937(rd());
		}

		Random(std::vector<T> data, std::vector<double> statements)
		{
			std::random_device rd;

			this->mersen_random_generator = std::mt19937(rd());

			this->set_data(data, statements);
		}

		bool set_data(std::vector<T> data, std::vector<double> statements)
		{
			if (data.size() != statements.size())
			{
				std::cerr << "ERROR::Random => size data != statements" << std::endl;

				return false;
			}

			this->database = data;
			this->statements = this->prepare_statements(statements);
			
			this->is_load_data = true;

			return true;
		}

		T* random()
		{
			if (!this->is_load_data)
			{
				std::cerr << "ERROR::Random => not get random item after load dataset" << std::endl;

				return nullptr;
			}

			const double random_value = double(this->mersen_random_generator()) / this->mersen_random_generator.max();

			double statement = 0;

			for (int i = 0; i < this->statements.size(); i++)
			{
				statement += this->statements[i];

				if (random_value < statement)
				{
					T* item = &this->database[i];

					return item;
				}
			}

			T* item = &this->database[database.size() - 1];

			return item;
		}

		size_t get_size_database() { return this->statements.size(); }

	private:
		bool is_load_data = false;

		std::vector<T> database;
		std::vector<double> statements;
		std::mt19937 mersen_random_generator;

		std::vector<double> prepare_statements(std::vector<double> statements)
		{
			double persentage = 0;

			for (std::vector<double>::iterator it = statements.begin(); it != statements.end(); ++it)
			{
				persentage += *it;
			}

			if (persentage == 1.0)
			{
				return statements;
			}

			const double offset = std::pow(persentage, -1);

			for (size_t i = 0; i < statements.size(); i++)
			{
				statements[i] *= offset;
			}

			return statements;
		}
	};
}

#endif // !__RANDOM_RANDOM__
