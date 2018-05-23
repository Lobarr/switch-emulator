#pragma once
#include "packet.h"

struct Node {
	Node();
	int priority;
	Packet p;
	Node *next;
};

Node::Node() {
	next = NULL;
}