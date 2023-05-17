/*Сортировка слиянием

Первая строка содержит число 1≤n≤10^5, вторая — массив A[1…n], содержащий натуральные числа.
Необходимо посчитать число пар индексов 1≤i<j≤n, для которых A[i]>A[j]. 
(Такая пара элементов называется инверсией массива. 
Количество инверсий в массиве является в некотором смысле его мерой неупорядоченности: 
например, в упорядоченном по неубыванию массиве инверсий нет вообще, а в массиве, упорядоченном по убыванию, инверсию образуют каждые два элемента.)
*/
#include <iostream>
#include <vector>

using std::cin; using std::cout;
using std::vector;

long count = 0; // счётчик инверсий

// слияние двух отсортированных массивово
vector<int> Merge(vector<int> vec_1, vector<int> vec_2)
{
	auto it_1 = vec_1.begin(), it_1_end = vec_1.end();
	auto it_2 = vec_2.begin(), it_2_end = vec_2.end();
	auto size = vec_1.size() + vec_2.size();
	vector<int> result(size);
	
	decltype(size) i = 0;
	while (i < size)
	{
		if (it_1 != it_1_end && it_2 != it_2_end)
		{
			if (*it_1 <= *it_2)
			{
				result[i] = *it_1;
				++it_1;
			}
			else
			{
				result[i] = *it_2;
				count += (it_1_end - it_1);
				++it_2;
			}
		}
		else if (it_1 != it_1_end)
		{
			result[i] = *it_1;
			++it_1;
		}
		else if (it_2 != it_2_end)
		{
			result[i] = *it_2;
			++it_2;
		}
		
		++i;
	}
	
	return result;
}
	
	

vector<int> MergeSort(vector<int> & vec)
{	
	if (vec.size() <= 1)
		return vec;
	
	auto start  = vec.begin();
	auto finish = vec.end();
	auto medium = start + (finish - start) / 2;
	
	vector<int> v1(start, medium);
	vector<int> v2(medium, finish);
	
	return Merge(MergeSort(v1), MergeSort(v2));
}

int main()
{
	int n = 0;
	cin >> n;
	vector<int> arr(n);
	for (auto & x : arr)
		cin >> x;
	
	// сортировка массива
	vector<int> sort = MergeSort(arr); 
	
	// вывод количества инверсий
	cout << count;
	
	return 0;
}