//
// DateFormatter.cpp
//
// $Id: //poco/Main/WebWidgets/src/DateFormatter.cpp#4 $
//
// Library: WebWidgets
// Package: Formatters
// Module:  DateFormatter
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/WebWidgets/DateFormatter.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Timezone.h"


namespace Poco {
namespace WebWidgets {


DateFormatter::DateFormatter(const std::string& format):
	_format(format)
{
}


DateFormatter::~DateFormatter()
{
}


std::string DateFormatter::format(const Poco::Any& value) const
{
	const Poco::DateTime& dt = Poco::RefAnyCast<DateTime>(value);
	return DateTimeFormatter::format(dt, _format, Timezone::utcOffset());
}


Poco::Any DateFormatter::parse(const std::string& value) const
{
	int diff(0);
	Poco::DateTime dt;
	DateTimeParser::parse(_format, value, dt, diff);
	return dt;
}


bool DateFormatter::lowerThan(const Poco::Any& first, const Poco::Any& second) const
{
	if (first.empty())
		return true;
	if (second.empty())
		return false;
	
	return Poco::RefAnyCast<DateTime>(first) < Poco::RefAnyCast<DateTime>(second);
}


} } // namespace Poco::WebWidgets
