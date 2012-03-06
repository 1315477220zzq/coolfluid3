// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef cf3_Python_ScriptEngine_hpp
#define cf3_Python_ScriptEngine_hpp

////////////////////////////////////////////////////////////////////////////////

#if MAC_FRAMEWORK_PYTHON
#include <Python/Python.h>
#else
#include <Python.h>
#endif
//python Py_ssize_t backward compatibility

#if (PY_VERSION_HEX < 0x02050000)
    typedef int Py_ssize_t;
#endif


////////////////////////////////////////////////////////////////////////////////


#include "common/Component.hpp"

#include "python/LibPython.hpp"

#include "common/PE/Manager.hpp"

#include "common/CommonAPI.hpp"

#include <frameobject.h>

namespace cf3 {
namespace python {

////////////////////////////////////////////////////////////////////////////////

/// @brief python tracing function, used to
int python_trace(PyObject *obj, PyFrameObject *frame, int what, PyObject *arg);

/// @brief Threaded c function, used to contain the PyEval_CodeEval
void python_execute_function();
/// @brief Threaded c function, used to stop python execution with mutex
void python_stop_function();

/// @brief Executes python scripts passed as a string
///
/// Exposes an execute_script signal, taking as single argument the string containing the python script to run
/// @author Bart Janssens
class Python_API ScriptEngine : public common::Component {

public: // typedefs

  /// pointer to this type



public: // functions

  /// Contructor
  /// @param name of the component
  ScriptEngine ( const std::string& name );

  /// Virtual destructor
  virtual ~ScriptEngine();

  /// Get the class name
  static std::string type_name () { return "ScriptEngine"; }

  /// Execute the script passed as a string
  void execute_script(std::string script,int code_fragment);

  /// Signal to execute a script
  void signal_execute_script(common::SignalArgs& node);

  /// Signal to change the current debugging state
  void signal_change_debug_state(common::SignalArgs& node);

  /// Signal to retrieve the completion list
  void signal_completion(common::SignalArgs& node);

  /// Called by the trace function when a new line is reached
  int new_line_reached(int code_fragment,int line_number);

  void check_python_change();

private:
  enum debug_command {
      INVALID=-1,
      BREAK=0,
      CONTINUE=1,
      LINE_BY_LINE_EXECUTION=2,
      NORMAL_EXECUTION=3
  };

  /// Signature for the execute_script signal
  void signature_execute_script(common::SignalArgs& node);

  void emit_output(std::string output);

  void emit_debug_trace(int fragment,int line);

  void emit_completion_list();

  bool check_scope_difference(PyObject* dict,std::vector<PyObject*>* diff);

  void read_objects(PyObject* obj,std::string obj_name);

  void flush_python_stdout();

  std::string current_instruction;
  bool new_command;
  Handle< common::PE::Manager > m_manager;
  std::vector<PyObject*> local_scope_diff;
  std::vector<PyObject*> global_scope_diff;
  std::vector<std::string> completion_word_list;
  debug_command interpreter_mode;

  static int python_close;
  int break_fragment;
  int break_line;
  bool stoped;
}; // ScriptEngine

////////////////////////////////////////////////////////////////////////////////

} // python
} // cf3

////////////////////////////////////////////////////////////////////////////////

#endif // cf3_Python_ScriptEngine_hpp
