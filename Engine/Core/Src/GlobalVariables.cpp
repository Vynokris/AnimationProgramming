#include "stdafx.h"
#include "GlobalVariables.h"

#include "FileSystem.h"

#include "Render/Renderer.h"
#include "System/OperatingSystem.h"
#include "ResourceManager.h"
#include "Application.h"
#include "LogSystem/LogSystem.h"

#include "BehaviorManager.h"

WHITEBOX_BEGIN

SGlobalVariables* gVars = NULL;

void SGlobalVariables::Init()
{
	gVars = new SGlobalVariables();

	gVars->pFileSystem = new CFileSystem();
	gVars->pLogSystem = new CLogSystem();
	
	gVars->pRenderer = new CRenderer();
	gVars->pOperatingSystem = new COperatingSystem();
	gVars->pApplication = new CApplication();
	gVars->pResourceManager = new CResourceManager();
	
	gVars->pBehaviorManager = new CBehaviorManager();
};


WHITEBOX_END

