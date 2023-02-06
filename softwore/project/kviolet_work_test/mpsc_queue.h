/*
MIT License

Copyright (c) 2018 Meng Rao <raomeng1@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <deque>

template<typename TypeT>
class MPSCQueue
{
public:
    struct Entry
    {
        Entry *next;
        TypeT data;
    };

    MPSCQueue(uint32_t init_size)
            : pending_tail((Entry *) &pending_head), max_entry(init_size)
    {
        while (init_size--)
        {
            Entry *cur = _Alloc();
            cur->next = empty_top;
            empty_top = cur;
        }
    }

    Entry *Alloc()
    {
        Entry *top = FetchAndLock(empty_top, (Entry *) EmptyLock);
        if (top == nullptr)
        {
            empty_top = nullptr;
            return _Alloc();
        }
        empty_top = top->next;
        return top;
    }

    // A correct and the most efficient implementation that I've tested
    // In normal case pending_tail saves the address of tail entry(if empty it save the address of head)
    // contention winner will temporarily set pending_tail to PendingLock
    void Push(Entry *entry)
    {
        Entry *tail = FetchAndLock(pending_tail, (Entry *) PendingLock);
        tail->next = entry;
        asm volatile("" : : "m"(tail->next), "m"(pending_tail) :);       // memory fence
        pending_tail = entry;
    }


    // Similar to Push(), but it directly set pending_tail to the address of pending_head
    Entry *PopAll()
    {
        if (pending_tail == (Entry *) &pending_head) return nullptr;
        Entry *tail = FetchAndLock(pending_tail, (Entry *) PendingLock);
        Entry *ret = pending_head;
        asm volatile("" : : "m"(pending_tail) :); // memory fence
        pending_tail = (Entry *) &pending_head;
        tail->next = nullptr;
        return ret;
    }

    void Recycle(Entry *first, Entry *last)
    {
        Entry *top = FetchAndLock(empty_top, (Entry *) EmptyLock);
        last->next = top;
        asm volatile("" : : "m"(last->next), "m"(empty_top) :); // memory fence
        empty_top = first;
    }

public:
    void Push(TypeT &value)
    {
        Entry *entry;

        while ((entry = Alloc()) == nullptr)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(50));
        }

        entry->data = value;

        Push(entry);
    }

    void WaitPopAll(std::vector<TypeT> &value)
    {

        while (true)
        {
            auto *list = PopAll();

            if (!list)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(15));
                continue;
            }
            auto cur = list;
            while (true)
            {
                value.push_back(cur->data);

                if (!cur->next)
                {
                    break;
                }
                cur = cur->next;

            }
            Recycle(list, cur);

            break;
        }

    }

private:
    template<class T>
    static T FetchAndLock(volatile T &var, T lock_val)
    {
        T val = var;
        while (true)
        {
            while (__builtin_expect(val == lock_val, 0)) val = var;
            T new_val = __sync_val_compare_and_swap(&var, val, lock_val);
            if (__builtin_expect(new_val == val, 1)) break;
            val = new_val;
        }
        return val;
    }

    Entry *_Alloc()
    {
        if (entry_cnt >= max_entry) return nullptr;
        int cnt = FetchAndLock(entry_cnt, -1);
        if (__builtin_expect(cnt >= max_entry, 0))
        {
            entry_cnt = cnt;
            return nullptr;
        }
        deq.emplace_back();
        Entry *ret = &deq.back();
        asm volatile("" : : "m"(entry_cnt) :); // memory fence
        entry_cnt = deq.size();
        return ret;
    }

private:
    static constexpr long PendingLock = 0x8;
    static constexpr long EmptyLock = 0x10;

    alignas(64) Entry *volatile pending_tail;
    Entry *pending_head;

    alignas(64) Entry *volatile empty_top = nullptr;

    alignas(64) volatile int entry_cnt = 0;
    std::deque<Entry> deq;
    const int max_entry;
};
