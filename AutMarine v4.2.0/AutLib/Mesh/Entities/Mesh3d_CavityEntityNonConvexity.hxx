#pragma once
#ifndef _Mesh3d_CavityEntityNonConvexity_Header
#define _Mesh3d_CavityEntityNonConvexity_Header

#include <Mesh3d_CavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Edge;

		class Mesh3d_CavityEntityNonConvexity : public Mesh3d_CavityEntity
		{

		private:

			const Global_Handle(Mesh3d_Edge) theEdge_;

			Standard_Real theAngle_;

		protected:

			Mesh3d_CavityEntityNonConvexity();

			Mesh3d_CavityEntityNonConvexity(const Global_Handle(Mesh3d_Edge) theEdge);

			Mesh3d_CavityEntityNonConvexity(const Global_Handle(Mesh3d_Edge) theEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

		public:

			virtual ~Mesh3d_CavityEntityNonConvexity();

			const Global_Handle(Mesh3d_Edge) Edge() const;

			Standard_Real Angle() const;

			void Init(const Global_Handle(Mesh3d_Edge) theEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			void SetAngle(const Standard_Real theAngle);
		};
	}
}

#include <Mesh3d_CavityEntityNonConvexityI.hxx>

#endif // !_Mesh3d_CavityEntityNonConvexity_Header
