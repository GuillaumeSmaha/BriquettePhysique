/*!
 *  \file  Utils.h
 * \brief Utilities file
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <math.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>
#endif

///Approximation du chiffre PI
#define PI Ogre::Math::PI

/*!
 * \class Utils
 * \brief A tools class
 */
class Utils
{
	private:
		/*!
		 * \brief Initialize the rand function
		 */
		static int initialize();

		/*!
		 * \brief Value of a unique counter
		 */
		static int _count;

		/*!
		 * \brief Path of the log file
		 */
		static Ogre::String _logFile;
		
	public:
		/*!
		* \brief Returns an int between min and max (inclusive)
		* \param min lower bound
		* \param max upper bound
		* \return An int between min and max (inclusive)
		*/
		static int randRangeInt(int min, int max);

		/*!
		 * \brief Returns an unique int
		 * \return unique int
		 */
		static int unique();

		/*!
		* \brief Show a log message on the console
		* \param text Text to show
		*/
		static void log(const Ogre::String &text);
		/*!
		* \brief Show a log message on the console (generic)
		* \param value Value to show
		*/
		template <typename T>
        static Ogre::String log( const T & value )
        {
            return Utils::toString<T>(value);
        }
		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte à afficher
		*/
		static void log(int text)
		{
		    Utils::log(Utils::toString(text));
		}
		/*!
		* \brief Show a number on the console
		* \param text Number to show
		*/
        static void log(float text)
		{
		    Utils::log(Utils::toString(text));
		}		
		/*!
		* \brief Show a log message on the console
		* \param text Texte à afficher
		*/
		static void log(const char * text)
		{
			Utils::log(Ogre::String(text));
		}

		/*!
		* \brief Init the path of the log file
		* \param file Path of the log file
		*/
		static void logFileInit(const Ogre::String &file);
		/*!
		* \brief Save a log message ine the file
		* \param text Text to show
		*/
		static void logFile(const Ogre::String &text);
        /*!
		* \brief Save a log message ine the file(generic)
		* \param value Value to show
		*/
        template <typename T>
        static void logFile( const T & value )
        {
            Utils::logFile(Utils::toString<T>(value));
        }
		/*!
		* \brief Transform a value in a string(generic)
		* \param value Value to transform
		*/
		template <typename T>
		static Ogre::String toString( const T & value )
        {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
		/*!
		* \brief Transform a number in a string
		* \param value Number to transform
		*/
        static Ogre::String toString( float value );
		/*!
		* \brief Transform a Number in a string
		* \param value Number to transform
		*/
		static Ogre::String toString( int value );

        /*!
		* \brief Returns the content of a file in a string 
		* \param path Path of the file
		*/
        static Ogre::String readFile(const Ogre::String &path)
        {
			return Utils::readFile(path.c_str());
		}
        /*!
		* \brief Returns the content of a file in a string
		* \param path Path of the file
		* \return Content of the file
		*/
        static Ogre::String readFile(const char * path)
        {
			return Utils::readFile((char *)path);
		}
        /*!
		* \brief Returns the content of 
		* \return Content of the filea file in a string
		* \param path Path of the file
		*/
        static Ogre::String readFile(char * path);

        /*!
		* \brief Returns the full path of a file contained in the resources of a defined group
		* \param groupName Groupname
		* \param filename Filename
		* \return Full path of the file
		*/
		static Ogre::String getFullPathRessources(const Ogre::String &groupName, const Ogre::String &filename);
        /*!
		* \brief Returns the full path of a file contained in the resources of any group
		* \param filename Filename
		* \return Full path of the file
		*/
		static Ogre::String getFullPathRessources(const Ogre::String &filename);
        /*!
		* \brief Returns the full path of a sound file (depend to the "soundDir.here" file)
		* \param filename Sound filename
		* \return Full path of the sound file
		*/
		static Ogre::String getFullPathSound(const Ogre::String &filename);
		
		/*!
		* \brief Returns the range between two points
		* \param A First point
		* \param B Second point
		* \return The range
		*/
		static Ogre::Real distance(const Ogre::Vector3 &A, const Ogre::Vector3 &B);
		
		/*!
		* \brief Returns the angle between [point;futurePoint] and [point;object]
		* \param point Position of the point
		* \param futurePoint Future position of the point
		* \param object Position of the object
		* \return Angle [0.0, 0.4[ left; [O.4, 0.6] center; ]0.6, 1.0] right;
		*/
		static Ogre::Real getAngle(const Ogre::Vector3 &point, const Ogre::Vector3 &futurePoint, const Ogre::Vector3 &object);
};


#endif // __UTILS_H__
