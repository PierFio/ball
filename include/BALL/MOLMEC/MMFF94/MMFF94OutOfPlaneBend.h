// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: MMFF94OutOfPlaneBend.h,v 1.1.6.1 2006/06/09 14:04:03 leonhardt Exp $
//

#ifndef BALL_MOLMEC_MMFF94_MMFF94OUTOFPLANEBEND_H
#define BALL_MOLMEC_MMFF94_MMFF94OUTOFPLANEBEND_H

#ifndef BALL_MOLMEC_COMMON_FORCEFIELDCOMPONENT_H
#	include <BALL/MOLMEC/COMMON/forceFieldComponent.h>
#endif

#ifndef BALL_MOLMEC_COMMON_FORCEFIELD_H
#	include <BALL/MOLMEC/COMMON/forceField.h>
#endif

#ifndef BALL_MOLMEC_MMFF94_MMFF94PARAMETERS_H
#	include <BALL/MOLMEC/MMFF94/MMFF94Parameters.h>
#endif

namespace BALL 
{
	/**	MMFF94 Out of plane component
    	\ingroup  MMFF94
	*/
	class BALL_EXPORT MMFF94OutOfPlaneBend 
		: public ForceFieldComponent
	{
		public:

		struct BALL_EXPORT OutOfPlaneBend
		{
			Atom::StaticAtomAttributes *i, *j, *k, *l;
			double k_oop;
			// debug
			double energy;  
		};

		BALL_CREATE(MMFF94OutOfPlaneBend)

		///	Default constructor.
		MMFF94OutOfPlaneBend();

		///	Constructor.
		MMFF94OutOfPlaneBend(ForceField& force_field);

		///	Copy constructor
		MMFF94OutOfPlaneBend(const MMFF94OutOfPlaneBend& to_copy);

		///	Destructor.
		virtual ~MMFF94OutOfPlaneBend();

		///	Setup method.
		virtual bool setup()
			throw(Exception::TooManyErrors);

		///	Calculates and returns the component's energy.
		virtual double updateEnergy();

		///	Calculates and returns the component's forces.
		virtual void updateForces();

		///
		const vector<OutOfPlaneBend>& getOutOfPlaneBends() const { return bends_;}

		private:
		vector<OutOfPlaneBend> bends_;
		MMFF94PlaneParameters parameters_;
	};

} // namespace BALL

#endif // BALL_MOLMEC_MMFF94_MMFF94OUTOFPLANEBEND_H