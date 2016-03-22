//
// Created by pavel on 22.03.16.
//

#include <iostream>
#include "PrintfBuffer.h"

PrintfBuffer::PrintfBuffer() :
        _buffer(1 << 12) {
    setp(_buffer.data(), _buffer.data() + _buffer.size());
}

PrintfBuffer::~PrintfBuffer() {

}

std::streambuf::int_type PrintfBuffer::overflow(int_type c) {
    size_t pos = _buffer.size();
    _buffer.resize(_buffer.size() * 2);
    setp(_buffer.data(), _buffer.data() + _buffer.size());
    pbump(pos);
    *pptr() = c;
    pbump(1);
    return traits_type::not_eof(c);
}


int PrintfBuffer::sync() {
    printf("%s", _buffer.data()); // output
    for (auto &i: _buffer) i = 0; // clean
    setp(_buffer.data(), _buffer.data() + _buffer.size()); // reset
    return 0;
}

