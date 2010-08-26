// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_EXTRADATABUMPMAPPING_HPP
#define _VGOPENCOLLADA_IMPORTER_EXTRADATABUMPMAPPING_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vector>
#include <COLLADASaxFWLIExtraDataCallbackHandler.h>

namespace vgOpenCOLLADA
{

namespace importer
{

/**
 * @brief Container class for Extra data information.
 */
struct BumpMappingInfo
{

    BumpMappingInfo () {}

    virtual ~BumpMappingInfo () {}

	/**
	 * @brief Get/set the id of the node which the extra depends.
	 */
    //const std::string getId () const { return mId; }
    //void setId ( const std::string val ) { mId = val; }

	/**
	 * @brief Get/set the texture id.
	 */
	const std::string& getTexture () const { return mTexture; }
	void setTexture( const std::string& val ) { mTexture = val; }
    void setTexture ( const GeneratedSaxParser::ParserChar* text, size_t textLength ) 
    { 
        mTexture.assign ( text, textLength ); 
    }


	/**
	 * @brief Get/set the texture channel.
	 */
	const std::string& getChannel () const { return mChannel; }
	void setChannel( const std::string& val ) { mChannel = val; }
    void setChannel ( const GeneratedSaxParser::ParserChar* text, size_t textLength ) 
    { 
        mChannel.assign ( text, textLength ); 
    }

private:
	std::string		mTexture;	///< The texture id.
    std::string		mChannel;	///< The channel of the texture.
};



/**
 * @brief	Implementation of an extra data callback handler with the callback handler interface
 *			to support bump mapping extra infos.
 * @see DAE2MAExtraDataCallbackHandler.h (from OpenCOLLADA)
 */
struct ExtraDataBumpMapping : public COLLADASaxFWL::IExtraDataCallbackHandler
{

	ExtraDataBumpMapping();

	virtual ~ExtraDataBumpMapping();

	/**
	 * @brief Returns the extra info with the searched id.
	 */
    std::vector<BumpMappingInfo> findExtraInfo ( const std::string id ) const;

	/**
	 * @brief Method to ask, if the current callback handler want to read the data of the given extra element.
	 */
    virtual bool parseElement ( 
        const GeneratedSaxParser::ParserChar* profileName, 
        const COLLADASaxFWL::StringHash& elementHash, 
        const COLLADAFW::UniqueId& uniqueId );

	/**
	 * @brief Methods to get the extra data tags to the registered callback handlers.
	 */
    virtual bool elementBegin( const GeneratedSaxParser::ParserChar* elementName, const GeneratedSaxParser::xmlChar** attributes);
    virtual bool elementEnd(const GeneratedSaxParser::ParserChar* elementName );
    virtual bool textData(const GeneratedSaxParser::ParserChar* text, size_t textLength);

private:

    /** Disable default copy ctor. */
	ExtraDataBumpMapping( const ExtraDataBumpMapping& pre );

    /** Disable default assignment operator. */
	const ExtraDataBumpMapping& operator= ( const ExtraDataBumpMapping& pre );

	typedef std::map<std::string, std::vector<BumpMappingInfo> > ExtraInfosMap;

    bool			m_isOriginalIdField;	///< True, if the current text field is the original id field.
	bool			m_currentId;			///< True, if the current text field is the dependent node name.

    BumpMappingInfo	m_currentExtraInfo;		///< Current extra data.

    ExtraInfosMap	m_extraInfos;			///< map of all extra data.
};


} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_EXTRADATABUMPMAPPING_HPP