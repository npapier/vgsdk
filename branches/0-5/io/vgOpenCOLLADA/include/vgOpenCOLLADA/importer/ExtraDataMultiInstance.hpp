// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_EXTRADATAMULTIINSTANCE_HPP
#define _VGOPENCOLLADA_IMPORTER_EXTRADATAMULTIINSTANCE_HPP


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
struct MultiInstanceInfo
{

    MultiInstanceInfo () {}

    virtual ~MultiInstanceInfo () {}

	/**
	 * @brief Get/set the uniqueId of the node which the extra depends.
	 */
    const COLLADAFW::UniqueId getUniqueId () const { return mUniqueId; }
    void setUniqueId ( const COLLADAFW::UniqueId val ) { mUniqueId = val; }

	/**
	 * @brief Get/set the matrix for Multiple Instances.
	 */
	const std::string& getMatrix () const { return mMatrix; }
	void setMatrix( const std::string& val ) { mMatrix = val; }
    void setMatrix ( const GeneratedSaxParser::ParserChar* text, size_t textLength ) 
    { 
        mMatrix.assign ( text, textLength ); 
    }


private:

	COLLADAFW::UniqueId	mUniqueId;	///< The unique Id of the currently parsed extra data element.
	std::string			mMatrix;	///< The text value of the current matrix.

};



/**
 * @brief	Implementation of an extra data callback handler with the callback handler interface
 *			to support multiple instance.
 * @see DAE2MAExtraDataCallbackHandler.h (from OpenCOLLADA)
 */
struct ExtraDataMultiInstance : public COLLADASaxFWL::IExtraDataCallbackHandler
{

	ExtraDataMultiInstance();

	virtual ~ExtraDataMultiInstance();

	/**
	 * @brief Returns the extra info with the searched id.
	 */
    std::vector<MultiInstanceInfo> findExtraInfo ( const COLLADAFW::UniqueId uniqueId ) const;

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
	ExtraDataMultiInstance( const ExtraDataMultiInstance& pre );

    /** Disable default assignment operator. */
	const ExtraDataMultiInstance& operator= ( const ExtraDataMultiInstance& pre );

	typedef std::map<COLLADAFW::UniqueId, std::vector<MultiInstanceInfo> > ExtraInfosMap;

    bool				m_isOriginalIdField;	///< True, if the current text field is the original id field.

    MultiInstanceInfo	m_currentExtraInfo;		///< Current extra data.

    ExtraInfosMap		m_extraInfos;			///< map of all extra data.
};


} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_EXTRADATAMULTIINSTANCE_HPP