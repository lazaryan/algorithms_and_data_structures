#ifndef __CSV_INTERFACES__
#define __CSV_INTERFACES__

#include <vector>
#include <string>
#include <fstream>

/*
 * ���� ��� �������� ���������� ������� ��� namespace CSV
 * 
 * ����������� ��������� ������:
 * - CSVReader
 */

namespace CSV {
	/*
	 * ����� ��� ������ � CSV ������
	 * ������������ ��� ���������� ������ � �����
	 *
	 * @Template T - ���������, � ������� ����� �������� ������ �� ������ �����
	 */
	template <typename T>
	class ICSVReader {
	public:
		// �������� ����������� �����
		virtual size_t size() const = 0;

		// ��������, ��� ������� ������� ����
		virtual bool is_open() const = 0;

		/*
		 * ������� ��� ���������� ��������� ������ �� CSV �����
		 * ��� ������� ��� ������ ����� �������� ����� line_reader ��� �������������� � ������ ���������
		 */
		virtual T* next() = 0;

		// ������� ��� ��������� ���� ����� �����
		virtual std::vector<T*> read_all() = 0;
	private:
		/*
		 * ������� ��������� ������ ��������� ������ �� csv �����
		 * ����� ��� ����, ���� ������ ������ ����� ������������� � ������ ��� ������
		 */
		virtual T* line_reader(std::vector<std::string>) = 0;
	};
}


#endif // !__CSV_INTERFACES__
