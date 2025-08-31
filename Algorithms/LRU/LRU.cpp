// LRU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Node {
private:
    int key;
    char value;
public:
    Node(int k, char v) : key(k), value(v) {}
	char getValue() const { return value; }
	int getKey() { return key; }
};

class LRUCache {
private:
	int capacity;
	list<Node> cache;
	unordered_map<int, list<Node>::iterator> map;

public:
        LRUCache(int capacity) : capacity(capacity) {
			//initialization
		}

		void insertItem(int key, char value) {
			//insert item
			// if key exists, update value and move to front
			auto it = map.find(key);
			if (it != map.end())
			{
				auto itr = it->second;

				cout << "Updated " << key << " from " << itr->getValue() << " to " << value << endl;
				cache.erase(itr);
				cache.push_front(Node(key, value));
			}
			else
			{
				// if cache is full, remove least recently used item
				if (cache.size() == capacity)
				{
					//cout << "Removing " << cache.back().getKey() << endl;
					cache.pop_back();
				}

				cout << "Inserting " << key << endl;
				cache.push_front(Node(key, value));
			}
			map[key] = cache.begin();

			displayCache();
		}

		Node* getRecentlyUsed()
		{
			Node* item = NULL;
			if (!cache.empty())
			{
				item = &cache.front();
				cout << "Most recently used: \n" << item->getKey() << " - " << item->getValue() << endl;
			}
			else
			{
				cout << "Cache is empty" << endl;
			}

			return item;
		}
		void displayCache() {
			//display cache
			for(auto item: cache)
			{
				cout << "(" << item.getKey() << ", " << item.getValue() << ") -> ";
			}
			cout << endl;
		}
};

int main()
{
    std::cout << "LRU Algorithm\n";

	LRUCache lru(3);

	lru.insertItem(1, 'A');
	lru.insertItem(2, 'B');
	lru.insertItem(3, 'C');
	lru.insertItem(4, 'D');
	lru.insertItem(3, 'E');

	lru.getRecentlyUsed();

	return 0;
}
