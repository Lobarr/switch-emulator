#pragma once
#include "packet.h"
#include <vector>

class PriorityQueue {
public:
	PriorityQueue();
	void push(Packet p);
	Packet pop();
	Packet top();
	int size();
	bool isEmpty();

	void print() {
		for (int i = 0; i < count; i++) {
			std::cout << heap[i].priority() << " ";
		}
		std::cout << "\n";
	};
private:
	int count;
	std::vector<Packet> heap;
	void heapify_down(int index);
	void heapify_up(int index);
};



