#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>

class Logger
{
public:
	enum LogLevel 
	{ 
		DEBUG, 
		INFO, 
		WARN, 
		ERROR, 
		NONE
	};

	static LogLevel logLevel;

	// log input arguments with label "DEBUG" to stderr
	template <typename T, typename... Args>
	static void debug(T arg, Args... args)
	{
		log("DEBUG", Logger::DEBUG, arg, args...);
	}

	// log input arguments with label "INFO" to stderr
	template <typename T, typename... Args>
	static void info(T arg, Args... args)
	{
		log("INFO", Logger::INFO, arg, args...);
	}

	// log input arguments with label "WARN" to stderr
	template <typename T, typename... Args>
	static void warn(T arg, Args... args)
	{
		log("WARN", Logger::WARN, arg, args...);
	}

	// log input arguments with label "ERROR" to stderr
	template <typename T, typename... Args>
	static void error(T arg, Args... args)
	{
		log("ERROR", Logger::ERROR, arg, args...);
	}

private:
	// writes argument to stderr
	template <typename T>
	static void _log(T arg)
	{
		std::cerr << arg;
	}

	// recursively writes a sequence of arguments to stderr
	template <typename T, typename... Args>
	static void _log(T arg, Args... args)
	{
		_log(arg);
		_log(args...);
	}

	// write a log message to stderr unless the message's log level is disabled
	template <typename T, typename... Args>
	static void log(const char *label, LogLevel level, T arg, Args... args)
	{
		if (Logger::logLevel <= level)
		{
			std::cerr << label << ": ";
			Logger::_log(arg, args...);
			std::cerr << std::endl;
		}
	}
};

#endif