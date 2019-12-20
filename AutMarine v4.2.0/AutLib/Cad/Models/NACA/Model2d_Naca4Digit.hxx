#pragma once
#ifndef _Model2d_Naca4Digit_Header
#define _Model2d_Naca4Digit_Header

#include <Global_Memory.hxx>
#include <Model2d_Naca.hxx>
#include <Model2d_Naca4DigitParameters.hxx>
#include <TColStd_Ary1dOfReal.hxx>

class gp_Ax2d;
class gp_Ax22d;

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_Plane;

		class Model2d_Naca4Digit : public Model2d_Naca
		{

		private:

			Standard_Integer theNbOffsetPoints_;

			Model2d_Naca4DigitParameters theParameters_;

		public:

			Model2d_Naca4Digit();

			Model2d_Naca4DigitParameters& Parameters();

			const Model2d_Naca4DigitParameters& Parameters() const;

			void SetNbOffsets(const Standard_Integer NbOffsetPoints);

			void Perform();

			//! Warning: The Plane must be deleted to release the memory
			Global_Handle(Cad2d_Plane) ExportAsPart(const gp_Ax2d& A, const Standard_Boolean Sense = Standard_True) const;

			//! Warning: The Plane must be deleted to release the memory
			Global_Handle(Cad2d_Plane) ExportAsPart(const gp_Ax22d& A) const;

		private:

			//! Throw an exception if NbSegments < 1
			TColStd_Ary1dOfReal Parameters(const Standard_Integer NbSegmets) const;

			TColStd_Ary1dOfReal CamberOffsets(const TColStd_Ary1dOfReal& Parameters) const;

			TColStd_Ary1dOfReal ThicknessDistribution(const TColStd_Ary1dOfReal& Parameters) const;

			TColStd_Ary1dOfReal CamberTangentDistribution(const TColStd_Ary1dOfReal& Parameters) const;
		};
	}
}

#endif // !_Model2d_Naca4Digit_Header
