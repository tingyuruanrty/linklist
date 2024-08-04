#ifndef STRING_LIST_H
#define STRING_LIST_H

#include<iostream>
#include<sstream>

class String_List
{
private:
    struct Node
    {
        std::string data; 
        Node* next; 
        Node(std::string s = "") : data(s), next(nullptr) {}
    };

    Node* _head; 
    Node* _tail; 
    Node* _prev_to_current; 
    size_t _size; 

public: 
    String_List() : 
        _head(new Node("_SENTINEL_")), 
        _tail(_head), 
        _prev_to_current(_head), 
        _size(0) {}

    ~String_List()
    {
        clear(); 
        delete _head; 
    }

    String_List* insert_at_current(std::string s)
    {
        Node* new_node = new Node(s); 
        new_node->next = _prev_to_current->next;
        _prev_to_current->next = new_node; 

        if (_tail == _prev_to_current)
        {
            _tail = new_node; 
        }

        _size++; 
        return this; 
    }

    String_List* push_back(std::string s)
    {
        Node* saved_prev = _prev_to_current; 
        _prev_to_current = _tail; 
        insert_at_current(s); 
        _prev_to_current = saved_prev; 
        return this; 
    }

    String_List* push_front(std::string s)
    {
        Node* saved_prev = _prev_to_current; 
        _prev_to_current = _head; 
        insert_at_current(s); 
        _prev_to_current = saved_prev; 
        return this; 
    }

    String_List* advance_current()
    {
        if (_prev_to_current == _tail)
        {
            return nullptr; 
        }

        _prev_to_current = _prev_to_current->next; 
        return this; 
    }

    std::string get_current() const
    {
        if (_prev_to_current == _tail)
        {
            return _head->data; 
        }

        return _prev_to_current->next->data; 
    }

    String_List* remove_at_current()
    {
        if (_prev_to_current == _tail)
        {
            return nullptr; 
        }

        Node* to_delete = _prev_to_current->next; 
        if (_tail == to_delete)
        {
            _tail = _prev_to_current; 
        }
        _prev_to_current->next = to_delete->next; 
        delete to_delete; 
        _size--; 
        return this; 
    }

    size_t get_size() const 
    {
        return _size; 
    }

    String_List* rewind()
    {
        _prev_to_current = _head; 
        return this; 
    }

    void clear()
    {
        _prev_to_current = _head; 
        while (remove_at_current() != nullptr);
    }

    std::string& find_item(std::string s) const 
    {
        static std::string sentinel = "_SENTINEL_"; 
        if (sentinel != "_SENTINEL_")
        {
            sentinel = "_SENTINEL_"; 
        }

        Node* runner = _head->next; 
        while (runner != nullptr)
        {
            if (runner->data == s)
            {
                return runner->data; 
            }
            runner = runner->next; 
        }

        return sentinel; 
    }

    std::string to_string() const
    {
        const size_t MAX_LINES = 25; 
        std::ostringstream oss; 
        oss << "# String_List - " << _size << " entries total. Starting at cursor:\n";
        Node* runner = _prev_to_current->next; 
        size_t counter = 0; 
        while (runner != nullptr && counter < MAX_LINES)
        {
            oss << runner->data << std::endl; 
            counter++; 
            runner = runner->next; 
        }
        if (runner != nullptr)
        {
            oss << "..." << std::endl; 
        }
        return oss.str(); 
    }

    // Don't remove this line
    friend class Tests; 
};

#endif 