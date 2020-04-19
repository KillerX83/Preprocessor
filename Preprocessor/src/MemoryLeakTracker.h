#pragma once
#include <iostream>
class MemoryLeakTracker
{
public:
	inline void Add(size_t size) { m_MemoryLeakSize += size; m_Allocated += size; }
	inline void Sub(size_t size) { m_MemoryLeakSize -= size; }

	~MemoryLeakTracker()
	{
		std::cout << std::endl << "MemoryLeakSize = " << m_MemoryLeakSize << " bytes" << std::endl; 
		std::cout << std::endl << "Allocated = " << m_Allocated << " bytes" << std::endl; 
	}
private:
	size_t m_MemoryLeakSize = 0;
	size_t m_Allocated = 0;
};

MemoryLeakTracker tracker;

void* operator new(size_t size)
{
	tracker.Add(size);
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	tracker.Sub(size);
	free(memory);
}


