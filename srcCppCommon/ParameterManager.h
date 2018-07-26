#ifndef __PARAMETERMANAGER_H__
#define __PARAMETERMANAGER_H__

/*
 * (c) 2005-2018  Copyright, Real-Time Innovations, Inc. All rights reserved.
 * Subject to Eclipse Public License v1.0; see LICENSE.md for details.
 */
#include "PerftestTransport.h"
#include "RTIDDSImpl.h"
#include "Parameter.h"
#include <map>

#if defined(RTI_WIN32)
  #pragma warning(push)
  #pragma warning(disable : 4996)
  #define STRNCASECMP _strnicmp
#elif defined(RTI_VXWORKS)
  #define STRNCASECMP strncmp
#else
  #define STRNCASECMP strncasecmp
#endif
#define IS_OPTION(str, option) (STRNCASECMP(str, option, strlen(str)) == 0)

class ParameterManager
{
    private:
        std::map<std::string, AnyParameter> _parameterList;

    public:
        ParameterManager();
        void initialize();
        static ParameterManager& GetInstance();
        ~ParameterManager();

        // Set the value of a parameter
        template <typename T>
        void set(std::string parameterKey, T var)
        {
            std::map<std::string, AnyParameter>::iterator it =
                    _parameterList.find(parameterKey);
            if (it != _parameterList.end()) {
                (static_cast<Parameter<T>*>(it->second.get<T>()))->set_value(var);
            }
        }

        // Get the value of a parameter
        template <typename T>
        T get(std::string parameterKey)
        {
            std::map<std::string, AnyParameter>::iterator it =
                    _parameterList.find(parameterKey);
            if (it != _parameterList.end()) {
                return (static_cast<Parameter<T>*>(it->second.get<T>()))->get_value();
            } else {
                return T(); // Return the default
                // TODO throw exception
            }
        }

        // Get a vector with the values of a parameter
        template <typename T>
        std::vector<T> get_vector(std::string parameterKey)
        {
            std::map<std::string, AnyParameter>::iterator it =
                    _parameterList.find(parameterKey);
            if (it != _parameterList.end()) {
                return (static_cast<ParameterVector<T>*>(it->second.get_vector<T>()))->get_value();
            } else {
                return std::vector<T>(); // Return the default
                // TODO throw exception
            }
        }

        // Get a vector with the values of a parameter
        template <typename K, typename V>
        std::pair<K,V> get_pair(std::string parameterKey)
        {
            std::map<std::string, AnyParameter>::iterator it =
                    _parameterList.find(parameterKey);
            if (it != _parameterList.end()) {
                return (static_cast<ParameterPair<K,V>*>(it->second.get_pair<K,V>()))->get_value();
            } else {
                return std::pair<K,V>(); // Return the default
                // TODO throw exception
            }
        }

        // Parse the command line parameters and set the values
        bool parse(int argc, char *argv[]);

        // Get the help message
        std::string display_help();

        // check -help option
        bool check_help(int argc, char *argv[]);

        // check if a variable has been set
        bool is_set(std::string parameterKey);

        /*
         * Validate:
         *     That if -pub not use parameter of SUB group
         *     That if -sub not use parameter of PUB group
         */
        bool validate_group();

        // Verify if there is a parameter of the group set
        bool group_is_use(GROUP group);


    private:
        std::vector<std::string> split(std::string str, std::string delimiter = ":");
        std::string get_center_header_help_line(std::string name);

};

typedef ParameterManager PM;

#endif // __PARAMETERMANAGER_H__