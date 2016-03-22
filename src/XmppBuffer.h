//
// Created by pavel on 22.03.16.
//

#ifndef PROJECT_XMPPBUFFER_H
#define PROJECT_XMPPBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include <gloox/client.h>
#include <gloox/messagehandler.h>

class XmppBuffer: public std::streambuf, public gloox::MessageHandler {
public:
    XmppBuffer(const std::string &server, const std::string &password);
    virtual ~XmppBuffer();

    virtual void handleMessage(const gloox::Message &msg, gloox::MessageSession *session) override ;

    virtual int_type overflow(int_type c = traits_type::eof());
    virtual int sync();

private:
    std::vector<char> _buffer;
    std::unique_ptr<gloox::Client> m_client;
};


#endif //PROJECT_XMPPBUFFER_H
