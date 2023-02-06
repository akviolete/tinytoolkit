#ifndef __ZMQ_YQUEUE_HPP_INCLUDED__
#define __ZMQ_YQUEUE_HPP_INCLUDED__

#include <stdlib.h>
#include <stddef.h>

#include "atomic_ptr.hpp"

namespace zmq
{
    template<typename T, int N>
    class yqueue_t
    {
    public:
        //  Create the queue.
        inline yqueue_t()
        {
            _begin_chunk = allocate_chunk();
            _begin_pos = 0;

            _back_chunk = NULL;
            _back_pos = 0;

            _end_chunk = _begin_chunk;
            _end_pos = 0;
        }

        //  Destroy the queue.
        inline ~yqueue_t()
        {
            while (true)
            {
                if (_begin_chunk == _end_chunk)
                {
                    free(_begin_chunk);
                    break;
                }
                chunk_t *o = _begin_chunk;
                _begin_chunk = _begin_chunk->next;
                free(o);
            }

            chunk_t *sc = _spare_chunk.xchg(NULL);
            free(sc);
        }

        //  Returns reference to the front element of the queue.
        //  If the queue is empty, behaviour is undefined.
        inline T &front()
        {
            return _begin_chunk->values[_begin_pos];
        }

        //  Returns reference to the back element of the queue.
        //  If the queue is empty, behaviour is undefined.
        inline T &back()
        {
            return _back_chunk->values[_back_pos];
        }

        //  Adds an element to the back end of the queue.
        inline void push()
        {
            _back_chunk = _end_chunk;
            _back_pos = _end_pos;

            if (++_end_pos != N)
                return;

            chunk_t *sc = _spare_chunk.xchg(NULL);
            if (sc)
            {
                _end_chunk->next = sc;
                sc->prev = _end_chunk;
            } else
            {
                _end_chunk->next = allocate_chunk();

                _end_chunk->next->prev = _end_chunk;
            }
            _end_chunk = _end_chunk->next;
            _end_pos = 0;
        }

        //  Removes element from the back end of the queue. In other words
        //  it rollbacks last push to the queue. Take care: Caller is
        //  responsible for destroying the object being unpushed.
        //  The caller must also guarantee that the queue isn't empty when
        //  unpush is called. It cannot be done automatically as the read
        //  side of the queue can be managed by different, completely
        //  unsynchronised thread.
        inline void unpush()
        {
            //  First, move 'back' one position backwards.
            if (_back_pos)
                --_back_pos;
            else
            {
                _back_pos = N - 1;
                _back_chunk = _back_chunk->prev;
            }

            //  Now, move 'end' position backwards. Note that obsolete end chunk
            //  is not used as a spare chunk. The analysis shows that doing so
            //  would require free and atomic operation per chunk deallocated
            //  instead of a simple free.
            if (_end_pos)
                --_end_pos;
            else
            {
                _end_pos = N - 1;
                _end_chunk = _end_chunk->prev;
                free(_end_chunk->next);
                _end_chunk->next = NULL;
            }
        }

        //  Removes an element from the front end of the queue.
        inline void pop()
        {
            if (++_begin_pos == N)
            {
                chunk_t *o = _begin_chunk;
                _begin_chunk = _begin_chunk->next;
                _begin_chunk->prev = NULL;
                _begin_pos = 0;

                //  'o' has been more recently used than _spare_chunk,
                //  so for cache reasons we'll get rid of the spare and
                //  use 'o' as the spare.
                chunk_t *cs = _spare_chunk.xchg(o);
                free(cs);
            }
        }

    private:
        //  Individual memory chunk to hold N elements.
        struct chunk_t
        {
            T values[N];
            chunk_t *prev;
            chunk_t *next;
        };

        static inline chunk_t *allocate_chunk()
        {
            auto *ptr = static_cast<chunk_t *> (malloc(sizeof(chunk_t)));

            if (!ptr)
            {
                throw std::runtime_error("allocate_chunk");
            }
            return ptr;
        }

        //  Back position may point to invalid memory if the queue is empty,
        //  while begin & end positions are always valid. Begin position is
        //  accessed exclusively be queue reader (front/pop), while back and
        //  end positions are accessed exclusively by queue writer (back/push).
        chunk_t *_begin_chunk;
        int _begin_pos;
        chunk_t *_back_chunk;
        int _back_pos;
        chunk_t *_end_chunk;
        int _end_pos;

        //  People are likely to produce and consume at similar rates.  In
        //  this scenario holding onto the most recently freed chunk saves
        //  us from having to call malloc/free.
        atomic_ptr_t<chunk_t> _spare_chunk;

    private:
        yqueue_t(const yqueue_t &);

        yqueue_t &operator=(const yqueue_t &);

    };
}

#endif
