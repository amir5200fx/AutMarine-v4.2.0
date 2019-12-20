#pragma once
#ifndef _Rudder_Section_Header
#define _Rudder_Section_Header

#include <Standard_Handle.hxx>
#include <Geom_Pnt3d.hxx>
#include <TColStd_Ary1dOfReal.hxx>

class Geom_Curve;

namespace AutLib
{
	namespace CadLib
	{

		class Rudder_Section
		{

		private:

			Standard_Integer theNbOffsetPoints_;

			Standard_Real theChord_;
			Standard_Real theThickness_;
			Standard_Real theTEGap_;

			Standard_Boolean IsDone_;

			Handle(Geom_Curve) theUpper_;
			Handle(Geom_Curve) theLower_;

		public:

			Rudder_Section();

			Standard_Boolean IsDone() const;

			const Handle(Geom_Curve)& UpperCurve() const;

			const Handle(Geom_Curve)& LowerCurve() const;

			void SetNbOffsets(const Standard_Integer NbOffsetPoints);

			void SetChord(const Standard_Real theValue);

			void SetThickness(const Standard_Real theValue);

			void Perform();

			void ExportToPlt(fstream& File) const;

		private:

			//! Throw an exception if NbSegments < 1
			TColStd_Ary1dOfReal Parameters(const Standard_Integer NbSegmets) const;

			TColStd_Ary1dOfReal ThicknessDistribution(const TColStd_Ary1dOfReal& Parameters) const;
		};
	}
}

#include <Rudder_SectionI.hxx>

#endif // !_Rudder_Section_Header
