#pragma once
#ifndef _Merge_Triangulation3d_Header
#define _Merge_Triangulation3d_Header

#include <TColEntity_HAry1dOfTriangulation3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Triangulation3d;

		class Merge_Triangulation3d
		{

		private:

			Global_Handle(Entity_Triangulation3d) theTriangulation_;

			Standard_Real theResolution_;
			Standard_Real theRadius_;

			Standard_Boolean IsDone_;

		public:

			Merge_Triangulation3d(const Standard_Real Resolution = 1.0E-3, const Standard_Real Radius = 1.0E-6);

			~Merge_Triangulation3d();

			Global_Handle(Entity_Triangulation3d) Merged() const;

			Standard_Boolean IsDone() const;

			void Import(const TColEntity_HAry1dOfTriangulation3d& theTriangulations);

			void Perform();

			void ReleaseMemory();
		};
	}
}

#endif // !_Merge_Triangulation3d_Header
