// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/Base.hpp"

#include <sbf/Module.hpp>
#include <sbf/path.hpp>
#include <vgTest/convenience.hpp>


namespace vgTest
{

Base::Base()
:	m_quit ( false ),
	m_filename( "test" ),
	m_fileCounter( 0 ),
	m_log( new Logging )
{
}

Base::Base(const std::string& filename)
:	m_quit ( false ),
	m_filename( filename ),
	m_fileCounter( 0 ),
	m_log( new Logging )
{
	m_datedFilename = vgTest::getDatedImageName(m_filename);
}

Base::~Base()
{
	m_log.reset();
}

void Base::setQuit(const bool b)
{
	m_quit = b;
}

vgd::Shp< vgTest::Logging > Base::getLog()
{
	return m_log;
}

const std::string Base::getReferencePath() const
{
	// @todo Replace the hard coded path
	boost::filesystem::path path = sbf::path::getTopLevel(sbf::path::Var) / "vgUI" / "0-5" / "references/";

	if (sbf::path::mkdirs(path.string()))
	{
		std::cout << "Reference path created" << std::endl;
	}

	return path.string();
}

const std::string Base::getScreenShotPath() const
{
	// @todo Replace the hard coded path

	boost::filesystem::path path = sbf::path::getTopLevel(sbf::path::Var) / "vgUI" / "0-5" / "screenshots/";
	return path.string();
}

const std::string Base::getDifferencePath() const
{
	// @todo Replace the hard coded path
	boost::filesystem::path path = sbf::path::getTopLevel(sbf::path::Var) / "vgUI" / "0-5" / "differences/";

	if (sbf::path::mkdirs(path.string()))
	{
		std::cout << "Differences path created" << std::endl;
	}

	return path.string();	
}

const std::string Base::getImagesPath(const bool diff) const
{
	std::string imagePath = "references="+getReferencePath() + ";" + m_filename;
	imagePath += "|screenshots="+getScreenShotPath() + ";" + m_datedFilename;

	if (diff)
	{
		imagePath += "|differences="+getDifferencePath() + ";" + m_datedFilename;
	}
	return imagePath;
}

const std::string	Base::getImagesPath(const std::list<int>& diff) const
{
	std::string references = "references="+getReferencePath() + ";";
	std::string screenshots = "|screenshots="+getScreenShotPath() + ";";
	std::string differences = "";
	for (int i = 0; i < m_fileCounter; i++)
	{
		references += vgTest::getNumberedImageName(m_filename, i) + ",";
		screenshots += vgTest::getNumberedImageName(m_datedFilename, i) + ",";
	}
	
	if(!diff.empty()) 
	{
		differences = "|differences="+getDifferencePath() + ";";

		std::list<int>::const_iterator it; 
		for(it=diff.begin();it!=diff.end();it++)
		{
			differences += vgTest::getNumberedImageName(m_datedFilename, *it) + ",";
		}
	}
	return references + screenshots + differences;
}

const std::string	Base::getScreenShotName() const
{
	return m_filename;
}

const std::string	Base::getDatedScreenShotName() const
{
	return m_datedFilename;
}

const std::string	Base::getCountedDatedScreenShotName()
{
	std::string filename =  vgTest::getNumberedImageName(m_datedFilename, m_fileCounter);
	++m_fileCounter;

	return filename;
}

const int Base::getFileCounter() const
{
	return m_fileCounter;
}

} // namespace vgTest