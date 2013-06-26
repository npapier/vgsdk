// VGSDK - Copyright (C) 2009, 2010, 2012, 2013, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgTest/Base.hpp"

#include <boost/filesystem/operations.hpp>
#include <gtest/gtest.h>
#include "vgTest/convenience.hpp"
#include "vgTest/Logging.hpp"



namespace vgTest
{


Base::Base(const std::string filename, const boost::shared_ptr< sbf::pkg::Module > module )
:	m_quit ( false ),
	m_filename( filename ),
	m_datedFilename( vgTest::getDatedImageName( filename ) ),
	m_fileCounter( -1 ),
	m_screenshotFrequency ( 1 ),
	m_log( new Logging ),
	m_module( module )
{}


Base::~Base()
{
	m_log.reset();
}


void Base::setQuit( const bool b )
{
	m_quit = b;
}


vgd::Shp< vgTest::Logging > Base::getLog()
{
	return m_log;
}


const boost::filesystem::path Base::getReferencePath() const
{
	namespace bfs = boost::filesystem;
	const bfs::path path = m_module->getPath(sbf::pkg::VarPath) / "references";

	return path;
}


const boost::filesystem::path Base::getScreenShotPath() const
{
	namespace bfs = boost::filesystem;
	const bfs::path path = m_module->getPath(sbf::pkg::VarPath) / "screenshots";

	return path;
}


const boost::filesystem::path Base::getDifferencePath() const
{
	namespace bfs = boost::filesystem;
	const bfs::path path = m_module->getPath(sbf::pkg::VarPath) / "differences";

	return path;
}


const std::string Base::getImagesPath(const bool diff) const
{
	std::string imagePath = "references="+getReferencePath().string() + ";" + m_filename;
	imagePath += "|screenshots="+getScreenShotPath().string() + ";" + m_datedFilename;

	if (diff)
	{
		imagePath += "|differences="+getDifferencePath().string() + ";" + m_datedFilename;
	}
	return imagePath;
}

const std::string Base::getImagesPath(const std::list<int>& diff) const
{
	std::string references = "references="+getReferencePath().string() + ";";
	std::string screenshots = "|screenshots="+getScreenShotPath().string() + ";";
	std::string differences = "";
	for (int i = 0; i <= m_fileCounter; i++)
	{
		references += vgTest::getNumberedImageName(m_filename, i) + ",";
		screenshots += vgTest::getNumberedImageName(m_datedFilename, i) + ",";
	}
	
	if(!diff.empty()) 
	{
		differences = "|differences="+getDifferencePath().string() + ";";

		std::list<int>::const_iterator it; 
		for(it=diff.begin();it!=diff.end();it++)
		{
			differences += vgTest::getNumberedImageName(m_datedFilename, *it) + ",";
		}
	}
	return references + screenshots + differences;
}

const std::string Base::getScreenShotName() const
{
	return m_filename;
}

const std::string	Base::getDatedScreenShotName() const
{
	return m_datedFilename;
}

const std::string Base::getCountedDatedScreenShotName(const bool n)
{
	if (n || m_fileCounter < 0)
	{
		++m_fileCounter;
	}
	const std::string filename = vgTest::getNumberedImageName(m_datedFilename, m_fileCounter);

	return filename;
}

const std::string Base::getCountedScreenShotName(const bool n)
{
	if (n || m_fileCounter < 0)
	{
		++m_fileCounter;
	}
	const std::string filename = vgTest::getNumberedImageName(getScreenShotName(), m_fileCounter);

	return filename;
}


const int Base::getFileCounter() const
{
	return m_fileCounter;
}


const int Base::getScreenshotFrenquency() const
{
	return m_screenshotFrequency;
}

void Base::setScreenshotFrequency(int f)
{
	if ( f < 1 )
	{
		FAIL() << "FREQUENCY MUST BE POSITIVE";
		return;
	}
	m_screenshotFrequency = f;
}


void Base::compareScreenShots() const
{
	std::list<int> differences;
	for (int i = 0; i <= m_fileCounter; i++)
	{
		namespace bfs=boost::filesystem;
		const bfs::path referencePathfilename( getReferencePath() / vgTest::getNumberedImageName(getScreenShotName(), i) );
		if (!boost::filesystem::exists(referencePathfilename) )
		{
			FAIL() << "REFERENCES FILES : " + referencePathfilename.string() + " IS NOT CREATED";
		}

		SCOPED_TRACE("Screenshot : " + vgTest::getNumberedImageName(getDatedScreenShotName(), i) + " Reference : " +  vgTest::getNumberedImageName(getScreenShotName(), i)); 

		const bfs::path screenshotPathfilename( getScreenShotPath() / vgTest::getNumberedImageName(getDatedScreenShotName(), i) );
		const bfs::path differencePathfilename( getDifferencePath() / vgTest::getNumberedImageName(getDatedScreenShotName(), i) );
		const int diff = vgTest::compare(	referencePathfilename.string(),
											screenshotPathfilename.string(),
											differencePathfilename.string() );

		EXPECT_EQ( diff, 0 );

		if( diff != 0)
		{
			differences.push_back(i);
		}
	}

	m_log->add("ImagePath", getImagesPath(differences));
}



} // namespace vgTest
