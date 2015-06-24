//
//  ini.h
//  iniParser
//
//  Created by Mickael Bonfill on 23/06/2015.
//
//

#ifndef iniParser_ini_h
#define iniParser_ini_h

#include <map>
#include <string>
#include <fstream>

class IniParser
{
private:
    std::map<std::string, std::map<std::string, std::string>> m_iniMap;
public:
    
    enum ERR : unsigned int
    {
        DUMMY,
        NO_READ_ACESS,
        NO_WRITE_ACESS
    };
    
    /*
     * Get value of a specific key, located in specific section.
     */
    std::string get(const std::string& section, const std::string& key, const std::string& defaultValue)
    {
        for (auto it0 = m_iniMap.begin(); it0 != m_iniMap.end(); it0++)
        {
            if (section == it0->first)
            {
                for (auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
                {
                    if (key == it1->first)
                    {
                        return it1->second;
                    }
                }
            }
        }
        return defaultValue;
    }
    
    /*
     * Read the ini file, and populate the private map variable.
     */
    int read(const std::string& filePath)
    {
        const char * path = filePath.c_str();
        std::ifstream file;
        file.open(path);
        
        if (!file.is_open() || file.fail())
        {
            std::cout << "File not found : " << path << std::endl;
            return ERR::NO_READ_ACESS;
        }
        else
        {
            m_iniMap.clear();
            
            while(!file.eof())
            {
                std::string sectionName;
                for(std::string line; std::getline(file, line); )
                {
                    line.erase(line.end()-1);
                    
                    if (line.find("[") == 0) {
                        std::map<std::string, std::string> sectionMap;
                        sectionName = line.substr(line.find("[")+1, line.find("]")-1);
                        m_iniMap[sectionName] = sectionMap;
                    }
                    else
                    {
                        if (line.size() > 0)
                        {
                            std::string entryName = line.substr(0,line.find("="));
                            std::string value = line.substr(line.find("=")+1, line.size());
                            m_iniMap[sectionName][entryName] = value;
                        }
                        
                    }
                    
                }
                
            }
            file.close();
            return 0;
        }
    };
    
    
    /*
     * Write the ini file entirely, based on a specific map
     */
    int write(const std::string& filePath, std::map<std::string, std::map<std::string, std::string>> map)
    {
        const char* path = filePath.c_str();
        std::ofstream file;
        file.open(path);
        if (file.fail() || !file.is_open())
        {
            std::cout << "can't write file : " << path << std::endl;
            return ERR::NO_WRITE_ACESS;
        }
        for (auto it0 = map.begin(); it0 != map.end(); it0++)
        {
            file << "[" << it0->first << "]" << std::endl;
            
            std::map<std::string, std::string> sectionMap = it0->second;
            
            for (auto it1 = sectionMap.begin(); it1 != sectionMap.end(); it1++)
            {
                file << it1->first << "=" << it1->second << std::endl;
            }
        }
        file.close();
        return 0;
    };
    
    /*
     * Get the map variable containing structured version of the ini file
     */
    std::map<std::string, std::map<std::string, std::string>> getMap()
    {
        return m_iniMap;
    };
};

#endif // iniParser_ini_h
