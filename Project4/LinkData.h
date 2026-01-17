#include <iostream>
// dont modify
using namespace std;

class LinkData{
	public:
		static const int SIZE = 4;

		void setDigits(int, int, int, int);
		int getDigit(int);

	private:
		int digits[4];
};
