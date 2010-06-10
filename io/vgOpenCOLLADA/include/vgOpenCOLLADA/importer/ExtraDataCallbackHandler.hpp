// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_EXTRADATACALLBACKHANLDER_HPP
#define _VGOPENCOLLADA_IMPORTER_EXTRADATACALLBACKHANLDER_HPP


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
struct ExtraInfo
{

    ExtraInfo () {}

    virtual ~ExtraInfo () {}

	/**
	 * @brief Get/set the id of the node which the extra depends.
	 */
    const std::string getId () const { return mId; }
    void setId ( const std::string val ) { mId = val; }

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

    std::string		mId;		///< The unique Id of the currently parsed extra data element.
	std::string		mMatrix;	///< The text value of the current matrix.

};



/**
 * @brief Implementation of an extra data callback handler with the callback handler interface.
 * @see DAE2MAExtraDataCallbackHandler.h (from OpenCOLLADA)
 */
struct ExtraDataCallbackHandler : public COLLADASaxFWL::IExtraDataCallbackHandler
{

	ExtraDataCallbackHandler();

	virtual ~ExtraDataCallbackHandler();

	/**
	 * @brief Returns the extra info with the searched id.
	 */
    std::vector<ExtraInfo> findExtraInfo ( const std::string id ) const;

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
	ExtraDataCallbackHandler( const ExtraDataCallbackHandler& pre );

    /** Disable default assignment operator. */
	const ExtraDataCallbackHandler& operator= ( const ExtraDataCallbackHandler& pre );

	typedef std::map<std::string, std::vector<ExtraInfo> > ExtraInfosMap;

    bool			m_isOriginalIdField;	///< True, if the current text field is the original id field.
	bool			m_currentId;			///< True, if the current text field is the dependent node name.

    ExtraInfo		m_currentExtraInfo;		///< Current extra data.

    ExtraInfosMap	m_extraInfos;			///< map of all extra data.
};


} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_EXTRADATACALLBACKHANLDER_HPP