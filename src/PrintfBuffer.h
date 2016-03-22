//
// Created by pavel on 22.03.16.
//

#ifndef PROJECT_PRINTFBUFFER_H
#define PROJECT_PRINTFBUFFER_H

#include <iostream>
#include <vector>

class PrintfBuffer : public std::streambuf {
public:
    PrintfBuffer();
    virtual ~PrintfBuffer();

    virtual int_type overflow(int_type c = traits_type::eof());
    virtual int sync();

private:
    std::vector<char> _buffer;
};


#endif //PROJECT_PRINTFBUFFER_H
