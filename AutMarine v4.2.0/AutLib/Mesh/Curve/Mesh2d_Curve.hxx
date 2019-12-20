#pragma once
#ifndef _Mesh2d_Curve_Header
#define _Mesh2d_Curve_Header

#include <Standard_Real.hxx>
#include <Standard_Handle.hxx>
#include <Global_Memory.hxx>
#include <Standard_Stream.hxx>
#include <Entity_StaticChain2d.hxx>
#include <TColStd_Ary1dOfReal.hxx>

class Geom2d_Curve;

namespace AutLib
{
	namespace CadLib
	{
		class Cad2d_CurveOnPlane;
		class Cad3d_CurveOnPlane;
	}

	namespace MeshLib
	{
		
		class Mesh2d_SizeMap;

		class Mesh2d_Curve
		{

		protected:

			const Global_Handle(Mesh2d_SizeMap) theMap_;

			Handle(Geom2d_Curve) theCurve_;

			M_GEO Entity_StaticChain2d theChain_;

			Standard_Real theUnderRelaxation_;

			Standard_Boolean IsDone_;

			Standard_Real theFirst_;
			Standard_Real theLast_;

		public:

			Mesh2d_Curve(const Mesh2d_SizeMap& SizeMap, const Global_Handle(M_CAD Cad2d_CurveOnPlane) theCurve);

			Mesh2d_Curve(const Mesh2d_SizeMap& SizeMap, const Global_Handle(M_CAD Cad3d_CurveOnPlane) theCurve);

			Mesh2d_Curve(const Mesh2d_SizeMap& SizeMap, const Global_Handle(Geom2d_Curve) Curve, const Standard_Real First, const Standard_Real Last);

			~Mesh2d_Curve();

			const M_GEO Entity_StaticChain2d& Chain() const;

			Standard_Boolean IsDone() const;

			void SetRelaxation(const Standard_Real Factor);

			void Perform();

			void ExportToPlt(fstream & File) const;

		private:

			void MakeChain(const TColStd_Ary1dOfReal& Parameters);
		};
	}
}

#endif // !_Mesh2d_Curve_Header
