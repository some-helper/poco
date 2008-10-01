//
// Table.cpp
//
// $Id: //poco/Main/WebWidgets/src/Table.cpp#14 $
//
// Library: WebWidgets
// Package: Views
// Module:  Table
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
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


#include "Poco/WebWidgets/Table.h"
#include "Poco/WebWidgets/RequestHandler.h"
#include "Poco/NumberParser.h"
#include "Poco/Net/HTTPServerResponse.h"


namespace Poco {
namespace WebWidgets {


const std::string Table::FIELD_COL("col");
const std::string Table::FIELD_ROW("row");
const std::string Table::FIELD_VAL("val");
const std::string Table::FIELD_CNT("cnt");
const std::string Table::EV_CELLCLICKED("click");
const std::string Table::EV_BEFORECELLCLICKED("beforeclick");
const std::string Table::EV_ROWCLICKED("row");
const std::string Table::EV_BEFOREROWCLICKED("beforerow");
const std::string Table::EV_CELLVALUECHANGED("edit");
const std::string Table::EV_BEFORECELLVALUECHANGED("beforeedit");
const std::string Table::EV_LOADDATA("load");
const std::string Table::EV_AFTERLOAD("afterload");
const std::string Table::EV_RENDER("render");
const std::string Table::EV_MOUSEUP("mouseup");
const std::string Table::EV_MOUSEDOWN("mousedown");
const std::string Table::EV_KEYDOWN("keydown");
const std::string Table::EV_KEYPRESSED("keypressed");
const std::string Table::EV_ROWSELECTED("rowselected");
const std::string Table::EV_CELLSELECTED("cellselected");
const std::string Table::EV_STARTCELLVALUECHANGE("startedit");


Table::Table(const TableColumns& tc, TableModel::Ptr pModel):
	View(typeid(Table)),
	_pModel(pModel),
	_columns(tc),
	_sm(SM_CELL),
	_dragAndDrop(false),
	_autoEdit(false),
	_maxRowsPerPage(0)
{
	checkValidConfig();
}

	
Table::Table(const std::string& name, const TableColumns& tc, TableModel::Ptr pModel):
	View(name, typeid(Table)),
	_pModel(pModel),
	_columns(tc),
	_sm(SM_CELL),
	_dragAndDrop(false),
	_maxRowsPerPage(0)
{
	checkValidConfig();
}


Table::Table(const std::string& name, const std::type_info& type, const TableColumns& tc, TableModel::Ptr pModel):
	View(name, type),
	_pModel(pModel),
	_columns(tc),
	_sm(SM_CELL),
	_dragAndDrop(false),
	_maxRowsPerPage(0)
{
	checkValidConfig();
}


Table::Table(const std::type_info& type, const TableColumns& tc, TableModel::Ptr pModel):
	View(type),
	_pModel(pModel),
	_columns(tc),
	_sm(SM_CELL),
	_dragAndDrop(false),
	_maxRowsPerPage(0)
{
	checkValidConfig();
}


Table::~Table()
{
}


void Table::checkValidConfig()
{
	if (_columns.empty())
		throw Poco::InvalidArgumentException("At least one column is required for a table");
	if (!_pModel)
		throw Poco::InvalidArgumentException("An empty model is not allowed");
	if (_columns.size() != _pModel->getColumnCount())
		throw Poco::InvalidArgumentException("Model column count mismatches Columns count");

	TableColumns::iterator it = _columns.begin();
	for (; it != _columns.end(); ++it)
	{
		if ((*it))
			adoptChild((*it));;
	}
}


void Table::handleForm(const std::string& field, const std::string& value)
{
	// Form fields from a table?
}


void Table::handleAjaxRequest(const Poco::Net::NameValueCollection& args, Poco::Net::HTTPServerResponse& response)
{
	static const std::string strZero("0");
	static const std::string strMin1("-1");
	const std::string& ev = args[RequestHandler::KEY_EVID];
	const std::string& strRow = args.get(FIELD_ROW, strMin1);
	const std::string& strCol = args.get(FIELD_COL, strMin1);
	const std::string& strCnt = args.get(FIELD_CNT, strZero);
	int row(-1);
	int cnt(-1);
	int col(-1);
	Poco::NumberParser::tryParse(strRow, row);
	Poco::NumberParser::tryParse(strCol, col);
	Poco::NumberParser::tryParse(strCnt, cnt);
	if (ev == EV_LOADDATA)
	{
		const std::string& strLimit = args.get("limit", strCnt); //Extjs hack
		const std::string& strStart = args.get("start", strRow);
		Poco::NumberParser::tryParse(strStart, row);
		Poco::NumberParser::tryParse(strLimit, cnt);
		/// serialize the Table back
		/// check for cnt and start if only a segment was requested	
		if (row < 0)
			row = 0;
		if (cnt < 0)
			cnt = 0;
		LoadData ld(&response, this, row, cnt);
		beforeLoad.notify(this, ld);
	}
	else if (ev == EV_CELLCLICKED)
	{
		if (col < 0 || row < 0 || col >= getColumnCount())
			throw InvalidArgumentException("col/row out of range");

		CellClick ev(row, col);
		cellClicked(this, ev);
		response.send();
	}
	else if (ev == EV_BEFORECELLCLICKED)
	{
		if (col < 0 || row < 0 || col >= getColumnCount())
			throw InvalidArgumentException("col/row out of range");

		CellClick ev(row, col);
		beforeCellClicked(this, ev);
		response.send();
	}
	else if (ev == EV_ROWCLICKED)
	{
		if (row < 0 )
			throw InvalidArgumentException("row out of range");

		std::size_t theRow(row);
		rowClicked(this, theRow);
		response.send();
	}
	else if (ev == EV_BEFOREROWCLICKED)
	{
		if (row < 0 )
			throw InvalidArgumentException("row out of range");

		std::size_t theRow(row);
		beforeRowClicked(this, theRow);
		response.send();
	}
	else if (ev == EV_CELLVALUECHANGED)
	{
		if (col < 0 || row < 0 || col >= getColumnCount())
			throw InvalidArgumentException("col/row out of range");
		const std::string& val = args.get(FIELD_VAL);
		Cell::Ptr pCell = getColumns()[col]->getCell();
		Formatter::Ptr pForm;
		if (pCell)
			pForm = pCell->getFormatter();
		if (pForm)
		{
			Poco::Any any = pForm->parse(val);
			setValue(any, row, col);
		}
		else
			setValue(Poco::Any(val), row, col);
		response.send();
	}
	else if (ev == EV_BEFORECELLVALUECHANGED)
	{
		const std::string& val = args.get(FIELD_VAL);
		Poco::Any oldValue;
		if (getColumnCount() > col)
			oldValue = getValue(row, col);
			
		Cell::Ptr pCell = getColumns()[col]->getCell();
		Formatter::Ptr pForm;
		if (pCell)
			pForm = pCell->getFormatter();
		
		if (pForm)
		{
			Poco::Any newValue = pForm->parse(val);
			CellValueChange cvc(row, col, oldValue, newValue);	
			beforeCellValueChanged(this, cvc);
		}
		else
		{
			Poco::Any newValue(val);
			CellValueChange cvc(row, col, oldValue, newValue);	
			beforeCellValueChanged(this, cvc);
		}
		response.send();
	}
	else if (ev == EV_AFTERLOAD)
	{
		Table* pTable = this;
		afterLoad(this, pTable);
		response.send();
	}
	else if (ev == EV_RENDER)
	{
		Table* pTable = this;
		afterRender(this, pTable);
		response.send();
	}
	else if (ev == EV_MOUSEUP)
	{
		Table* pTable = this;
		mouseUp(this, pTable);
		response.send();
	}
	else if (ev == EV_MOUSEDOWN)
	{
		Table* pTable = this;
		mouseDown(this, pTable);
		response.send();
	}
	else if (ev == EV_KEYDOWN)
	{
		Table* pTable = this;
		keyDown(this, pTable);
		response.send();
	}
	else if (ev == EV_KEYPRESSED)
	{
		Table* pTable = this;
		keyPressed(this, pTable);
		response.send();
	}
	else if (ev == EV_CELLSELECTED)
	{
		if (col < 0 || row < 0 || col >= getColumnCount())
			throw InvalidArgumentException("col/row out of range");

		CellClick ev(row, col);
		cellSelected(this, ev);
		response.send();
	}
	else if (ev == EV_ROWSELECTED)
	{
		if (row < 0 )
			throw InvalidArgumentException("row out of range");

		std::size_t theRow(row);
		rowSelected(this, theRow);
		response.send();
	}
	else if (ev == EV_STARTCELLVALUECHANGE)
	{
		if (col < 0 || row < 0 || col >= getColumnCount())
			throw InvalidArgumentException("col/row out of range");

		CellClick ev(row, col);
		startCellValueChange(this, ev);
		response.send();
	}
}


void Table::setValue(const Poco::Any& val, std::size_t row, std::size_t col)
{
	Poco::Any oldValue;
	if (getRowCount() > row)
		oldValue = getValue(row, col); 
	CellValueChange ev(row, col, oldValue, val);
	beforeCellValueChanged(this,ev);
	_pModel->setValue(ev.newValue, row, col);
	cellValueChanged(this, ev);
}


Table::CellClick::CellClick(std::size_t r, std::size_t c):
	row(r),
	col(c)
{
}


Table::CellValueChange::CellValueChange(std::size_t r, std::size_t c, const Poco::Any& old, const Poco::Any& n):
	row(r),
	col(c),
	oldValue(old),
	newValue(n)
{
}


Table::LoadData::LoadData(Poco::Net::HTTPServerResponse* pR, Table* pT, int row, int cnt):
	pResponse(pR),
	pTable(pT),
	firstRow(row),
	rowCnt(cnt)
{
}


bool Table::serializeJSON(std::ostream& out, const std::string& name)
{
	return false;
}


} } // namespace Poco::WebWidgets
