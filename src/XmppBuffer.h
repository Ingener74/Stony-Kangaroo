//
// Created by pavel on 22.03.16.
//

#ifndef PROJECT_XMPPBUFFER_H
#define PROJECT_XMPPBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <deque>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <gloox/client.h>
#include <gloox/messagehandler.h>

class Bot: public gloox::MessageHandler {
public:
    Bot(const std::string& jid, const std::string& password);
    virtual ~Bot();

    void sendMessage(const std::string&);

private:
    virtual void handleMessage(const gloox::Message&, gloox::MessageSession*) override ;

    std::unique_ptr<gloox::Client> m_client;

    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cond;

    gloox::JID m_master;
    std::deque<std::string> m_missingMessages;
    bool m_work;
};

class XmppBuffer: public std::streambuf {
public:
    XmppBuffer(const std::string &userJid, const std::string &password);
    virtual ~XmppBuffer();

    virtual int_type overflow(int_type c = traits_type::eof());
    virtual int sync();

private:
    std::unique_ptr<Bot> m_bot;
    std::vector<char> m_buffer;
};


#endif //PROJECT_XMPPBUFFER_H
