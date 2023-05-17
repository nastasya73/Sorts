/* Быстрая сорировка

 В первой строке задано два целых числа 1≤n≤50000 и 1≤m≤50000 — количество отрезков и точек на прямой, соответственно. 
 Следующие n строк содержат по два целых числа — координаты концов отрезков. 
 Последняя строка содержит m целых чисел — координаты точек. 
 Точка считается принадлежащей отрезку, если она находится внутри него или на границе. 
 Для каждой точки в порядке появления во вводе выведите, скольким отрезкам она принадлежит.
*/
#include <iostream>
#include <cstdlib>
#include <utility>
#include <ctime>

using std::cin; using std::cout; using std::endl;
using std::pair;

void ChangeMem(long arr[], long n1, long n2);
void Partition(long arr[], long l, long r, long m[2]);
void QuickSort(long arr[], long l, long r);
long BinarSearch(long arr[], long n, long point, bool eql);

int main()
{
	//считывание входных данных
	long n, m;
	cin >> n >> m;
	
	long *seg_begin = new long[n];
	long *seg_end = new long[n];
	long *points = new long[m];
	
	for (long i = 0; i < n; ++i)
		cin >> seg_begin[i] >> seg_end[i];
	for (long i = 0; i < m; ++i)
		cin >> points[i];
	
   
	//сортировка каждого массива
	QuickSort(seg_begin, 0, n);
	QuickSort(seg_end, 0, n);
	
	
	//обработка каждой точки
	for (long i = 0; i < m; ++i)
	{
		long x = BinarSearch(seg_begin, n, points[i], true);
		long y = BinarSearch(seg_end, n, points[i], false);
        long res =  x - y;
		
		cout << res << " ";
	}
	
	return 0;
}

void ChangeMem(long arr[], long n1, long n2)
{
	long temp = arr[n1];
	arr[n1] = arr[n2];
	arr[n2] = temp;
}

pair<int, int> Partition(long arr[], long l, long r)
{
	
	//выбор опорного элемента случайным образом
	// j - последний элемент, меньший опорного; k - последний элемент, равный опорному
	srand(unsigned(time(0)));
	long j = l, k = l, sup_el = l + (rand() % (r - l));
	
	//обмен опорного элемента с первым в данном подмассиве
	ChangeMem(arr, sup_el, l);
	
	// сортировка подмассива относительно опорного элемента (< = >)
	for (long i = l + 1; i < r; ++i)
	{
		if (arr[i] < arr[l])
		{
			ChangeMem(arr, ++j, i);
			if (++k != j)
				ChangeMem(arr, k, i);
		}
		else if (arr[i] == arr[l])
		{
			ChangeMem(arr, ++k, i);
		}
	}
	
	// постановка опорного элемента в правильное место
    ChangeMem(arr, j, l);
	
	return {j, ++k};
}

void QuickSort(long arr[], long l, long r)
{
	//сортировка без хвостовой рекурсии
	pair<int, int> p;
    while (l < r)
    {
	    p = Partition(arr, l, r);
	    QuickSort(arr, l, p.first);
        l = p.second;
    }
}

long BinarSearch(long arr[], long n, long point, bool eql)
{
	bool now_mem, lef_mem, rgt_mem;
	int mem, left = 0, right = n - 1;
	
	while (left <= right)
	{
		mem = left + (right - left) / 2;
		//вычисление логических выражения для границы 1) меньше или равно - больше 2) меньше - равно или больше
		if (eql)
		{
			now_mem = arr[mem] > point;
			lef_mem = (mem == 0 || (mem - 1 >= 0 && arr[mem - 1] <= point));
			rgt_mem = (mem == n - 1 || (mem + 1 <= n - 1 && arr[mem + 1] > point));
		}
		else
		{
			now_mem = arr[mem] >= point;
			lef_mem = (mem == 0 || (mem - 1 >= 0 && arr[mem - 1] < point));
			rgt_mem = (mem == n - 1 || (mem + 1 <= n - 1 && arr[mem + 1] >= point));
		}
		
		//проверка значения как границы разделения элементов на большие и меньшие нашего значения		
		if (lef_mem && rgt_mem)
		{
			if (now_mem)
				return mem;
			else 
				return mem + 1;
		}
		else if (!now_mem)
			left = mem + 1;
		else 
			right = mem - 1;
	}
	
	return 0;
}