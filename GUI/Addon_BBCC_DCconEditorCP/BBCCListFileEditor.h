#pragma once
#include "FileListReader.h"
#include "BBCCListFileReader.h"
#include "EngineHeader.h"

//둘다 상속!
class BBCCListFileEditor : FileListReader, BBCCListFileReader
{


	private :
		std::string ConvertToUTF8(std::string input);
		std::string ConvertInputManager(std::string input);
};

