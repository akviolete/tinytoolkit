#ifndef RINGBUF_H
#define RINGBUF_H

#include <iostream>


/**
 * 找出小于等于N的最大的2的幂指数
 * */
uint32_t FindPowerExpTwoDown(uint32_t num);

/**
 * 找出大于等于N的最小的2的幂指数
 * */
uint32_t FindPowerExpTwoUp(uint32_t num);

class RingQueueLockFree
{
public:
    RingQueueLockFree() = delete;

    RingQueueLockFree(uint32_t size)
    {
        _in = _out = 0;
        _size = _mask = FindPowerExpTwoUp(size);

        _buffer = new unsigned char[_size];
    }

    ~RingQueueLockFree()
    {
        delete[]_buffer;
        _buffer = nullptr;
    }

public:

private:
    uint32_t _in{0};
    uint32_t _out{0};
    uint32_t _mask{0};
    uint32_t _size{0};
    unsigned char *_buffer{nullptr};
};


struct ringbuf_t
{
    unsigned char *data;
    unsigned int in, out, mask, esize;
};


void ringbuf_init(struct ringbuf_t *self, unsigned int item_size, void *buf, unsigned int bufsize);

// item count in buf
unsigned int ringbuf_len(struct ringbuf_t *self);

// max item count in buf
unsigned int ringbuf_cap(struct ringbuf_t *self);

// avail item count
unsigned int ringbuf_avail(struct ringbuf_t *self);

int ringbuf_is_full(struct ringbuf_t *self);

int ringbuf_is_empty(struct ringbuf_t *self);

unsigned int ringbuf_in(struct ringbuf_t *self, const void *buf, unsigned int item_count);

unsigned int ringbuf_out(struct ringbuf_t *self, void *buf, unsigned int item_count);

unsigned int ringbuf_out_peek(struct ringbuf_t *self, void *buf, unsigned int len);


#endif // RINGBUF_H
