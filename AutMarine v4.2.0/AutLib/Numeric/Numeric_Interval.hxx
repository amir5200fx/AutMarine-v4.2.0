#pragma once
#ifndef _Numeric_Interval_Header
#define _Numeric_Interval_Header

#include <iostream>

#include <Global_Macros.hxx>

using namespace std;

namespace AutLib
{
	namespace NumLib
	{

#define MSW 3


		static unsigned short mask[16] = {
			0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
			0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };

		typedef union {
			double dp;
			unsigned short sh[4];
		} Double;

		inline double ulp(double x)
		{
			Double U, X;

			int bit, e1, word;

			X.dp = x;
			X.sh[MSW] &= 0x7ff0;

			U.dp = 0.0;

			if (X.sh[MSW] > 0x0340)
				U.sh[MSW] = X.sh[MSW] - 0x0340;
			else
			{
				e1 = (X.sh[MSW] >> 4) - 1;
				word = e1 >> 4;

				if (MSW == 0) word = 3 - word;

				bit = e1 % 16;
				U.sh[word] |= mask[bit];
			}

			return U.dp;
		}

		class Interval
		{

		private:

			double low_;
			double upp_;

		public:

			Interval() { low_ = upp_ = 0; }  // default constructor
			Interval(double x)
			{
				low_ = upp_ = x;

				double r = ulp(x);

				low_ -= r;
				upp_ += r;
			}
			Interval(double x, double y)
			{
				low_ = x;
				upp_ = y;

				low_ -= ulp(x);
				upp_ += ulp(y);
			}

			inline Interval& operator=(double _d);
			inline Interval& operator+=(double _d);
			inline Interval& operator-=(double _d);
			inline Interval& operator*=(double _d);
			inline Interval& operator/=(double _d);
			inline Interval& operator=(const Interval&);
			inline Interval& operator+=(const Interval&);
			inline Interval& operator-=(const Interval&);
			inline Interval& operator*=(const Interval&);
			inline Interval& operator/=(const Interval&);

			inline double Lower() const { return low_; }
			inline double Upper() const { return upp_; }

			inline void Print(ostream& out = cout) const
			{
				out << "[" << low_ << "," << upp_ << "]";
			}
		};

		inline ostream& operator<<(ostream& _os, const Interval& _x)
		{
			_os << "[" << _x.Lower() << "," << _x.Upper() << "]";
			return _os;
		}

		Interval& Interval::operator=(double _d)
		{
			Interval x(_d);

			*this = x;

			return *this;
		}

		Interval& Interval::operator+=(double _d)
		{
			Interval x(_d);

			*this += x;

			return *this;
		}

		Interval& Interval::operator-=(double _d)
		{
			Interval x(_d);

			*this -= x;

			return *this;
		}

		Interval& Interval::operator*=(double _d)
		{
			Interval x(_d);

			*this *= x;

			return *this;
		}

		Interval& Interval::operator/=(double _d)
		{
			Interval x(_d);

			*this /= x;

			return *this;
		}

		Interval& Interval::operator=(const Interval& _x)
		{
			low_ = _x.low_;
			upp_ = _x.upp_;

			return *this;
		}

		Interval& Interval::operator+=(const Interval& _x)
		{
			low_ += _x.low_;
			upp_ += _x.upp_;

			low_ -= ulp(low_);
			upp_ += ulp(upp_);

			return *this;
		}

		Interval& Interval::operator-=(const Interval& _x)
		{
			low_ -= _x.upp_;
			upp_ -= _x.low_;

			low_ -= ulp(low_);
			upp_ += ulp(upp_);

			return *this;
		}

		Interval& Interval::operator*=(const Interval& _x)
		{
			double a1, a2, a3, a4;

			a1 = low_*_x.low_;
			a2 = low_*_x.upp_;
			a3 = upp_*_x.low_;
			a4 = upp_*_x.upp_;

			low_ = MIN(a1, a2);
			low_ = MIN(low_, a3);
			low_ = MIN(low_, a4);

			upp_ = MAX(a1, a2);
			upp_ = MAX(upp_, a3);
			upp_ = MAX(upp_, a4);

			low_ -= ulp(low_);
			upp_ += ulp(upp_);

			return *this;
		}

		Interval& Interval::operator/=(const Interval& _x)
		{
			Interval x(1.0 / _x.upp_, 1.0 / _x.low_);

			(*this) *= x;

			return *this;
		}

		inline Interval operator+(const Interval& _x1, const Interval& _x2)
		{
			Interval x = _x1;

			x += _x2;

			return x;
		}

		inline Interval operator-(const Interval& _x1, const Interval& _x2)
		{
			Interval x = _x1;

			x -= _x2;

			return x;
		}

		inline Interval operator*(const Interval& _x1, const Interval& _x2)
		{
			Interval x = _x1;

			x *= _x2;

			return x;
		}

		inline Interval operator/(const Interval& _x1, const Interval& _x2)
		{
			Interval x = _x1;

			x /= _x2;

			return x;
		}

		inline Interval operator+(double _d, const Interval& _x)
		{
			Interval x(_d);

			x += _x;

			return x;
		}

		inline Interval operator+(const Interval& _x, double _d)
		{
			Interval x(_d);

			x += _x;

			return x;
		}

		inline Interval operator-(double _d, const Interval& _x)
		{
			Interval x(_d);

			x -= _x;

			return x;
		}

		inline Interval operator-(const Interval& _x, double _d)
		{
			Interval x(_d);
			Interval y(_x);

			y -= x;

			return y;
		}

		inline Interval operator*(double _d, const Interval& _x)
		{
			Interval x(_d);

			x *= _x;

			return x;
		}

		inline Interval operator*(const Interval& _x, double _d)
		{
			Interval x(_d);

			x *= _x;

			return x;
		}

		inline Interval Sqrt(const Interval& _x)
		{
			return Interval(sqrt(_x.Lower()), sqrt(_x.Upper()));
		}

		inline Interval Sin(const Interval& _x)
		{
			return Interval(sin(_x.Lower()), sin(_x.Upper()));
		}

		inline Interval Cos(const Interval& _x)
		{
			return Interval(cos(_x.Lower()), cos(_x.Upper()));
		}
	}
}

#endif // !_Numeric_Interval_Header
