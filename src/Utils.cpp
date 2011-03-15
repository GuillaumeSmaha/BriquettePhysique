#include "Utils.h"

int Utils::_count = 0;
Ogre::String Utils::_logFile = "";

int Utils::initialize(void)
{
	srand(time(NULL));
	return 0;
}

int Utils::randRangeInt(int min, int max)
{
    static bool init = false;
    if(init == false)
    {
        init = true;
        Utils::initialize();
    }
	return (int)((double)rand() / ((double)RAND_MAX + 1) * (max-min+1)+min);
}

int Utils::unique(void)
{
	return _count++;
}

void Utils::log(const Ogre::String &text)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(text);
}

void Utils::logFileInit(const Ogre::String &file)
{
	if(file.compare("") != 0)
	{
		std::ofstream fileLog(file.c_str());
		if (fileLog.is_open())
		{
			Utils::_logFile.assign(file);

			fileLog.close();
			std::remove((file.c_str()));
		}
		else
		{
			Ogre::String text = "L'ouverture du fichier de sortie de log a échoué : ";
			text.append(file);
			Ogre::LogManager::getSingletonPtr()->logMessage(text);
		}
	}
	else
	{
		Ogre::String text = "Le fichier de sortie de log est invalide : ";
		text.append(file);
		Ogre::LogManager::getSingletonPtr()->logMessage(text);
	}
}

void Utils::logFile(const Ogre::String &text)
{
	if(Utils::_logFile.compare("") != 0)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char bufferTime[15];
		std::ofstream fileLog(Utils::_logFile.c_str(), std::ios_base::app);

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime(bufferTime, 80, "%X: ", timeinfo);

		fileLog << bufferTime << text << "\n";

		fileLog.close();
	}
}

Ogre::String Utils::toString( float value )
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

Ogre::String Utils::toString( int value )
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

Ogre::String Utils::readFile(char * path)
{
    Ogre::String res;
    std::ifstream fichier(path, std::ios::in);
    if(fichier)
    {
        std::string ligne;
        while(getline(fichier, ligne))
        {
                res = res+(ligne+"\n");
        }
            fichier.close();
            return res;
    }
    else
        return NULL;
}


Ogre::String Utils::getFullPathRessources(const Ogre::String &groupName, const Ogre::String &filename)
{
	Ogre::FileInfoListPtr listPtr = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(groupName, filename);
	if(listPtr->size() != 1)
		return "";

	Ogre::String output = listPtr->at(0).archive->getName();
	output.append("/");
	output.append(filename);

	return output;
}


Ogre::String Utils::getFullPathRessources(const Ogre::String &filename)
{
	Ogre::String group = Ogre::ResourceGroupManager::getSingleton().findGroupContainingResource(filename);

	Ogre::FileInfoListPtr listPtr = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(group, filename);
	if(listPtr->size() != 1)
		return "";

	Ogre::String output = listPtr->at(0).archive->getName();
	output.append("/");
	output.append(filename);

	return output;
}

Ogre::String Utils::getFullPathSound(const Ogre::String &filename)
{
	Ogre::String fileSoundDir = "soundDir.here";
	Ogre::String group = Ogre::ResourceGroupManager::getSingleton().findGroupContainingResource(fileSoundDir);

	Ogre::FileInfoListPtr listPtr = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(group, fileSoundDir);
	if(listPtr->size() != 1)
		return "";

	Ogre::String output = listPtr->at(0).archive->getName();
	output.append("/sound/");
	output.append(filename);

	return output;
}

Ogre::Real Utils::distance(const Ogre::Vector3 &A, const Ogre::Vector3 &B)
{
	return sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1])+(A[2]-B[2])*(A[2]-B[2]));
}

Ogre::Real Utils::getAngle(const Ogre::Vector3 &point, const Ogre::Vector3 &futurePoint, const Ogre::Vector3 &object)
{
	Ogre::Real a = Utils::distance(futurePoint, object);
	Ogre::Real b = Utils::distance(point, object);
	Ogre::Real c = Utils::distance(point, futurePoint);
	return Ogre::Math::ACos((a*a+b*b-c*c)/(2*a*b)).valueDegrees()/(360.0);
}
