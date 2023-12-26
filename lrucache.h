#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

// Doubly Linked List Node with key and value
struct DLLNode
{
    DLLNode *prev;
    int key;
    int value;
    DLLNode *next;

    DLLNode(int key, int value) : prev(NULL), key(key), value(value), next(NULL) {}
};

// general imlementation of LRU Cache. In our case key will be the vpn and value will be the pfn
class LRUCache
{
    DLLNode *lru; // least recently used -- here head
    DLLNode *mru; // most recently used -- here tail
    int capacity; // maximum capacity of the cache
    int size;     // current size of the cache

    // map to store key to node mapping for access in O(1) (average case)
    unordered_map<int, DLLNode *> umap;

    // get a node and change it to mru
    DLLNode *get_and_make_mru(int key)
    {
        DLLNode *ptr = mru;

        auto itr = umap.find(key);

        // if key not found
        if (itr == umap.end())
            return NULL;
        else
            ptr = itr->second;

        if (ptr == mru)
            return ptr;

        DLLNode *t = ptr;

        // check if ptr->prev is NULL
        if (ptr->prev != NULL)
            ptr->prev->next = ptr->next;
        else
            // if ptr is the lru
            lru = lru->next;

        ptr->next->prev = ptr->prev;

        ptr->prev = mru;
        mru->next = ptr;
        ptr->next = NULL;

        mru = ptr;

        return ptr;
    }

public:
    LRUCache(int capacity)
        : capacity(capacity), size(0), lru(NULL), mru(NULL) {}

    int get(int key)
    {
        DLLNode *ptr = get_and_make_mru(key);

        // if key not found
        if (ptr == NULL)
            return -1;

        return ptr->value;
    }

    void put(int key, int value)
    {
        DLLNode *ptr = get_and_make_mru(key);
        if (ptr != NULL)
        {
            ptr->value = value;
            return;
        }

        // key wasn't there so we add one node
        ptr = new DLLNode(key, value);
        umap[key] = ptr;
        size++;

        if (size == 1)
        {
            lru = ptr;
            mru = ptr;
            return;
        }

        // establishing links
        mru->next = ptr;
        ptr->prev = mru;

        // updating the mru
        mru = ptr;

        if (size > capacity)
        {
            size--;
            // updating lru and removing that key
            lru = lru->next;
            umap.erase(lru->prev->key);
            delete lru->prev;
            lru->prev = NULL;
        }
        return;
    }
};