// VGSDK - Copyright (C) 2007, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker, Nicolas Papier

#ifndef _VGD_BASIC_WINDOWING_HPP
#define _VGD_BASIC_WINDOWING_HPP

#include "vgd/basic/ITransferFunction.hpp"



namespace vgd
{
	
namespace basic
{
	
	
	
/**
 * @brief	Implements a windowing transfer function.
 * 
 * @todo	Add some explanations about the job that is done it this function.
 * 
 * @author	Guillaume Brocker
 */
struct Windowing : public ITransferFunction
{
	/**
	 * @brief	Constructor
	 * 
	 * @param	min	the lowest intensity to show (0 by default)
	 * @param	max	the highest intensity to show (255 by default)
	 */
	Windowing( const int min = 0, const int max = 255 );
	
	/**
	 * @brief	Updates the output alpha.
	 * 
	 * @param	low		the alpha for inputs below the window lower bound
	 * @param	minMax	the alpha for inputs in the window
	 * @param	high		the alpha for inputs above the upper window bound
	 */
	void setOutputAlpha( const uint8 low, const uint8 minMax, const uint8 high );
	
	/**
	 * @brief	Updates the output intensities.
	 * 
	 * @param	low		the output intensity for inputs below the window lower bound
	 * @param	min		the output intensity for inputs at the lower window bound
	 * @param	max		the output intensity for inputs at the upper window bound
	 * @param	high		the output intensity for inputs above the upper window bound
	 */
	void setOutputIntensities( const uint8 low, const uint8 min, const uint8 max, const uint8 high );
	
	/**
	 * @brief	Updates the position of the window.
	 * 
	 * @param	min	the low window bound
	 * @param	max	the up window bound
	 * 
	 * @pre	min < max
	 */
	void setWindow( const int min, const int max );
	
	/**
	 * @name	Overrides
	 */
	//@{
	vgd::Shp< vgd::basic::IImage > apply( const vgd::Shp< vgd::basic::IImage > image ) const;
	//@}
	
private:

	int		m_min;			///< Defines the lower bound of the window.
	int		m_max;			///< Defines the upper bound of the window.
	
	uint8	m_lowOutput;	///< Defines the output intensity for inputs that are below the min window bound.
	uint8	m_lowAlpha;		///< Defines the output alpha for inputs that are below the min window bound.
	
	uint8	m_minOutput;	///< Defines the output intensity at the min window bound.
	uint8	m_maxOutput;	///< Defines the output intensity at the max window bound.
	uint8	m_minMaxAlpha;	///< Defines the output alpha for inputs that are in the window.
	
	uint8	m_highOutput;	///< Defines the output intensity for inputs that are above the max window bound.  
	uint8	m_highAlpha;	///< Defines the output alpha for inputs that are above the max window bound.
	
	/**
	 * @brief	Invoked by apply, it performs the windowing treatement.
	 * 
	 * @see		apply
	 */
	template< typename InputType >
	vgd::Shp< vgd::basic::IImage > doApply( const vgd::Shp< vgd::basic::IImage > input ) const;

};
	


} // namespace basic

} // namespace vgd



#include "vgd/basic/Windowing.hxx"



#endif // #ifndef _VGD_BASIC_WINDOWING_HPP
