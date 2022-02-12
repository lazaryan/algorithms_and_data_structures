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

		/*
		 * ������� ��������� ������ ��������� ������ �� csv �����
		 * ����� ��� ����, ���� ������ ������ ����� ������������� � ������ ��� ������
		 */
		virtual const void line_reader() = 0;

		/*
		 * ������� ��� ���������� ��������� ������ �� CSV �����
		 * ��� ������� ��� ������ ����� �������� ����� line_reader ��� �������������� � ������ ���������
		 */
		virtual T next() = 0;

		// ������� ��� ��������� ���� ����� �����
		virtual std::vector<T> read_all() = 0;
	private:
		std::vector<T> db;
		std::ifstream file_stream;
	};
}


#endif // !__CSV_INTERFACES__
