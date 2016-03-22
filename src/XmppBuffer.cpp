//
// Created by pavel on 22.03.16.
//

#include <gloox/message.h>
#include "XmppBuffer.h"

using namespace std;
using namespace gloox;

XmppBuffer::XmppBuffer(const std::string &server, const std::string &password) {
    JID jid{server};
    m_client.reset(new Client(jid, password));
    m_client->connect();
}

XmppBuffer::~XmppBuffer() {
}

void XmppBuffer::handleMessage(const gloox::Message &msg, gloox::MessageSession *session) {
}

std::streambuf::int_type XmppBuffer::overflow(int c) {
    size_t pos = _buffer.size();
    _buffer.resize(_buffer.size() * 2);
    setp(_buffer.data(), _buffer.data() + _buffer.size());
    pbump(pos);
    *pptr() = c;
    pbump(1);
    return traits_type::not_eof(c);
}

int XmppBuffer::sync() {
    // printf("%s", _buffer.data()); // output
    JID jid{};
    Message msg{Message::MessageType::Chat, jid, std::string{_buffer.data()} };
    for (auto &i: _buffer) i = 0; // clean
    setp(_buffer.data(), _buffer.data() + _buffer.size()); // reset
    return 0;
}

