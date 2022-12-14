#include "stdafx.h"
#include "LogSystem/LogSystem.h"
#include "Render/Renderer.h"
#include "GlobalVariables.h"

#ifdef __GEAR_VR
#include <android/log.h>
#endif
#include <stdarg.h>

using namespace WhiteBox;

extern "C"
{
	void WbLog( const char* channel, const char* format, ... )
	{
		va_list arglist;
		va_start(arglist, format);
		va_list args2;
		va_copy(args2, arglist);
		int size = 1 + vsnprintf(nullptr, 0, format, arglist);
		char* message = new char[size];
		va_end(arglist);
#if defined(_WIN32) || defined(_WIN64)
		vsprintf_s(message, size, format, args2);
#else
		vsprintf(message, format, args2);
#endif
		va_end(args2);
		gVars->pLogSystem->Log( channel, message  );
		delete[] message;
	}
}

WHITEBOX_BEGIN

class CConsoleLogger : public ILogger
{
	virtual void	Log( const char* message ) override
	{
#ifdef __GEAR_VR
		__android_log_print( ANDROID_LOG_ERROR, "WhiteBox", message, 0 );
#else
		fwrite( message, sizeof(char), strlen(message), stdout );
#endif
	}
};


CLogSystem::CLogSystem()
{
	m_loggers.push_back( new CConsoleLogger ); 
}

CLogSystem::~CLogSystem()
{
	for( ILogger* pLogger : m_loggers )
	{
		delete pLogger;
	}
}

void	CLogSystem::Log( const char* channel, const char* message )
{
	String formatMessage = String(channel) + " : " + String(message) + "\n";
	for( ILogger* pLogger : m_loggers )
	{
		pLogger->Log( formatMessage.c_str() );
	}
}

WHITEBOX_END
