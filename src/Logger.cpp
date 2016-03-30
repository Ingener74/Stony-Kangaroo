/*
 * Logger.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: pavel
 */

#include <sys/time.h>

#include <cstdarg>
#include <string>
#include <chrono>

#include "Logger.h"
#include "Output.h"

namespace logger
{

using namespace std;
using namespace std::chrono;

const map<Priority, string> Logger::s_priorities{
	{DEBUG,		"D"},
	{INFO,		"I"},
	{ERROR,		"E"},
	{WARNING,	"W"},
};

Priority Logger::s_maxPriorityLevel = INFO;

Logger::Logger(Priority priority) :
	m_priority(priority), m_start(true)
{
}

Logger::~Logger()
{
}

void Logger::setMaxLogLevel(Priority priority)
{
	s_maxPriorityLevel = priority;
}

Logger& Logger::operator()(const string& format, ...)
{
	char dest[1024 * 4];
	va_list args;
	va_start(args, format.c_str());
	vsprintf(dest, format.c_str(), args);
	va_end(args);
	return *this << dest << end;
}

Logger& Logger::setEmpty()
{
	m_start = true;
	if (m_priority <= s_maxPriorityLevel)
	{
        Output::instance().out() << m_out.str() << endl;
	}
	m_out.str(string{ });
	return *this;
}

string Logger::getTime() const
{
	const int dtm_size = 200;
	char date_time[dtm_size];

	time_t rawtime;
	time(&rawtime);

	struct timeval tv;
	gettimeofday(&tv, NULL);

	snprintf(date_time + strftime(date_time, 80, "%G%m%d %H%M%S", localtime(&rawtime)), dtm_size, ".%03d", tv.tv_usec / 1000);

	return string{ date_time };
}

End::End()
{
}

End::~End()
{
}

Logger& operator<<(Logger& out, const End&)
{
	return out.setEmpty();
}

Logger debug{ DEBUG };
Logger error{ ERROR };
Logger warning{ WARNING };
Logger info{ INFO };
End end;

}  // namespace log
