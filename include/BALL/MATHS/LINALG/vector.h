#ifndef BALL_LINALG_VECTOR_H
#define BALL_LINALG_VECTOR_H

#ifndef BALL_COMMON_GLOBAL_H
# include <BALL/COMMON/global.h>
#endif

namespace BALL {

  template <class valuetype>
  class Vector;

  template <class valuetype, class mtraits>
  class Matrix;
}

#include <BALL/MATHS/LINALG/vector.ih>

#ifdef BALL_OS_WINDOWS
	namespace BALL
	{
		// explicit instantiation needed to export the template
		template class BALL_EXPORT Vector<float>;
		template class BALL_EXPORT Vector<double>;
		template class BALL_EXPORT Vector<ComplexFloat>;
		template class BALL_EXPORT Vector<ComplexDouble>;
	}
#endif

#include <BALL/MATHS/LINALG/matrix.ih>

#include <BALL/MATHS/LINALG/vectorConstructors.iC>
#include <BALL/MATHS/LINALG/vectorIO.iC>
#include <BALL/MATHS/LINALG/vectorBasicFunctions.iC>
#include <BALL/MATHS/LINALG/vectorIterators.iC>

#include <BALL/MATHS/LINALG/matrixConstructors.iC>
#include <BALL/MATHS/LINALG/matrixBasicFunctions.iC>
#include <BALL/MATHS/LINALG/matrixIO.iC>
#include <BALL/MATHS/LINALG/matrixIterator.iC>

#endif // BALL_LINALG_VECTOR_H