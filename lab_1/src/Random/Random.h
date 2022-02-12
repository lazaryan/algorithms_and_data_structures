#ifndef __RANDOM_RANDOM__
#define __RANDOM_RANDOM__

#include <iostream>
#include <vector>
#include <random>
#include <math>

namespace Random {
	/*
	 * ����� ��� ��������� ���������� �������� ������ �� ��� ����������� ���������
	 * ���� ����������� ���� ������� != 1, �� ��� ����� ��������� � ������� �������� �������������
	 */
	template <typename T>
	class IRandom {
	public:
		/*
		 * ����� ��� �������� ������ � ����� � ���������� �� ���������
		 * ����� ��������� � �� ����������� ������ ���������
		 * 
		 * @params
		 * - data - ������ ������, ������� ����� ������������ ��������� �������
		 * - statements - ������ ������������ ��������� ������� ��������
		 * @return bool - ���������� ��������� ������
		 */
		virtual bool set_data(std::vector<T> data, std::vector<double> statements) = 0;

		// ��������, ������� ��������� � �������
		virtual size_t get_size_database() = 0;

		/*
		 * ����� ��� ��������� ���������� ��������
		 * ������ ����� ����� ������� ������ ����� �������� ������, ����� ����� ��������� nullptr
		 */
		virtual T* random() = 0;
	private:
		/*
		 * ������� ��� ���������� ������� ������������ � 1
		 * ���� ��� ����������� � ����� ���� 1, �� � ���� ������ �� ����������
		 *
		 * ����� ����������� ����� ���������� = (persentage^-1) * 0.1
		 * � ������ ��� ����������� ���������� �� ��� ����������
		 * ���� ����� < 1, �� ��� ���������� > 1 � ��������
		 * � ����� ��� �� �������� 1 � ����� ���� ������������
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

			const double random_value = double(this->mersen_random_generator()) / RAND_MAX;

			int statement = 0;

			for (int i = 0; i < this->statements.size(); i++)
			{
				statement += this->statements[i];

				if (random_value < statement)
				{
					return &this->statements[i];
				}
			}

			return &this->statements.end();
		}

	private:
		bool is_load_data = false;

		std::vector<T> database;
		std::vector<double> statements;
		std::mt19937 mersen_random_generator;

		std::vector<double> prepare_statements(std::vector<double> statements)
		{
			const double persentage = 0;

			for (std::vector<double>::iterator it = statements.begin(); it != statements.end(); ++it)
			{
				persentage += *it;
			}

			if (persentage == 1.0)
			{
				return statements;
			}

			const double offset = std::pow(persentage, -1) * 0.1;

			for (size_t i = 0; i < statements.size(); i++)
			{
				statements[i] *= offset;
			}

			return statements;
		}
	};
}

#endif // !__RANDOM_RANDOM__
