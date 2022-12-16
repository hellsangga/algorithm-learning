#include <iostream>
#include <vector>
#include <chrono>
#include <string>

class Timer
{
public:
	Timer(std::string name)
	{
		m_name = name;
		m_start = std::chrono::system_clock::now();
		std::cout << m_name << " timer satrt\n";
	}

	~Timer()
	{
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start);

		std::cout << m_name  << " usage_time: " << duration.count() << " ms\n";
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_start;
	std::string m_name;
};

namespace luo
{
	void quick_sort(std::vector<int>& values, int s, int e, int ch);

	void selection_sort(std::vector<int>& values);

	void insertion_sort(std::vector<int>& values);

	void shell_sort(std::vector<int>& values);

	enum MergeSortMethod
	{
		TOP_DOWN,
		DOWN_TOP
	};

	void merge_sort(std::vector<int>& values, int method);

	void entropy_optimal_sort(std::vector<int>& values, int s, int e);
}


int main()
{
	int N = 25;
	srand(time(0));

	std::vector<int> v;
	for (int i = 0; i < N; i++)
	{
		int x = rand();
		v.push_back(x);
	}

	{
		std::vector<int> shs = v;
		Timer t("shell_sort");
		luo::shell_sort(shs);

		for (int i = 0; i < shs.size(); i++)
			std::cout << shs[i] << " ";
		std::cout << "\n";
	}
}