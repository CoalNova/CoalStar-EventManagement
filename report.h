#pragma once

namespace Coal
{
	enum class ReportLevel{Info, Warning, Error, Terminal, UNUSED_LAST};

	struct Report
	{
		ReportLevel level; //is it bad and by how much
		void* caller; //whomst
		int alpha, //data one
			beta; //data two
		char description[32]; //this may be insuffecient for full utilization

	};
}