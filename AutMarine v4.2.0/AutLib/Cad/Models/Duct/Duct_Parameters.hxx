#pragma once
#ifndef _Duct_Parameters_Header
#define _Duct_Parameters_Header

#include <Duct_Dimensions.hxx>
#include <Duct_HullForm.hxx>
#include <Duct_GeneratorLineForm.hxx>
#include <Duct_BreadthForm.hxx>
#include <Duct_DepthForm.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_Parameters
		{

		private:

			Duct_Dimensions theDimensions_;

			Duct_HullForm theHull_;

			Duct_GeneratorLineForm theGenerator_;

			Duct_BreadthForm theBreadth_;

			Duct_DepthForm theDepth_;

		public:

			Duct_Parameters();

			void SetDimensions(const Duct_Dimensions& theDimensions);

			void SetHullForm(const Duct_HullForm& theHullForm);

			void SetGenerator(const Duct_GeneratorLineForm& theGenerator);

			Duct_Dimensions& Dimensions();

			Duct_HullForm& HullForm();

			Duct_GeneratorLineForm& Generator();

			Duct_BreadthForm& Breadth();

			Duct_DepthForm& Depth();

			const Duct_Dimensions& Dimensions() const;

			const Duct_HullForm& HullForm() const;

			const Duct_GeneratorLineForm& Generator() const;

			const Duct_BreadthForm& Breadth() const;

			const Duct_DepthForm& Depth() const;

		};
	}
}

#include <Duct_ParametersI.hxx>

#endif // !_Duct_Parameters_Header
