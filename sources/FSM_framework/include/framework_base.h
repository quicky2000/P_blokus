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
#ifndef FRAMEWORK_BASE_H
#define FRAMEWORK_BASE_H

#include "framework_algorithm_if.h"
#include "framework_algorithm_UI_if.h"
#include "quicky_exception.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include <vector>
#include <map>
#include <string>

// Define for dynamic libraries management
#ifdef _WIN32
#include <windows.h>
#define dlopen LoadLibrary
#define dlerror GetLastError
#define dlclose FreeLibrary
#define dlsym GetProcAddress
#else
#include <dlfcn.h>
#endif

namespace FSM_framework
{
  class framework_controler;

  class framework_base
  {
  public:
    // Constructors/Destructors
    framework_base(framework_controler *p_framework_controler);
    ~framework_base(void);

    /***********/
    /* Methods */
    /***********/
    void run(void);
    void loadLibrary(std::string p_library_name) throw (quicky_exception::quicky_logic_exception);

    std::vector<std::string> get_fsm_list(void);
    std::vector<std::string> get_fsm_ui_list(void);
    std::vector<std::string> get_algorithm_list(void);

    void select_fsm(std::string p_FSM_name);
    void select_fsm_ui(std::string p_FSM_UI_name);
    void select_algorithm(std::string p_algorithm_name);

  protected:
    /***********/
    /* Methods */
    /***********/
    bool is_fsmLoaded(std::string p_fsm_name);
    bool is_fsm_uiLoaded(std::string p_FSM_UI_name);
    bool is_algorithmLoaded(std::string p_algorithm_name);

    FSM_interfaces::FSM_creator_t get_fsm_creator(std::string p_fsm_name);
    FSM_interfaces::FSM_UI_creator_t get_fsm_ui_creator(std::string p_FSM_UI_name);
    FSM_framework_algorithm_creator_t get_algorithm_creator(std::string p_algorithm_name);
	
    std::map<std::string,FSM_framework_algorithm_creator_t> & get_algorithm_factory(void);
    std::map<std::string,FSM_framework_algorithm_UI_creator_t> & get_algorithmUi_factory(void);

    FSM_interfaces::FSM_if* get_fsm(void);
    framework_algorithm_if* get_algorithm(void);

    void set_fsm(FSM_interfaces::FSM_if & p_fsm);
    void set_fsm_ui(FSM_interfaces::FSM_UI_if & p_fsm_ui);
    void set_algorithm(framework_algorithm_if & p_algorithm);

    void register_algorithmUi_creator(std::string p_name,FSM_framework_algorithm_UI_creator_t p_creator);

  private:
    /***********/
    /* Methods */
    /***********/
    void closeLibrary(std::string p_library_name);
    void closeAllLibrary(void);

    /***********/
    /* Members */
    /***********/
    framework_controler *m_framework_controler;

#ifndef _WIN32
    std::map<std::string,void*> m_library_handles;
#else
    std::map<std::string,HMODULE> m_library_handles;
#endif
  
    // FSM triplet instance
    FSM_interfaces::FSM_if *m_fsm;
    FSM_interfaces::FSM_UI_if *m_fsm_ui;
    framework_algorithm_if * m_algorithm;

    //Factories
    std::map<std::string,FSM_interfaces::FSM_creator_t> m_fsm_factory;
    std::map<std::string,FSM_interfaces::FSM_UI_creator_t > m_fsm_ui_factory;
    std::map<std::string,FSM_framework_algorithm_creator_t > m_algorithm_factory;
    std::map<std::string,FSM_framework_algorithm_UI_creator_t > m_algorithm_ui_factory;

    static std::string m_register_function_name;
  };
}
#endif // FRAMEWORK_BASE_H
//EOF
