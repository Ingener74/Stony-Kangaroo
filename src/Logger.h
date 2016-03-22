#ifndef BACKENDS_LOGGER_SRC_LOGGER_H_
#define BACKENDS_LOGGER_SRC_LOGGER_H_

#include <iostream>
#include <sstream>
#include <map>
#include <mutex>
#include <thread>

namespace logger
{

/*
	Тестовое задание
	Необходимо написать класс предназначенный для логирования.

	Основные функциональные требования:
	- простой способ логирования
	- поддержка уровней (приоритетов) логирования. Возможны следующие
	типы сообщений в порядке возрастания приоритетов: debug, info, warn, error,
	fatal - возможность управления уровнем логирования. При установке
	определенного уровня сообщения с меньшим приоритетом должны быть
	отфильтрованы

	- возможность вывода дополнительной информации: время, номер строки,
			имя файла, уровень

	- поддержка вывода результатов логирования в различные форматы

			приемников: файл и stdout. Также предусмотреть возможность гибкого
	расширения приемников в случае необходимости, например, логирование в
	БД, отправка в jabber или на mail
*/


enum Priority
{
	ERROR, WARNING, DEBUG, INFO,
};

class Logger
{
public:
	Logger(Priority);
	virtual ~Logger();

	static void setMaxLogLevel(Priority);

	Logger& operator()(const std::string& format, ...);

	template<typename T>
	Logger& operator<<(T const& t)
	{
		if (m_start)
		{
			m_out << getTime() << " " << s_priorities.at(m_priority) << " ";
			m_start = false;
		}
		m_out << t;
		return *this;
	}

	Logger& setEmpty();
private:
	std::string getTime() const;

	static const std::map<Priority, std::string> s_priorities;

	Priority m_priority;
	std::stringstream m_out;
	bool m_start;

	static Priority s_maxPriorityLevel;
};

class End
{
public:
	End();
	virtual ~End();

	friend Logger& operator<<(Logger&, const End&);
};

extern Logger debug;
extern Logger error;
extern Logger warning;
extern Logger info;
extern End end;

}  // namespace log

#endif /* BACKENDS_LOGGER_SRC_LOGGER_H_ */
