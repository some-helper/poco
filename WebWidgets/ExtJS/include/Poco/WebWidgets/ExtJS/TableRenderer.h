//
// TableRenderer.h
//
// $Id: //poco/Main/WebWidgets/ExtJS/include/Poco/WebWidgets/ExtJS/TableRenderer.h#2 $
//
// Library: ExtJS
// Package: Core
// Module:  TableRenderer
//
// Definition of the TableRenderer class.
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


#ifndef ExtJS_TableRenderer_INCLUDED
#define ExtJS_TableRenderer_INCLUDED


#include "Poco/WebWidgets/ExtJS/ExtJS.h"
#include "Poco/WebWidgets/Type.h"
#include "Poco/WebWidgets/Renderer.h"
#include "Poco/WebWidgets/Cell.h"
#include "Poco/WebWidgets/Table.h"
#include <map>



namespace Poco {
namespace WebWidgets {

	class TableColumn;
	class TableModel;

namespace ExtJS {


class ExtJS_API TableRenderer: public Poco::WebWidgets::Renderer
	/// TableRenderer renders a button
{
public:
	static const std::string EV_CELLCLICKED;
	static const std::string EV_ROWCLICKED;
	static const std::string EV_BEFORECELLCLICKED;
	static const std::string EV_BEFOREROWCLICKED;
	static const std::string EV_AFTEREDIT;
	static const std::string EV_BEFORECELLVALUECHANGED;
	static const std::string EV_AFTERLOAD;
	static const std::string EV_RENDER;
	static const std::string EV_MOUSEUP;
	static const std::string EV_MOUSEDOWN;
	static const std::string EV_KEYDOWN;
	static const std::string EV_KEYPRESSED;
	static const std::string EV_ROWSELECTED;
	static const std::string EV_CELLSELECTED;
	static const std::string EV_STARTCELLVALUECHANGE;
	static const std::string HIDDEN_INDEX_ROW;
	static const std::string FIELD_TOTALPROPERTY;
	static const std::string FIELD_ROOT;
	
	TableRenderer();
		/// Creates the TableRenderer.

	virtual ~TableRenderer();
		/// Destroys the TableRenderer.

	void renderHead(const Renderable* pRenderable, const RenderContext& context, std::ostream& ostr);
		/// Emits code for the page header to the given output stream.

	void renderBody(const Renderable* pRenderable, const RenderContext& context, std::ostream& ostr);
		/// Emits code for the page body to the given output stream.
		
	static Poco::WebWidgets::JSDelegate createCellValueChangedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has changed a value in the Table
		/// The Extjs handler offers a method signature of "function(obj)" where obj is a complex element containing members (column, row, value)
		
	static Poco::WebWidgets::JSDelegate createBeforeCellValueChangedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has changed a value in the Table
		/// The Extjs handler offers a method signature of "function(obj)" where obj is a complex element 
		/// containing members (grid, record, column, row, value, cancel)!
		/// obj.cancel must be set to false to forbid the edit
		
	static Poco::WebWidgets::JSDelegate createStartCellValueChangeServerCallback(const Table* pTable);
			/// Adds a javascript callback to inform the WebServer that the client has entered edit mode in the Table
			/// The Extjs handler offers a method signature of "function(obj)" where obj is a complex element 
			/// containing members (grid, record, column, row, value, cancel)!
		
	static Poco::WebWidgets::JSDelegate createCellSelectedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has selected a cell
		/// The Extjs handler offers a method signature of
		///    cellselect : ( SelectionModel this, Number rowIndex, Number colIndex )
		
	static Poco::WebWidgets::JSDelegate createRowSelectedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has selected a row
		/// The Extjs handler offers a method signature of
		///    rowselect : ( SelectionModel this, Number rowIndex, Ext.data.Record r )
		
	static Poco::WebWidgets::JSDelegate createCellClickedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has clicked on a cell in the Table
		/// Method signature is cellclick : ( Grid this, Number rowIndex, Number columnIndex, Ext.EventObject e )
		
	static Poco::WebWidgets::JSDelegate createRowClickedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has clicke don a row
		/// This event will only be added if the Table uses a Row selection model!
		/// Single cell selection will trigger an exception!
		/// Method signature is rowclick : ( Grid this, Number rowIndex, Ext.EventObject e )
		
	static Poco::WebWidgets::JSDelegate createBeforeCellClickedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has clicked on a cell in the Table
		/// Method signature is cellclick : ( Grid this, Number rowIndex, Number columnIndex, Ext.EventObject e )
		
	static Poco::WebWidgets::JSDelegate createBeforeRowClickedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has clicke don a row
		/// This event will only be added if the Table uses a Row selection model!
		/// Single cell selection will trigger an exception!
		/// Method signature is rowselect : ( SelectionModel this, Number rowIndex, Ext.Data.Record r )
		
	static Poco::WebWidgets::JSDelegate createAfterLoadServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has finished loading data
		/// Method signature is ( Store this, Ext.data.Record[] records, Object options )
		
	static Poco::WebWidgets::JSDelegate createRenderServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has finished rendering
		/// Method signature is ( Grid this, config)	
		
	static Poco::WebWidgets::JSDelegate createMouseUpServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has release a mouse button
		/// Method signature is ( Ext.EventObject e)
		
	static Poco::WebWidgets::JSDelegate createMouseDownServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has pressed a mouse button
		/// Method signature is ( Ext.EventObject e)
		
	static Poco::WebWidgets::JSDelegate createKeyDownServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has a key down
		/// Method signature is ( Ext.EventObject e)
		
	static Poco::WebWidgets::JSDelegate createKeyPressedServerCallback(const Table* pTable);
		/// Adds a javascript callback to inform the WebServer that the client has pressed a key
		/// Method signature is ( Ext.EventObject e)	

	static std::string createDnDGroupName(const Table* pTable);
		/// Creates a DND name for the table
		
protected:
	static void renderProperties(const Table* pTable, const RenderContext& context, std::ostream& ostr);
		/// Renders Table properties

	static void renderColumns(const Table* pTable, const RenderContext& context, std::ostream& ostr);
		/// Renders the columns of the table

	static void renderColumn(const Table* pTable, const TableColumn& tc, int idx, const RenderContext& context, std::ostream& ostr);
		/// Renders a single colum

	static void renderStore(const Table* pTable, std::ostream& ostr);
		/// Renders the data store of the table
		
	static void onBeforeLoad(void* pSender, Table::LoadData& ld);
};


} } } // namespace Poco::WebWidgets::ExtJS


#endif // ExtJS_TableRenderer_INCLUDED
