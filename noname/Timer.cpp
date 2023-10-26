#include <iostream>
#include <chrono>

class SimpleTimer
{
public:
	SimpleTimer()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	~SimpleTimer()
	{
		_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = _end - _start;
		std::cout << "Duration of code = " << duration.count() << " seconds\n";
	}
private:
	std::chrono::high_resolution_clock::time_point _start, _end;
};