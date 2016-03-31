//
// Created by pavel on 22.03.16.
//

#include <gloox/message.h>
#include <mutex>
#include "XmppBuffer.h"

using namespace std;
using namespace gloox;

Bot::Bot(const std::string &jid, const std::string &password) {
    m_thread = thread([=]{
        try {
            cout << "jid " << jid << ", password " << password << endl;
            Client client{{jid}, password};
            client.connect();

            unique_lock<mutex> lock(m_mutex);
            while(!m_missingMessages.empty() || m_work){
                if(!m_missingMessages.empty() && m_master){
                    for(const auto &message : m_missingMessages){
                        Message msg{Message::MessageType::Chat, m_master, message};
                        client.send(msg);
                    }
                }
                m_cond.wait(lock);
            }
        }catch (const exception& e){
            cerr << e.what() << endl;
        }
    });
}

Bot::~Bot() {
    m_thread.join();
}

void Bot::sendMessage(const std::string & message) {
    unique_lock<mutex> lock(m_mutex);
    m_missingMessages.push_back(message);
    m_cond.notify_all();
}

void Bot::handleMessage(const gloox::Message & message, gloox::MessageSession *) {
    unique_lock<mutex> lock(m_mutex);
    m_master = message.from();
    m_cond.notify_all();
}


XmppBuffer::XmppBuffer(const std::string &userJid, const std::string &password) :
        m_buffer(1 << 12) {
    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    m_bot.reset(new Bot(userJid, password));
}

XmppBuffer::~XmppBuffer() {
}

std::streambuf::int_type XmppBuffer::overflow(int c) {
    size_t pos = m_buffer.size();
    m_buffer.resize(m_buffer.size() * 2);
    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    pbump(pos);
    *pptr() = c;
    pbump(1);
    return traits_type::not_eof(c);
}

int XmppBuffer::sync() {
    m_bot->sendMessage(std::string{m_buffer.data()});
    for (auto &i: m_buffer) i = 0; // clean
    setp(m_buffer.data(), m_buffer.data() + m_buffer.size()); // reset
    return 0;
}
