// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: colorTable.h,v 1.14 2005/07/16 21:00:32 oliver Exp $
//

#ifndef BALL_VIEW_DATATYPE_COLORTABLE_H
#define BALL_VIEW_DATATYPE_COLORTABLE_H

#ifndef BALL_VIEW_DATATYPE_COLORRGBA_H
#	include <BALL/VIEW/DATATYPE/colorRGBA.h>
#endif

#include <vector>

namespace BALL 
{
	namespace VIEW 
	{
		/** This class is used to implement a color table that can be used to
		 *  map a floating point value into a color.
		\ingroup ViewDatatypeFormat
		*/
		class BALL_EXPORT ColorTable
			: public vector<ColorRGBA>
		{
			public:

			BALL_CREATE(ColorTable)

			/**	@name	Constructors and Destructors 
			*/	
			//@{

			/**	Default constructor.
					Create an empty instance of ColorTable.
			*/
			ColorTable()
				throw();

			/** Alternative constructor.
			 *  Create an instance of ColorTable.
			 *  \param color_number The number of colors the table will contain.
			 */
			ColorTable(Size color_number)
				throw();
			
			/**	Copy constructor.
					Create a copy of a ColorTable object.
					\param	color_table the color table to be copied
			*/
			ColorTable(const ColorTable& color_table)
				throw();

			/** Detailed constructor.
			 * 	\param size the number of elements in the color table
			 * 	\param color an array of colors, used to initialize the table
			 * 	\param alpha_blending decides whether the alpha channel should be interpolated between colors
			*/
			ColorTable(Size size, const ColorRGBA& color, bool alpha_blending=false)
				throw();

			/**
			*/
			ColorTable(const ColorTable& color_table, Index from, Index to, bool alpha_blending=false)
				throw();

			/**
			*/
			ColorTable(const ColorRGBA* color_array, Size array_size, bool alpha_blending=false)
				throw();

			/**	Destructor.
			*/
			virtual ~ColorTable()
				throw();
			//@}
			
			/** @name Accessors
			 */
			//@{
			
			/// Set the base colors for the interpolation
			void setBaseColors(const ColorRGBA* color_array, Size array_size)
				throw();

			/// Set the number of colors this table should contain after interpolation.
			void setNumberOfColors(const Size color_number)
				throw();

			/// Return the number of elements in our color table.
			Size getNumberOfColors() const
				throw();

			/// Decides if we should interpolate the alpha channel as well
			void setAlphaBlending(bool blending)
				throw();

			/// Returns true if the alpha channel is interpolated between colors, false otherwise.
			bool getAlphaBlending() const
				throw();

			/** Build the table, i.e. interpolate between the colors to obtain the desired number of colors. 
			 *  Returns the actual size of the table after interpolation.
			 */	
			Size createTable()
				throw();
			
			/** Sets the colors that are used for values below min and above max.
			 */
			void setMinMaxColors(ColorRGBA min, ColorRGBA max)
				throw();

			/** Sets the range used for the mapping.
			 */
			void setRange(float min, float max)
				throw();
		
			/** Maps value into the color table.
			 */
			ColorRGBA& map(float value)
				throw();

			/** Maps value into the color table. (const method)
			 */
			const ColorRGBA& map(float value) const
				throw();
			
			//@}
			/**	@name	Debugging and Diagnostics
			*/	
			//@{

			/**	Dump the content to an ostream
			*/
			virtual void dump(std::ostream& s = std::cout, Size depth = 0) const;
			//@}

			protected:

			Size 			color_number_;
			bool			alpha_blending_;
			ColorRGBA min_color_;
			ColorRGBA	max_color_;
			bool			has_min_max_colors_;
			float			min_;
			float			max_;
		};
  
	} // namespace VIEW
} // namespace BALL

#endif // BALL_VIEW_DATATYPE_COLORTABLE_H