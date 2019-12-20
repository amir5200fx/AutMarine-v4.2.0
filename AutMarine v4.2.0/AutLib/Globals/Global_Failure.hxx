#pragma once
#ifndef _Global_Failure_Header
#define _Global_Failure_Header

#include <Standard_OStream.hxx>
#include <Standard_String.hxx>
#include <Standard_SStream.hxx>
#include <time.h>

namespace AutLib
{

	template<typename S>
	inline void CloseProgram(const S& v)
	{
		cout << v << ". Program exited!\n";

		system("pause");
		exit(1);
	}

	template<typename S>
	inline void WarningProgram(const S& v)
	{
		cout << v << ". Program Terminated!\n";
	}

	inline void CloseProgram()
	{
		cout << ". Program exited!\n";

		system("pause");
		exit(1);
	}

	inline Standard_String getSource(const Standard_Character* _file, const Standard_Character* _function, const Standard_Integer _number)
	{
		Standard_SStream _string;

		_string
			<< _file
			<< " # line nb. "
			<< _number
			<< " at function: "
			<< _function;

		return _string.str();
	}

	inline Standard_String Implimented(const Standard_Character* _file, const Standard_Character* _function, const Standard_Integer _number)
	{
		Standard_SStream _string;

		_string
			<< " Implimented in "
			<< _file
			<< " # line nb. "
			<< _number
			<<
			" at function: "
			<< _function;

		return _string.str();
	}

	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	inline const std::string CurrentDateTime() 
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

	class Global_Failure
	{

	public:

		virtual void What(Standard_OStream & Ostream = cout) const
		{
			Ostream << " Exception has been occured!\n";
		}
	};

	class Bad_Boundary_Failure : public Global_Failure
	{

	public:

		void What(Standard_OStream & Ostream = cout) const override
		{
			Ostream << " Bad Boundary has been occured!\n";
		}
	};

	class Bad_Surface_Failure : public Global_Failure
	{

	public:

		void What(Standard_OStream & Ostream = cout) const override
		{
			Ostream << " Bad Surface has been occured!\n";
		}
	};

	class NonConvergency_Iteration_Failure : public Global_Failure
	{

	public:

		Standard_Integer maxNbIters_;
		Standard_Real resolution_;

		void What(Standard_OStream & Ostream = cout) const override
		{
			Ostream << " NonConvergency Iteration Algorithm has been occured!\n";
		}
	};
}

#endif // !_Global_Failure_Header
