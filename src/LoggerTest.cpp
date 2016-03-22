
#include <iostream>

#include "Logger.h"
#include "Output.h"
#include "XmppBuffer.h"

using namespace std;

int main(int argc, char **argv) {

    cout << "Usage: ./LoggerTest <log-level: 0 - ERROR, 1 - WARNING, 2 - DEBUG, 3 - INFO,>" << endl;
    cout << "Example: ./LoggerTest 3" << endl;

    Output::instance().setBuffer<XmppBuffer>("", "");

	if(argc > 1)
		logger::Logger::setMaxLogLevel(static_cast<logger::Priority>(stoi(argv[1])));

	logger::info << "Info message " << "foo " << 42 << logger::end;
	logger::debug << "Debug message "  << "bar " << 42 << logger::end;
	logger::warning << "Warning message " << "baz " << 42 << logger::end;
	logger::error << "Error message " << "quz " << 42 << logger::end;

	logger::info("Info format %s %d", "foo", 42);
	logger::debug("Debug format %s %d", "bar", 42);
	logger::warning("Warnin format %s %d", "baz", 42);
	logger::error("Error format %s %d", "quz", 42);
}



