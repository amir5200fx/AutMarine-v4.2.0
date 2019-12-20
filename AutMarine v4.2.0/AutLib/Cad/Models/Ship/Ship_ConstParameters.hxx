#pragma once
#ifndef _Ship_ConstParameters_Header
#define _Ship_ConstParameters_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_ConstParameters
		{

		public:

			static Standard_Integer LevelOfSmoothing();

			static Standard_Real SmoothWeight();

			static Standard_Real AftComp();

			static Standard_Real FwdComp();

			static Standard_Real MaxDeadRiseAngle();

			static Standard_Real MaxSideSlopeAngle();

			static Standard_Real MinDistanceCoefficient();

			static Standard_Real StemCurvatureCoefficient();

			static Standard_Real MaxSideSlopeCoefficient();

			static Standard_Real MaxDeadRiseCoefficient();

			static Standard_Real MinBowRoundingCoefficient();

			static Standard_Integer MinNbSections();

			static Standard_Real MaxLength();

			static Standard_Real MinLength();

			static Standard_Real MaxBreadth();

			static Standard_Real MinBreadth();

			static Standard_Real MaxDepth();

			static Standard_Real MinDepth();

			static Standard_Integer MaxNbSections();

			static Standard_Integer MaxNbRows();

			static Standard_Integer MinNbRows();

			static Standard_Real MinDraft();

			static Standard_Real MaxDraft();

			static Standard_Real MinTransomHeight();

			static Standard_Real MaxTransomHeight();

			static Standard_Real MinTightness();

			static Standard_Real MaxTightness();

			static Standard_Real MinDeadRise();

			static Standard_Real MaxDeadRise();

			static Standard_Real MinSideSlope();

			static Standard_Real MaxSideSlope();

			static Standard_Real MinFlare();

			static Standard_Real MaxFlare();

			static Standard_Real MinSkeg();

			static Standard_Real MaxSkeg();

			static Standard_Real MinAreaLocation();

			static Standard_Real MaxAreaLocation();

			static Standard_Real MinSheerHeight();

			static Standard_Real MaxSheerHeight();

			static Standard_Real MinSheerPosition();

			static Standard_Real MaxSheerPosition();

			static Standard_Real MinFullness();

			static Standard_Real MaxFullness();

			static Standard_Real MinRake();

			static Standard_Real MaxRake();

			static Standard_Real MinWidth();

			static Standard_Real MaxWidth();

			static Standard_Real MinKeelPosition();

			static Standard_Real MaxKeelPosition();

			static Standard_Real MinKeelRisePoint();

			static Standard_Real MaxKeelRisePoint();

			static Standard_Real MinKeelRiseTangent();

			static Standard_Real MaxKeelRiseTangent();

			static Standard_Real MinKeelTransomTangent();

			static Standard_Real MaxKeelTransomTangent();

			static Standard_Real MinBowRounding();

			static Standard_Real MaxBowRounding();

			static Standard_Real MinStemRake();

			static Standard_Real MaxStemRake();

			static Standard_Real MinStemCurvature();

			static Standard_Real MaxStemCurvature();

			static Standard_Real MinStemCurvaturePosition();

			static Standard_Real MaxStemCurvaturePosition();

			static Standard_Real MinForeFootShape();

			static Standard_Real MaxForeFootShape();

			static Standard_Real MaxBperL();

			static Standard_Real MaxDperL();
		};
	}
}

#define Set_ShipParameterValue(X, MinValue, MaxValue, Parameter) \
    Parameter = X;                                               \
    if (Parameter < MinValue) Parameter = MinValue;              \
    if (Parameter > MaxValue) Parameter = MaxValue;

#endif // !_Ship_ConstParameters_Header
