#include "PriorityQueue.h"
#include "packet.h"
#include <vector>

PriorityQueue::PriorityQueue() {
	count = 0;
}


bool PriorityQueue::isEmpty() {
	return !count;
}

int PriorityQueue::size() {
	return count;
}

Packet PriorityQueue::top() {
	if (isEmpty()) {
		return Packet();
	}
	return heap.front();
}

Packet PriorityQueue::pop() {
	if (isEmpty()) {
		return Packet();
	}
	Packet root = heap.front();
	heap[0] = heap[count - 1];
	heap.pop_back();

	count--;

	heapify_down(0);
	return root;
}

void PriorityQueue::push(Packet p) {
	heap.push_back(p);
	count++;
	heapify_up(count - 1);
}

void PriorityQueue::heapify_down(int index) {
	int left = (index * 2) + 1;
	int right = (index * 2) + 2;
	int largest = index;

	if (left < count && heap[left].priority() > heap[largest].priority()) {
		largest = left;
	}

	if (right < count && heap[right].priority() > heap[largest].priority()) {
		largest = right;
	}

	if (largest != index) {
		Packet temp = heap[index];
		heap[index] = heap[largest];
		heap[largest] = temp;

		heapify_down(largest);
	}
}

void PriorityQueue::heapify_up(int index) {
	if (index != 0 && heap[index].priority() > heap[(index - 1) / 2].priority()) {
		Packet parent = heap[(index - 1) / 2];
		heap[(index - 1) / 2] = heap[index];
		heap[index] = parent;

		heapify_up((index - 1) / 2);
	}
}
