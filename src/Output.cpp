//
// Created by pavel on 22.03.16.
//

#include <iostream>
#include "Output.h"
#include "PrintfBuffer.h"

using namespace std;

Output &Output::instance() {
    static Output self{};
    return self;
}

Output::~Output() {

}

Output::Output() {
    m_buffer.reset(new PrintfBuffer());
    m_stream.reset(new ostream(m_buffer.get()));
}

std::ostream &Output::out() {
    return *m_stream;
}

