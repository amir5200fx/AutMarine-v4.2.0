#pragma once
#ifndef _Ship_Parameters_Header
#define _Ship_Parameters_Header

#include <Ship_Dimensions.hxx>
#include <Ship_HullForm.hxx>
#include <Ship_KeelForm.hxx>
#include <Ship_TransomForm.hxx>
#include <Ship_StemForm.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_Parameters
		{

		private:

			Ship_Dimensions Dimensions_;

			Ship_TransomForm Transom_;

			Ship_StemForm Stem_;

			Ship_HullForm Hull_;

			Ship_KeelForm Keel_;

		public:

			Ship_Parameters();

			void SetDimensions(const Ship_Dimensions& Dimension);

			void SetTransomForm(const Ship_TransomForm& Transom);

			void SetStemForm(const Ship_StemForm& StemForm);

			void SetHullForm(const Ship_HullForm& HullForm);

			void SetKeelForm(const Ship_KeelForm& KeelForm);

			Ship_Dimensions& Dimensions();

			Ship_TransomForm& Transom();

			Ship_StemForm& Stem();

			Ship_HullForm& Hull();

			Ship_KeelForm& Keel();

			const Ship_Dimensions& Dimensions() const;

			const Ship_TransomForm& Transom() const;

			const Ship_StemForm& Stem() const;

			const Ship_HullForm& Hull() const;

			const Ship_KeelForm& Keel() const;
		};
	}
}

#endif // !_Ship_Parameters_Header
