#pragma once
#ifndef _Entity_StaticChain2dTools_Header
#define _Entity_StaticChain2dTools_Header

#include <TColEntity_HAry1dOfPolygon2d.hxx>
#include <TColEntity_HAry1dOfNode2d.hxx>
#include <TColEntity_HAry1dOfEdge2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_StaticChain2d;

		class Entity_StaticChain2dTools
		{

		public:

			//! WARNING: The Polygons are not destroyed automatically
			static TColEntity_HAry1dOfPolygon2d GetPolygons(const Entity_StaticChain2d& Chain);

			static void CreateDynamics(const Entity_StaticChain2d& Chain, TColEntity_HAry1dOfNode2d& Nodes, TColEntity_HAry1dOfEdge2d& Edges);
		};
	}
}

#endif // !_Entity_StaticChain2dTools_Header
