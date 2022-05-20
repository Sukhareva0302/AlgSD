#include <iostream>
#include "ListNode.h"
#include"Queue.h"
using namespace std;

int maxFlow(NodeList list, string start_name, string finish_name)
{
	int flow = 0;
	Node* start = list.find(start_name);
	Node* finish = list.find(finish_name);
	while (true)
	{
		reset_prev(list);
		Queue<Node*>* queue = new Queue<Node*>(start);
		while (!queue->Empty())
		{
			Node* cur_parent = queue->top();
			queue->pop();
			List<string> to = cur_parent->capacity.get_keys();
			List<int> cost = cur_parent->capacity.get_values();
			for (int i = 0; i < to.get_size(); i++)
			{
				if (cost.at(i) > 0)
				{
					Node* cur = list.find(to.at(i));
					if (cur->parent == NULL)
					{
						cur->parent = cur_parent;
						if (cur == finish)
						{
							queue->clear();
							break;
						}
						queue->push(cur);
					}
				}
			}
		}
		if (finish->parent == NULL)
		{
			break;
		}
		int minFlow = INT_MAX;
		Node* cur = finish;
		while (cur != start)
		{
			Node* prev = cur->parent;
			int cap = prev->capacity.find(cur->name);
			if (cap < minFlow)
			{
				minFlow = cap;
			}
			cur = cur->parent;
		}
		cur = finish;
		while (cur != start)
		{
			Node* prev = cur->parent;
			prev->update_flow(cur->name, prev->get_flow(cur->name) + minFlow);
			prev->update_capacity(cur->name, prev->get_capacity(cur->name) - minFlow);
			cur = cur->parent;
		}
		flow = flow + minFlow;
	}
	return flow;
};