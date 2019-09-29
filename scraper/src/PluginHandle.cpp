#include "PluginHandle.hpp"
#include <dlfcn.h>

PluginHandle::PluginHandle(std::string pluginPath)
{
	this->pluginPath = pluginPath;

	this->errorMsg = "";

	this->pluginHandle = NULL;
}

PluginHandle::~PluginHandle()
{
	this->close();
}

bool PluginHandle::isOpen()
{
	return this->pluginHandle != NULL;
}

bool PluginHandle::open()
{
	this->pluginHandle = dlopen(this->pluginPath.c_str(), RTLD_LAZY);
	
	if (!this->isOpen()) {
		// store a copy of the error message in case program wants to check it
		this->errorMsg = std::string(dlerror());
		return false;
	}

	return true;
}

std::string PluginHandle::lastError()
{
	return this->errorMsg;
}

void PluginHandle::close()
{
	if (this->isOpen()) {
		dlclose(this->pluginHandle);
		this->pluginHandle = NULL;
	}
}