#pragma once
#ifndef _Mesh3d_CurveIteration_Header
#define _Mesh3d_CurveIteration_Header

#include <Mesh3d_CurveIntegrand.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CurveIteration
		{

		private:

			const Global_Handle(Mesh3d_CurveIntegrand) theIntegrand_;

			Standard_Real theStart_;
			Standard_Real theStep_;
			Standard_Real theTolerance_;

		public:

			Mesh3d_CurveIteration();

			Mesh3d_CurveIteration(const Global_Handle(Mesh3d_CurveIntegrand) CurveIntegrand, const Standard_Real Start, const Standard_Real Step, const Standard_Real Tolerance);

			void SetIntegrand(const Global_Handle(Mesh3d_CurveIntegrand) CurveIntegrand);

			void SetStart(const Standard_Real Value);

			void SetStep(const Standard_Real Value);

			void SetTolerance(const Standard_Real Value);

			Standard_Real Start() const;

			Standard_Real Step() const;

			Standard_Real Tolerance() const;

			const Global_Handle(Mesh3d_CurveIntegrand) Integrand() const;
		};
	}
}

#include <Mesh3d_CurveIterationI.hxx>

#endif // !_Mesh3d_CurveIteration_Header
