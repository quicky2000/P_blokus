/*    This file is part of FSM_framework
      The aim of this software is to provided generic facilities for FSM analyzis
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "framework_controler.h"
#include "framework_base.h"
#include "algorithm_basic.h"
#include "algorithm_deep.h"
#include "algorithm_deep_first.h"
#include "algorithm_deep_first_weighted.h"
#include "algorithm_wide_first.h"
#include "algorithm_wide.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

namespace FSM_framework
{
  //---------------------------------------------------------------------------
  framework_base::framework_base
  (
   framework_controler *p_framework_controler
   ):
    m_framework_controler(p_framework_controler),
    m_fsm(NULL),
    m_fsm_ui(NULL),
    m_algorithm(NULL)
  {
    cout << "Framework_base 1.0" << endl ;

    assert(m_framework_controler);
    m_register_function_name = "register_fsm" ;

    // Registering algorithms
    algorithm_basic::register_algorithm(get_algorithm_factory());
    algorithm_deep::register_algorithm(get_algorithm_factory());
    algorithm_deep_first::register_algorithm(get_algorithm_factory());
    algorithm_deep_first_weighted::register_algorithm(get_algorithm_factory());
    algorithm_wide_first::register_algorithm(get_algorithm_factory());
    algorithm_wide::register_algorithm(get_algorithm_factory());
  }

  //---------------------------------------------------------------------------
  framework_base::~framework_base(void)
  {
    if(m_framework_controler != NULL)
      {
        // DO not delete framework controler because it has been created outside
        m_framework_controler = NULL;
      }
    if(m_fsm != NULL)
      {
        delete m_fsm;
        m_fsm = NULL;
      }
    if(m_fsm_ui != NULL)
      {
        delete m_fsm_ui;
        m_fsm_ui = NULL;
      }
    if(m_algorithm != NULL)
      {
        delete m_algorithm;
        m_algorithm = NULL;
      }
    closeAllLibrary();
  }

  //---------------------------------------------------------------------------
  void framework_base::run(void)
  {
    assert(m_algorithm != NULL);
    m_algorithm->set_fsm(m_fsm);
    m_algorithm->set_fsm_ui(m_fsm_ui);
    m_algorithm->run();
  }

  //---------------------------------------------------------------------------
  void framework_base::loadLibrary(string p_library_name) throw (quicky_exception::quicky_logic_exception)
  {
    // Check that library is not already open
    if(!m_library_handles.count(p_library_name))
      {
        // Opening shared library
#ifndef _WIN32
        void* l_library_handle = dlopen (p_library_name.c_str(), RTLD_LAZY);
#else

#ifndef UNICODE
        HMODULE l_library_handle = dlopen (p_library_name.c_str());
#else
        unsigned int l_size = MultiByteToWideChar(CP_ACP, 0, p_library_name.c_str(), -1, NULL, 0);
        WCHAR *l_buf = new WCHAR[l_size];
        MultiByteToWideChar(CP_ACP, 0,p_library_name.c_str(), -1, l_buf, l_size);
        HMODULE l_library_handle = dlopen (l_buf);
#endif
#endif

        if (l_library_handle == NULL)
          {
		  
            stringstream l_stream;
            l_stream << "Problem when opening library \"" << p_library_name << "\": " << dlerror() ;
            throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
          }

#ifndef _WIN32
        m_library_handles.insert(map<string,void*>::value_type(p_library_name,l_library_handle));
#else
        m_library_handles.insert(map<string,HMODULE>::value_type(p_library_name,l_library_handle));
#endif

        // Searching FSM_creator creator function
        void (*l_func)(map<string, FSM_interfaces::FSM_creator_t>*);
	
        *(void **)(&l_func) = dlsym(l_library_handle, m_register_function_name.c_str());
        if (l_func == NULL)
          {
            stringstream l_stream;
            l_stream << "Unable to find symbol \"" << m_register_function_name << "\" " << dlerror();
            dlclose(l_library_handle);
            throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
          }
	
        // Exécution de la fonction "func"
        l_func(&m_fsm_factory);
	  
        // Searchign FSM_UI_creator creator function
        void (*l_func_ui)(map<string, FSM_interfaces::FSM_UI_creator_t>*);
	
        *(void**)(&l_func_ui) =  dlsym(l_library_handle, "register_fsm_ui");
        if (l_func_ui == NULL)
          {
            stringstream l_stream;
            l_stream << "Unable to find symbol \"register_fsm_ui\" " << dlerror();
            dlclose(l_library_handle);
            throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);			
          }
	
        // Exécution de la fonction "func"
        l_func_ui(&m_fsm_ui_factory);
      }
    else
      {
        m_framework_controler->display_warning_message("library \"" + p_library_name + "\" was already loaded");
      }
  }

  //---------------------------------------------------------------------------
  vector<string> framework_base::get_fsm_list(void)
  {
    vector<string> l_result;
    map<string,FSM_interfaces::FSM_creator_t>::iterator l_iter = m_fsm_factory.begin();
    map<string,FSM_interfaces::FSM_creator_t>::iterator l_iter_end = m_fsm_factory.end();

    while(l_iter != l_iter_end)
      {
        l_result.push_back(l_iter->first);
        l_iter++;
      }
    return l_result;
  }

  //---------------------------------------------------------------------------
  vector<string> framework_base::get_fsm_ui_list(void)
  {
    vector<string> l_result;
    map<string,FSM_interfaces::FSM_UI_creator_t>::iterator l_iter = m_fsm_ui_factory.begin();
    map<string,FSM_interfaces::FSM_UI_creator_t>::iterator l_iter_end = m_fsm_ui_factory.end();

    while(l_iter != l_iter_end)
      {
        l_result.push_back(l_iter->first);
        l_iter++;
      }
    return l_result;
  }

  //---------------------------------------------------------------------------
  vector<string> framework_base::get_algorithm_list(void)
  {
    vector<string> l_result;
    map<string,FSM_framework_algorithm_creator_t>::iterator l_iter = m_algorithm_factory.begin();
    map<string,FSM_framework_algorithm_creator_t>::iterator l_iter_end = m_algorithm_factory.end();

    while(l_iter != l_iter_end)
      {
        l_result.push_back(l_iter->first);
        l_iter++;
      }
    return l_result;
  }

  //---------------------------------------------------------------------------
  void framework_base::select_fsm(string p_fsm_name)
  {
    if(is_fsmLoaded(p_fsm_name))
      {
        this->set_fsm(get_fsm_creator(p_fsm_name)());
      }
    else
      {
        m_framework_controler->display_warning_message("WARNING : FSM \"" + p_fsm_name + "\" is not available");
      }
  }

  //---------------------------------------------------------------------------
  void framework_base::select_fsm_ui(string p_fsm_ui_name)
  {
    if(is_fsm_uiLoaded(p_fsm_ui_name))
      {
        this->set_fsm_ui(get_fsm_ui_creator(p_fsm_ui_name)());
      }
    else
      {
        m_framework_controler->display_warning_message("WARNING : FSM_UI \"" + p_fsm_ui_name+ "\" is not available");
      }
  }

  //---------------------------------------------------------------------------
  void framework_base::select_algorithm(string p_algorithm_name)
  {
    if(is_algorithmLoaded(p_algorithm_name))
      {
        this->set_algorithm(get_algorithm_creator(p_algorithm_name)());
      }
    else
      {
        m_framework_controler->display_warning_message("WARNING : FSM \"" + p_algorithm_name + "\" is not available");
      }
  }

  //---------------------------------------------------------------------------
  bool framework_base::is_fsmLoaded(string p_fsm_name)
  {
    return m_fsm_factory.count(p_fsm_name);
  }

  //---------------------------------------------------------------------------
  bool framework_base::is_fsm_uiLoaded(string p_fsm_ui_name)
  {
    return m_fsm_ui_factory.count(p_fsm_ui_name);
  }

  //---------------------------------------------------------------------------
  bool framework_base::is_algorithmLoaded(string p_algorithm_name)
  {
    return m_algorithm_factory.count(p_algorithm_name);
  }

  //---------------------------------------------------------------------------
  FSM_interfaces::FSM_creator_t framework_base::get_fsm_creator(string p_fsm_name)
  {
    if(m_fsm_factory.count(p_fsm_name) == 0)
      {
        m_framework_controler->display_error_message("Framework ERROR : no fsm creator for fsm of type \"" + p_fsm_name + "\"");
        exit(-1);
      }
    return m_fsm_factory[p_fsm_name];
  }

  //---------------------------------------------------------------------------
  FSM_interfaces::FSM_UI_creator_t framework_base::get_fsm_ui_creator(string p_fsm_name)
  {
    if(m_fsm_ui_factory.count(p_fsm_name) == 0)
      {
        m_framework_controler->display_error_message("Framework ERROR : no fsm_ui creator for fsm of type \""+ p_fsm_name + "\"");
        exit(-1);
      }
    return m_fsm_ui_factory[p_fsm_name];
  }

  //---------------------------------------------------------------------------
  FSM_framework_algorithm_creator_t framework_base::get_algorithm_creator(string p_algorithm_name)
  {
    if(m_algorithm_factory.count(p_algorithm_name) == 0)
      {
        m_framework_controler->display_error_message("Framework ERROR : no algorithm creator for algorithm of type \"" + p_algorithm_name + "\"" );
        exit(-1);
      }
    return m_algorithm_factory[p_algorithm_name];
  }

  //---------------------------------------------------------------------------
  map<string,FSM_framework_algorithm_creator_t >& framework_base::get_algorithm_factory(void)
  {
    return m_algorithm_factory;
  }

  //---------------------------------------------------------------------------
  map<string,FSM_framework_algorithm_UI_creator_t >& framework_base::get_algorithmUi_factory(void)
  {
    return m_algorithm_ui_factory;
  }

  //---------------------------------------------------------------------------
  FSM_interfaces::FSM_if* framework_base::get_fsm(void)
  {
    return m_fsm;
  }

  //---------------------------------------------------------------------------
  framework_algorithm_if* framework_base::get_algorithm(void)
  {
    return m_algorithm;
  }

  //---------------------------------------------------------------------------
  void framework_base::set_fsm(FSM_interfaces::FSM_if  & p_fsm)
  {
    m_fsm = & p_fsm;
  }

  //---------------------------------------------------------------------------
  void framework_base::set_fsm_ui(FSM_interfaces::FSM_UI_if & p_fsm_ui)
  {
    m_fsm_ui = & p_fsm_ui;
  }

  //---------------------------------------------------------------------------
  void framework_base::set_algorithm(framework_algorithm_if  & p_algorithm)
  {
    m_algorithm = & p_algorithm;
  }

  //---------------------------------------------------------------------------
  void framework_base::register_algorithmUi_creator(string p_name, FSM_framework_algorithm_UI_creator_t p_creator)
  {
    if(m_algorithm_ui_factory.count(p_name) == 0)
      {
        m_algorithm_ui_factory.insert(map<string,FSM_framework_algorithm_UI_creator_t >::value_type(p_name,p_creator));
      }
    else
      {
        m_framework_controler->display_warning_message("WARNING : algorithm UI creator \""+p_name+"\" is already registered");
      }
  }

  //---------------------------------------------------------------------------
  void framework_base::closeLibrary(string p_library_name)
  {
    if(m_library_handles.count(p_library_name))
      {
        dlclose(m_library_handles[p_library_name]);
      }
    else
      {
        m_framework_controler->display_warning_message("library \"" + p_library_name + "\" was not loaded");
      }
  }

  //---------------------------------------------------------------------------
  void framework_base::closeAllLibrary(void)
  {
#ifndef _WIN32
    map<string,void*>::iterator l_iter = m_library_handles.begin();
    map<string,void*>::iterator l_iter_end = m_library_handles.end();
#else
    map<string,HMODULE>::iterator l_iter = m_library_handles.begin();
    map<string,HMODULE>::iterator l_iter_end = m_library_handles.end();
#endif

    while(l_iter != l_iter_end)
      {
        dlclose(l_iter->second);      
        ++l_iter;
      }
  }

  string framework_base::m_register_function_name = "Undefined";
}
//EOF
