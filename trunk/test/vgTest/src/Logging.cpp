// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/Logging.hpp"

#include <gtest/gtest.h>
#include <sstream>


namespace vgTest
{

Logging::Logging()
{
}

void Logging::add(std::string key, std::string value)
{
	m_log[key] = value;
}

const std::string Logging::get(std::string key)
{
	return m_log[key];
}

std::map<std::string, std::string> Logging::getLog() const
{
	return m_log;
}

void Logging::remove(std::string key)
{
	m_log.erase(key);
}

void Logging::addToGtest()
{
	for( std::map<std::string, std::string>::iterator ii=m_log.begin(); ii!=m_log.end(); ++ii)
	{
		::testing::Test::RecordProperty((*ii).first.c_str(), (*ii).second.c_str());
	}	
}

}

