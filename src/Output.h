//
// Created by pavel on 22.03.16.
//

#ifndef PROJECT_OUTPUT_H
#define PROJECT_OUTPUT_H


#include <bits/unique_ptr.h>

class Output {
public:
    static Output& instance();
    virtual ~Output();

    template<typename TBuffer, typename... Args>
    void setBuffer(Args&& ... args){
        m_buffer.reset(new TBuffer(args...));
    }

    std::ostream& out();

private:
    Output();

    std::unique_ptr<std::streambuf> m_buffer;
    std::unique_ptr<std::ostream> m_stream;
};


#endif //PROJECT_OUTPUT_H
