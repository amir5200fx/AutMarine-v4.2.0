#pragma once
#ifndef _Mesh3d_Curve_Header
#define _Mesh3d_Curve_Header

#include <Entity_StaticChain3d.hxx>
#include <Global_Macros.hxx>
#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_CurveOnSurface;
	}

	namespace MeshLib
	{
		class Mesh3d_SizeMap;

		class Mesh3d_Curve
		{

		private:

			const Mesh3d_SizeMap& theMap_;

			const M_CAD Cad3d_CurveOnSurface& theCurve_;

			M_GEO Entity_StaticChain3d theChain_;

			Standard_Real theUnderRelaxation_;

			Standard_Boolean IsDone_;

		public:

			Mesh3d_Curve(const Mesh3d_SizeMap& theSizeMap, const CadLib::Cad3d_CurveOnSurface& theCurve);

			const M_GEO Entity_StaticChain3d& Chain() const;

			Standard_Boolean IsDone() const;

			void SetUnderRelaxation(const Standard_Real Factor);

			//! Throw an exception if null curve detected
			void Perform();

			void ExportToPlt(fstream & File) const;

		private:

			void MakeChain(const TColStd_Ary1dOfReal & Parameters);
		};
	}
}

#include <Mesh3d_CurveI.hxx>

#endif // !_Mesh3d_Curve_Header
