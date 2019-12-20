#pragma once
#ifndef _Entity_PolyLine3d_Header
#define _Entity_PolyLine3d_Header

#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_PolyLine3d
		{

		private:

			TColGeom_Ary1dOfPnt3d thePoints_;

			Standard_Real theDeflection_;

		public:

			Entity_PolyLine3d();

			Entity_PolyLine3d(const TColGeom_Ary1dOfPnt3d& thePoints);

			void Init(const TColGeom_Ary1dOfPnt3d& thePoints);

			Standard_Integer NbPoints() const;

			Standard_Real Deflection() const;

			Standard_Boolean IsClosed() const;

			Entity_PolyLine3d Reversed() const;

			const TColGeom_Ary1dOfPnt3d& Points() const;

			TColGeom_Ary1dOfPnt3d& Points();

			void SetDeflection(const Standard_Real D);

			void SetCoords(const TColGeom_Ary1dOfPnt3d& Points);

			void Reverse();

			void Smoothing(const Standard_Real Omega, const Standard_Integer NbIterations);

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Entity_PolyLine3dI.hxx>

#endif // !_Entity_PolyLine3d_Header
