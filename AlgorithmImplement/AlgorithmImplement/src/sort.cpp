#include <vector>
#include <iostream>

namespace luo
{
	void exchange(std::vector<int>& v, int i, int j)
	{
		int temp = v[i];
		v[i] = v[j];
		v[j] = temp;
	}


	void selection_sort(std::vector<int>& values)
	{
		if (values.empty())
			return;

		int size = values.size();
		for (int i = 0; i < size - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < size; j++)
			{
				if (values[j] < values[min])
					min = j;
			}

			exchange(values, i, min);
		}
	}


	void insertion_sort(std::vector<int>& values)
	{
		if (values.empty())
			return;

		int end = values.size() - 1;

		for (int i = 0; i <= end; i++)
		{
			for (int j = i + 1; j > 0; j--)
			{
				if (values[j] >= values[j - 1])
					break;

				exchange(values, j, j - 1);
			}
		}
	}

	void insertion_sort(std::vector<int>& values, int s, int e)
	{
		if (values.empty() || s >= e || s < 0 || e <= 0) return;
		if (s >= values.size() - 1 || e > values.size() - 1) return;

		for (int i = s; i < e; i++)
		{
			for (int j = i + 1; j > s; j--)
			{
				if (values[j] >= values[j - 1])
					break;

				exchange(values, j, j - 1);
			}
		}
	}


	void shell_sort(std::vector<int>& values)
	{
		if (values.empty())
			return;

		int size = values.size();
		int h = 1;
		while (h < size / 3)
			h = h * 3 + 1;

		while (h >= 1)
		{
			for (int i = h; i < size; i++)
			{
				for (int j = i - h; j >= 0; j -= h)
				{
					if (values[j + h] >= values[j])
						break;

					exchange(values, j + h, j);
				}
			}

			h = h / 3;
		}
	}


	static std::vector<int> temp;

	void merge(std::vector<int>& v, int s, int m, int e)
	{
		for (size_t i = s; i <= e; i++)
			temp[i] = v[i];

		int i = s, j = m + 1;

		for (int k = s; k <= e; k++)
		{
			if (i > m) v[k] = temp[j++];
			else if (j > e) v[k] = temp[i++];
			else if (temp[i] <= temp[j]) v[k] = temp[i++];
			else v[k] = temp[j++];
		}
	}

	void top_down_merge_sort(std::vector<int>& v, int s, int e)
	{
		if (s >= e) return;

		int mid = s + (e - s) / 2;

		top_down_merge_sort(v, s, mid);
		top_down_merge_sort(v, mid + 1, e);

		merge(v, s, mid, e);
	}

	void down_top_merge_sort(std::vector<int>& v)
	{
		int size = v.size();
		int m, e;
		for (int i = 1; i < size; i = 2 * i)
		{
			for (int j = 0; j < size - i; j += 2 * i)
			{
				m = j + i - 1;
				e = (j + 2 * i - 1) <= (size - 1) ? (j + 2 * i - 1) : (size - 1);
				merge(v, j, m, e);
			}
		}
	}

	enum MergeSortMethod
	{
		TOP_DOWN,
		DOWN_TOP
	};

	void merge_sort(std::vector<int>& values, int method)
	{
		if (values.empty())
			return;

		temp = values;

		int start = 0;
		int end = values.size() - 1;

		switch (method)
		{
		case TOP_DOWN:
			top_down_merge_sort(values, start, end);
			break;

		case DOWN_TOP:
			down_top_merge_sort(values);
			break;

		default:
			break;
		}
	}


	int partition(std::vector<int>& v, int s, int e)
	{
		int mark_val = v[s];
		int i = s, j = e + 1;

		while (true)
		{
			while (v[++i] < mark_val)
			{
				if (i == e)
					break;
			}

			while (v[--j] >= mark_val)
			{
				if (j == s)
					break;
			}

			if (i >= j)
				break;

			exchange(v, i, j);
		}

		exchange(v, s, j);

		return j;
	}

	const int N = 10;

	void quick_sort(std::vector<int>& values, int s, int e, int ch)
	{
		if (s >= e)
			return;

		if (ch)
		{
			if (e - s <= N)
			{
				insertion_sort(values, s, e);
				return;
			}
		}

		int mark = partition(values, s, e);
		quick_sort(values, s, mark - 1, ch);
		quick_sort(values, mark + 1, e, ch);
	}

	void entropy_optimal_sort(std::vector<int>& values, int s, int e)
	{
		if (s >= e)
			return;

		int lt = s, i = s + 1, gt = e;
		int mark_val = values[s];
		while (i <= gt)
		{
			if (mark_val > values[i]) exchange(values, lt++, i++);
			else if (mark_val < values[i]) exchange(values, i, gt--);
			else i++;
		}

		entropy_optimal_sort(values, s, lt - 1);
		entropy_optimal_sort(values, gt + 1, e);
	}
}