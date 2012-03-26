// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.


#ifndef cf3_ui_core_NScriptEngine_hpp
#define cf3_ui_core_NScriptEngine_hpp


//////////////////////////////////////////////////////////////////////////////

#include <QHash>

#include "ui/core/CNode.hpp"

class QString;

//////////////////////////////////////////////////////////////////////////////

namespace cf3 {

namespace ui {
namespace core {

/////////////////////////////////////////////////////////////////////////////

/// @brief Log component
/// @author Bolsee Vivian.

class Core_API NScriptEngine :
    public QObject,
    public CNode
{
  Q_OBJECT
public:
  enum debug_command {
    INVALID=-1,
    STOP=0,
    CONTINUE=1,
    LINE_BY_LINE_EXECUTION=2,
    NORMAL_EXECUTION=3,
    BREAK=4,
    TOGGLE_BREAK_POINT=5
  };

  NScriptEngine();


  /// @brief Gives the text to put on a tool tip
  /// @return The name of the class.
  virtual QString tool_tip() const;

  static Handle<NScriptEngine> global();

  void execute_line( const QString & line, int fragment_number, QVector<int> break_points);

  void emit_debug_command(debug_command command,int fragment=0,int line=0);

  void request_documentation(QString &doc);

  /// @brief Boost slot called when python console output are sent from the server
  /// @param node Signal node
  void signal_output(common::SignalArgs & node);

  /// @brief Boost slot called when the server send new documentation about an expression
  /// @param node Signal node
  void signal_documentation(common::SignalArgs & node);

  /// @brief Boost slot called when the server send his completion list
  /// @param node Signal node
  void signal_completion(common::SignalArgs & node);

  /// @brief Boost slot called when the server send debugging information
  /// @param node Signal node
  void signal_debug_trace(common::SignalArgs & node);

  void append_command_to_python_console(std::string & command);
public slots:
  void client_connected();

signals:

  /// @brief Signal emitted when the server send the new console output.
  /// @param output Output message
  void new_output(const QString & output);

  /// @brief Signal emitted when the server find new entries in the python scope.
  /// @param word_list scope entry name
  /// @param doc_list entry documentation (__doc__ membre)
  void completion_list_received(const QStringList & add,const QStringList & sub);

  void debug_trace_received(int fragment,int line);

  void documentation_received(const QString & documentation);

  void execute_code_request(QString,bool,QVector<int>&);

protected:

  /// Disables the local signals that need to.
  /// @param localSignals Map of local signals. All values are set to true
  /// by default.
  virtual void disable_local_signals(QMap<QString, bool> & localSignals) const {}
private:
  QStringList std_vector_to_QStringList(std::vector<std::string> vector);
  bool connected;
}; // class NScriptEngine

///////////////////////////////////////////////////////////////////////////

} // Core
} // ui
} // cf3

/////////////////////////////////////////////////////////////////////////////


#endif // cf3_ui_core_NScriptEngine_hpp
