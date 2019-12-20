#include <Ship_ConstParameters.hxx>

Standard_Integer AutLib::CadLib::Ship_ConstParameters::LevelOfSmoothing()
{
	return 3;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::SmoothWeight()
{
	return (Standard_Real)0.25;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::AftComp()
{
	return (Standard_Real)0.05;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::FwdComp()
{
	return (Standard_Real)0.05;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxDeadRiseAngle()
{
	return (Standard_Real)45.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxSideSlopeAngle()
{
	return (Standard_Real)45.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinDistanceCoefficient()
{
	return (Standard_Real)0.05;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::StemCurvatureCoefficient()
{
	return (Standard_Real)0.5;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxSideSlopeCoefficient()
{
	return (Standard_Real)0.9;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxDeadRiseCoefficient()
{
	return (Standard_Real)0.5;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinBowRoundingCoefficient()
{
	return (Standard_Real)0.05;
}

Standard_Integer AutLib::CadLib::Ship_ConstParameters::MinNbSections()
{
	return 5;
}

Standard_Integer AutLib::CadLib::Ship_ConstParameters::MinNbRows()
{
	return 6;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinDraft()
{
	return 0.01*MinDepth();
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxDraft()
{
	return MaxDepth();
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinTransomHeight()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxTransomHeight()
{
	return MaxDepth();
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxLength()
{
	return (Standard_Real)500.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinLength()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxBreadth()
{
	return (Standard_Real)500.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinBreadth()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxDepth()
{
	return (Standard_Real)500.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinDepth()
{
	return (Standard_Real)1.0;
}

Standard_Integer AutLib::CadLib::Ship_ConstParameters::MaxNbSections()
{
	return 100;
}

Standard_Integer AutLib::CadLib::Ship_ConstParameters::MaxNbRows()
{
	return 60;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinTightness()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxTightness()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinDeadRise()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxDeadRise()
{
	return (Standard_Real)45.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinSideSlope()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxSideSlope()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinFlare()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxFlare()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinSkeg()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxSkeg()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinAreaLocation()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxAreaLocation()
{
	return MaxLength();
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinSheerHeight()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxSheerHeight()
{
	return (Standard_Real)2.0*MaxDepth();
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinSheerPosition()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxSheerPosition()
{
	return MaxLength();
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinFullness()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxFullness()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinRake()
{
	return -(Standard_Real)50.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxRake()
{
	return (Standard_Real)50.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinWidth()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxWidth()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinKeelPosition()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxKeelPosition()
{
	return (Standard_Real)1.0;
}


Standard_Real AutLib::CadLib::Ship_ConstParameters::MinKeelRisePoint()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxKeelRisePoint()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinKeelRiseTangent()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxKeelRiseTangent()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinKeelTransomTangent()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxKeelTransomTangent()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinBowRounding()
{
	return (Standard_Real)0.01;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxBowRounding()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinStemCurvature()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxStemCurvature()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinStemCurvaturePosition()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxStemCurvaturePosition()
{
	return (Standard_Real)1.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MinForeFootShape()
{
	return (Standard_Real)0.0;
}

Standard_Real AutLib::CadLib::Ship_ConstParameters::MaxForeFootShape()
{
	return (Standard_Real)1.0;
}