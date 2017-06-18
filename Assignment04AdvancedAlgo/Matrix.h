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

template<class T, size_t DIMENSIONS>
class Matrix
{
private:
	vector<Matrix<T, DIMENSIONS - 1>> m_mat;

public:
	Matrix(initializer_list<Matrix<T, DIMENSIONS-1>> vm)
	{
		for (auto m : vm)
		{
			m_mat.push_back(m);
		}
	}

	template<class FilterType>
	allGroups<T> groupValues(FilterType & f)
	{
		allGroups<T> retVal;
		for (size_t i = 0; i < m_mat.size(); i++)
		{
			allGroups<T> tempAllGroups = m_mat[i].groupValues(f);
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

template<class T>
class Matrix<T, 1>
{
private:
	vector<T> m_mat;
public:
	Matrix(initializer_list<T> vm)
	{
		for (auto m : vm)
		{
			m_mat.push_back(m);
		}
	}

	template<class FilterType>
	allGroups<T> groupValues(FilterType & f)
	{
		allGroups<T> retVal;
		for (size_t i = 0; i < m_mat.size(); i++)
		{
			auto type = f(m_mat[i]);
			//if key not found insert into map
			if (retVal.find(type) == retVal.end())
			{
				groupType gst;
				groupOfType gt;
				coord c;

				c.push_front(i);
				gt.push_back(c);
				gst.push_back(gt);
				retVal[type] = gst;
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



