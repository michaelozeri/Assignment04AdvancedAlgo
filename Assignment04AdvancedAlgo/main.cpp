#include "Matrix.h"

int main()
{
	Matrix2d<int> m = { {1,2,6}, {3,4,6}, {3,4,6} };
	auto groups = m.groupValues([](int i) {return i == 1 ? 1 : 0; });
	print(groups);


	Matrix2d<char> m1 = { { 'a', 'A','a' },{ 'B', 'a', 'B' },{ 'B', 'a', 'B' } };
	auto all_groups = m1.groupValues([](auto i) {return islower(i) ? 'L' :'U'; });
	print(all_groups);

	//Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
	//auto groupss = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
	//print(groupss);


}