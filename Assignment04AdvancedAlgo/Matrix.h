#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <list>

using namespace std;

using coord = list<size_t>;
using groupOfType = vector<coord>;
using groupType = vector<groupOfType>;

template<class T>
using allGroups = map<T, groupType>;

/*
temporary print function with additional data for debug
*/
template<typename Groups>
void printRetVal(const Groups& retval,int i) {
	cout << "****************" << endl;
	cout << "finished " << i << "'st iteration, printing ret val" << endl;
	for each (auto var in retval)
	{
		cout << "groupType: " << var.first << endl;
		int checksize = 0;
		cout << "coordinates: ";
		for each (auto varin in var.second)
		{
			for each (auto varinin in varin)
			{
				cout << "{ ";
				for (int i : varinin) {
					cout << i << ' ';
				}
				cout << "}, ";
			}
			checksize++;
		}
		cout << "groupType size is : " << checksize << endl;
	}
}

/*
template recursive class
*/
template<class T, size_t DIMENSIONS>
class Matrix
{
public:
	vector<Matrix<T, DIMENSIONS - 1>> m_mat;
	int my_max_dim;
	int lower_max_dim;
	Matrix(initializer_list<Matrix<T, DIMENSIONS-1>> vm)
	{
		my_max_dim = 0;
		//construct matrix and find my max dim
		for (auto m : vm)
		{
			m_mat.push_back(m);
			my_max_dim++;
		}
		lower_max_dim = 0;

		//find the max_dim of lower matrixes
		for (auto m : m_mat)
		{
			if (lower_max_dim < m.my_max_dim) {
				lower_max_dim = m.my_max_dim;
			}
		}
		//update each lower matrixes dim to be the max_dim
		for (auto& tempMat : m_mat)
		{
			if (lower_max_dim > tempMat.my_max_dim) {
				cout << "modifiying dimension: " << DIMENSIONS - 1 << endl;
				tempMat.my_max_dim = lower_max_dim;
			}
		}
		cout << endl;
		
	}

	template<class FilterType, typename R = std::result_of<FilterType&(T)>::type>
	allGroups<R> groupValues(FilterType& f)
	{
		

		allGroups<R> retVal;
		for (size_t i = 0; i < m_mat.size(); i++)
		{
			allGroups<R> tempAllGroups = m_mat[i].groupValues(f);
			for (auto& tempMapValue : tempAllGroups)
			{
				//for each map.second = value = groupType (map.first = key)
				for (auto& tempGroupofType : tempMapValue.second)
				{
					for (auto& tempCoord : tempGroupofType)
					{
						tempCoord.push_front(i); //checked - inserted all coordinates
					}
				}
			}

			//printRetVal(tempAllGroups, i);

			//inserting values of tempAllGroups into ret val
			for (auto tempGrouptype : tempAllGroups)
			{
				//if temp group type isnt inside the map
				if (retVal.find(tempGrouptype.first) == retVal.end())
				{
					retVal[tempGrouptype.first] = tempGrouptype.second;
				}
				else {
					auto temp = retVal[tempGrouptype.first];
					for (auto a : tempGrouptype.second)
					{
						temp.push_back(a);
					}

					retVal[tempGrouptype.first] = temp;
				}
			}
			//printRetVal(tempAllGroups,i);
		}

		return retVal;
	}
};

/*
recursion base
*/
template<class T>
class Matrix<T, 1>
{
public:
	vector<T> m_mat;
	int my_max_dim;
	Matrix(initializer_list<T> vm)
	{
		my_max_dim = vm.size();
		for (auto m : vm)
		{
			m_mat.push_back(m);
		}
	}

	template<class FilterType,typename R = std::result_of<FilterType&(T)>::type>
	allGroups<R> groupValues(FilterType & f)
	{
		allGroups<R> retVal;
		for (size_t i = 0; i < m_mat.size(); i++)
		{
			auto type = f(m_mat[i]);
			//if key not found insert into map
			if (retVal.find(type) == retVal.end())
			{
				groupType gt;
				groupOfType got;
				coord c;

				c.push_front(i);
				got.push_back(c);
				gt.push_back(got);
				retVal[type] = gt;
			}
			else //insert into exsiting grouptype
			{
				groupType gst = retVal[type];
				//create a new groupOfType and insert into it a new coordinate and a new index
				groupOfType gt;
				coord c;
				c.push_front(i);
				gt.push_back(c);
				gst.push_back(gt);
	
				retVal[type] = gst;
			}
		}
	
		return retVal;
	}
};

template<class T>
using Matrix2d = Matrix<T, 2>;

template<class T>
using Matrix3d = Matrix<T, 3>;

template<typename Groups>
void print(const Groups& all_groups) {
	for (const auto& groupType : all_groups) {
		cout << groupType.first << ":" << endl;
		for (const auto& groupOfType : groupType.second) {
			//int j = 0;
			for (const auto& coord : groupOfType) {
				cout << "{ ";
				for (int i : coord) {
					cout << i << ' ';
					//j++;
				}
				cout << "} ";
			}
			//cout << "coord size is: " << j;
			cout << endl;
		}
	}
}

template<class T, size_t DIMENSIONS>
void printDimensions(Matrix<T, DIMENSIONS> mat) {
	cout << "dimension: " << DIMENSIONS << " max_dim: " << mat.my_max_dim << endl;
	for (auto m : mat.m_mat)
	{
		printDimensions(m);
	}
	
}

template<class T>
void printDimensions(Matrix<T, 1> mat) {
	cout << "dimension: " << 1 << " max_dim: " << mat.my_max_dim << endl;
}




