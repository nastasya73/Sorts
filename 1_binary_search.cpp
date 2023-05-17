/* Бинарный поиск
* 
В первой строке даны целое число 1≤n≤10^5 и массив A[1…n] из n различных натуральных чисел, в порядке возрастания, 
во второй — целое число 1≤k≤10^5 и k натуральных чисел/.
Для каждого необходимо вывести индекс 1≤j≤n, для которого A[j]=bi, или −1, если такого j нет.
*/

#include <iostream>
#include <vector>

using std::cin; using std::cout;
using std::vector;

int get_pos(const vector<int> & vec, int key)
{
	int left = 0;
	int right = vec.size() - 1;
	
	while (right - left > 1)
	{
		int mem = left + (right - left) / 2;
		if (vec[mem] == key)
			return mem;
		else if (vec[mem] > key)
			right = mem - 1;
		else 
			left = mem + 1;
	}
	
	return -1;
}
		

int main()
{
	int n = 0;
	cin >> n;
	vector<int> arr(n);
	for (auto &x : arr)
		cin >> x;
	
	int k = 0;
	cin >> k;
	vector<int> keys(k);
	for (auto &x : keys)
		cin >> x;
	
	for (auto x : keys)
		cout << get_pos(arr, x) << " ";
	
	return 0;
}