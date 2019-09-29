#ifndef __PLUGIN_HANDLE_H__
#define __PLUGIN_HANDLE_H__

#include <string>

class PluginHandle
{
public:
	PluginHandle(std::string pluginPath);

	~PluginHandle();

	bool isOpen();

	bool open();

	void close();

	std::string lastError();

private:
	void *pluginHandle;

	std::string pluginPath;

	std::string errorMsg;
};

#endif