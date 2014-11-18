// VGSDK - Copyright (C) 2007, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker, Nicolas Papier

#ifndef _VGD_BASIC_WINDOWING_HXX
#define _VGD_BASIC_WINDOWING_HXX

#include <vgd/basic/Image.hpp>
#include <vgm/operations.hpp>



namespace vgd
{

namespace basic
{



template< typename InputType >
vgd::Shp< vgd::basic::IImage > Windowing::doApply( const vgd::Shp< vgd::basic::IImage > input ) const
{
#ifdef __STBIMAGE__
	#pragma message("Windowing::doApply(): not yet implemented")
	assert(false);
	Shp< vgd::basic::IImage > image;
	return image;
#else
	using vgd::basic::Image;
	
	assert( m_min <= m_max );
	assert( input->format() == Image::LUMINANCE || input->format() == Image::LUMINANCE_ALPHA );
	
	typedef uint8 OutputType;
	
	const Image::Type	outputType		= Image::UINT8;
	const Image::Format	outputFormat	= Image::LUMINANCE_ALPHA;
	
	const float windowMin = static_cast< float >( m_min );
	const float windowMax = static_cast< float >( m_max );
	float		a;
	float		b;
	
	if( windowMin != windowMax )
	{
		vgm::linearInterpolation( windowMin, m_minOutput, windowMax, m_maxOutput, a, b );
	}
	
	vgd::Shp< Image >	output( new Image(input->width(), input->height(), input->depth(), outputFormat, outputType) );
	OutputType			* iOutput			= static_cast< OutputType * >( output->editPixels() );
	const uint32		outputComponents	= output->components(); 
	
	const uint32	inputComponents = input->components();
	const InputType	* iInput	= static_cast< const InputType * >( input->pixels() );
	const InputType	* iInputEnd	= iInput + input->computeNumberOfPixels() * inputComponents;			
	
	for( ; iInput != iInputEnd; iInput += inputComponents, iOutput += outputComponents )
	{
		const float	currentIntensity = static_cast< float >(*iInput);

		if( currentIntensity < windowMin )
		{
			iOutput[0] = m_lowOutput;
			iOutput[1] = m_lowAlpha;
		}
		else if( currentIntensity > windowMax )
		{
			iOutput[0] = m_highOutput;
			iOutput[1] = m_highAlpha;
		}
		else if( currentIntensity == windowMin && currentIntensity == windowMax )
		{
			iOutput[0] = m_highOutput;
			iOutput[1] = m_minMaxAlpha;
		}
		else
		{
			const float value			= vgm::linearInterpolation( a, b, currentIntensity );
			const float valueClamped	= vgm::clamp( value, 0.f, 255.f );
		
			iOutput[0] = static_cast< OutputType >( valueClamped );
			iOutput[1] = m_minMaxAlpha;
		}
	}
	
	output->editPixelsDone();			
	return output;
#endif
}



} // namespace basic

} // namespace vgd



#endif // #ifndef _VGD_BASIC_WINDOWING_HXX
