// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/convenience.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>

#include <sbf/path.hpp>

#include <sstream>

#include <vgd/Shp.hpp>
#include <vgd/basic/Image.hpp>
#include <vgio/FilenameCollector.hpp>


namespace vgTest
{

void moveTo(std::string from, std::string to)
{
	if (boost::filesystem::exists(to))
	{
		boost::filesystem::remove(to);
	}
	boost::filesystem::rename(from, to);
}

int compare(std::string pathRef, std::string pathCap, std::string pathDif)
{
	using vgd::basic::Image;

	vgd::Shp< Image > capturedImage( new Image );
	vgd::Shp< Image > referenceImage( new Image );

	std::cout << "Loading captured image: " << pathCap << std::endl;
	capturedImage->load(pathCap);

	std::cout << "Loading reference image: " << pathRef << std::endl;
	referenceImage->load(pathRef);


	vgd::Shp< Image > differenceImage( new Image( pathCap ));

	assert(capturedImage->format() == Image::RGB && capturedImage->type() == Image::UINT8);

	uint8 *pref = (uint8*)referenceImage->pixels();
	float rref;
	float gref;
	float bref;

	uint8 *p = (uint8*)capturedImage->pixels();
	float r;
	float g;
	float b;

	uint8 *pdif = (uint8*)differenceImage->pixels();
	
	if(referenceImage->computeNumberOfPixels() != capturedImage->computeNumberOfPixels())
	{
		return false;
	}
	
	int identique = 0;
	int different = 0;

	for (uint i = 0; i < referenceImage->computeNumberOfPixels(); i++)
	{
		rref = pref[0];
		gref = pref[1];
		bref = pref[2];

		r = p[0];
		g = p[1];
		b = p[2];

		pdif[0] = static_cast<uint>( std::fabs(rref - r) );
		pdif[1] = static_cast<uint>( std::fabs(gref - g) );
		pdif[2] = static_cast<uint>( std::fabs(bref - b) );

		//pdif[0] = static_cast< uint8 >((rref - r) / 2.f + 127.5f);
		//pdif[1] = static_cast< uint8 >((gref - g) / 2.f + 127.5f);
		//pdif[2] = static_cast< uint8 >((bref - b) / 2.f + 127.5f);

		if(rref != r || gref != g || bref != b)
		{
			different++;
		}
		else
		{
			identique++;
		}

		pref += referenceImage->components();
		p += capturedImage->components();
		pdif += differenceImage->components();
	}
	
	if( boost::filesystem::exists( pathDif ) )
	{
		boost::filesystem::remove( pathDif );
	}
	if( different > 0 )
	{
		std::cout << "Creating differences image: " << pathDif << std::endl;
		differenceImage->save(pathDif);
	}
	
	return different;
}

std::string getImageName(std::string testName)
{
	boost::replace_all(testName, "/", "-");

	return testName + ".png";
}

std::string getDatedImageName(std::string filename)
{
	using namespace boost::posix_time;
	using namespace boost::gregorian;
	
	boost::replace_all(filename, "/", "-");
	boost::replace_all(filename, ".png", "");


	ptime now = second_clock::local_time();
	date d = now.date();
	filename += "_" + to_simple_string(now);

	boost::replace_all(filename, " ", "_");
	boost::replace_all(filename, ":", "");
	return filename + ".png";
}

std::string getNumberedImageName(std::string filename, int number)
{
	boost::replace_all(filename, "/", "-");
	boost::replace_all(filename, ".png", "");

	std::ostringstream out;
	out << number;

	std::string zero( (8 - out.str().size()), '0');

	return filename + "_" + zero + out.str() + ".png";
}

std::list< std::string > createModelList( bool collada )
{
	boost::filesystem::path path;

	if( collada )
	{
		path = sbf::path::getTopLevel(sbf::path::Share) / "vgTest" / "0-5" / "collada";
	}
	else
	{
		path = sbf::path::getTopLevel(sbf::path::Share) / "vgTest" / "0-5";
	}	

	vgio::FilenameCollector collector( path.string() );
	
	collector.setRegex(".*");
	collector.run();
	return collector.getStringFilenames();
}

} //namespace vgTest
