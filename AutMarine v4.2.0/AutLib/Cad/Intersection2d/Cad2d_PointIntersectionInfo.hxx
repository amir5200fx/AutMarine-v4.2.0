#pragma once
#ifndef _Cad2d_PointIntersectionInfo_Header
#define _Cad2d_PointIntersectionInfo_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_PointIntersectionInfo
		{

		private:

			Geom_Pnt2d thePoint_;

			Standard_Real theParameter1_;
			Standard_Real theParameter2_;

		public:

			Cad2d_PointIntersectionInfo();

			Cad2d_PointIntersectionInfo(const Standard_Real theParameter1, const Standard_Real theParameter2, const Geom_Pnt2d& thePoint);

			void Init(const Standard_Real theParameter1, const Standard_Real theParameter2, const Geom_Pnt2d& thePoint);

			Standard_Real Parameter1() const;

			Standard_Real Parameter2() const;

			const Geom_Pnt2d& Point() const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Cad2d_PointIntersectionInfoI.hxx>

#endif // !_Cad2d_PointIntersectionInfo_Header
