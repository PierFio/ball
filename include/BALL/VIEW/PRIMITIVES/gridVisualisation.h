// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: gridVisualisation.h,v 1.1.2.4 2006/05/05 14:35:59 amoll Exp $
//

#ifndef  BALL_VIEW_PRIMITIV_GRIDSLICE_H
#define  BALL_VIEW_PRIMITIV_GRIDSLICE_H

#ifndef BALL_VIEW_KERNEL_GEOMETRICOBJECT_H
# include <BALL/VIEW/KERNEL/geometricObject.h>
#endif

#ifndef BALL_DATATYPE_REGULARDATA3D_H
# include <BALL/DATATYPE/regularData3D.h>
#endif

namespace BALL
{
	namespace VIEW
	{
		/** GridVisualisation 
				\ingroup ViewKernelGeometricPrimitives
		*/
		class BALL_VIEW_EXPORT GridVisualisation
			: public GeometricObject
		{
			public:

			BALL_CREATE(GridVisualisation)

			///
			GridVisualisation()
				throw();

			///
			GridVisualisation(const GridVisualisation& plane)
				throw();

			/** Destructor
			*/
			virtual ~GridVisualisation()
				throw() {};

			///
			const GridVisualisation& operator = (const GridVisualisation& plane)
				throw();
			
			///
			const Vector3& getNormal() const { return normal_;}

			///
			void setNormal(const Vector3& normal) { normal_ = normal;}

			///
			const Vector3& getPoint() const { return point_;}

			///
			void setPoint(const Vector3& v) { point_ = v;}

			///
			void setGrid(const RegularData3D* grid) { grid_ = grid;}

			///
			const RegularData3D* getGrid() const { return grid_;}

			///
			Position getTexture() const { return texture_;}

			///
			void setTexture(Position texture) { texture_ = texture;}

			Vector3 origin, x,y,z;
			float max_dim;
			Size slices;

			protected:

			Vector3 normal_;
			Vector3 point_;
			Position texture_;
			const RegularData3D* grid_;
		};

	} // namespace VIEW
} // namespace BALL

#endif // BALL_VIEW_KERNEL_CLIPPING_PLANE_H