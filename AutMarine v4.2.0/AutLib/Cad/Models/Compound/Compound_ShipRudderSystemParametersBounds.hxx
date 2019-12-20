#pragma once
#ifndef _Compound_ShipRudderSystemParametersBounds_Header
#define _Compound_ShipRudderSystemParametersBounds_Header

#include <Compound_BoundedParameter.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Compound_ShipRudderSystemParametersBounds
		{

		private:

			Compound_BoundedParameter theX_;
			Compound_BoundedParameter theY_;
			Compound_BoundedParameter theZ_;

			Compound_BoundedParameter theShaftInclination_;

		public:

			Compound_ShipRudderSystemParametersBounds();

			const Compound_BoundedParameter& X() const;

			const Compound_BoundedParameter& Y() const;

			const Compound_BoundedParameter& Z() const;

			const Compound_BoundedParameter& ShaftInclination() const;

			void SetX(const Compound_BoundedParameter& theX);

			void SetY(const Compound_BoundedParameter& theY);

			void SetZ(const Compound_BoundedParameter& theZ);

			void SetShaftInclination(const Compound_BoundedParameter& theInclination);
		};
	}
}

#include <Compound_ShipRudderSystemParametersBoundsI.hxx>

#endif // !_Compound_ShipRudderSystemParametersBounds_Header
