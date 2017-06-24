#include "Matrix.h"

int main()
{
	cout << "***********mat1***********" << endl << endl;
	Matrix2d<int> m = { {1,2,6}, {3,4}, {3,4,6} };
	printDimensions(m);
	auto groups = m.groupValues([](int i) {return i == 1 ? 1 : 0; });
	print(groups);
	cout << endl;
	cout << "***********mat2***********" << endl << endl;
	Matrix2d<char> m1 = { { 'a', 'A','a' },{ 'B','a', 'B' },{ 'B', 'a', 'B' } };
	printDimensions(m1);
	auto all_groups = m1.groupValues([](auto i) {return islower(i) ? "L" : "U"; });
	print(all_groups);
	cout << endl;
	cout << "***********mat3***********" << endl << endl;
	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
	printDimensions(m2);
	auto groupss = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
	print(groupss);
	cout << endl;
}