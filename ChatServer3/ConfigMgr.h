#pragma once
#include "const.h"
struct SectionInfo
{
	SectionInfo() {};
	SectionInfo(const SectionInfo& other)
	{
		m_section_datas = other.m_section_datas;
	}
	SectionInfo& operator=(const SectionInfo& other)
	{
		if (&other == this)
		{
			return *this;
		}
		this->m_section_datas = other.m_section_datas;
		return *this;
	}
	~SectionInfo() {
		m_section_datas.clear();
	};
	std::map<std::string, std::string> m_section_datas;
	std::string GetValue(const std::string& key)
	{
		if (m_section_datas.find(key) == m_section_datas.end()) {
			return "";
		}
		// 这里可以添加一些边界检查  
		return m_section_datas[key];
	}
	std::string operator[](const std::string& key)
	{
		if (m_section_datas.find(key) == m_section_datas.end())
		{
			return "";
		}
		return m_section_datas[key];
	}
};
class ConfigMgr {
public:
	~ConfigMgr()
	{
		m_config_map.clear();
	}
	SectionInfo operator[](const std::string& section)
	{
		if (m_config_map.find(section) == m_config_map.end())
		{
			return SectionInfo();
		}
		return m_config_map[section];
	}

	
	ConfigMgr(const ConfigMgr& other)
	{
		m_config_map = other.m_config_map;
	}
	ConfigMgr & operator=(const ConfigMgr& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_config_map = other.m_config_map;
		return *this;
	}
	static ConfigMgr& Inst()
	{
		static ConfigMgr cfg_mgr;
		return cfg_mgr;
	}
	std::string GetValue(const std::string & section, const std::string &key);
private:
	ConfigMgr();
	std::map<std::string, SectionInfo> m_config_map;
};