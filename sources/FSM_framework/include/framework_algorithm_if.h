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
#ifndef FRAMEWORK_ALGORITHM_IF_H
#define FRAMEWORK_ALGORITHM_IF_H

#include <string>
#include <map>

namespace FSM_interfaces
{
  class FSM_if;
  class FSM_UI_if;
}

namespace FSM_framework
{
  class framework_algorithm_if
  {
  public:
    // Constructor and destructor
    framework_algorithm_if(void);
    virtual ~framework_algorithm_if(void);
    
    // Methods to implement
    virtual void run(void)=0;
    virtual const std::string & get_string(void)const=0;

    // Accessors
    void set_fsm(FSM_interfaces::FSM_if *p_FSM);
    void set_fsm_ui(FSM_interfaces::FSM_UI_if *p_FSM_UI);
    FSM_interfaces::FSM_if* get_fsm(void);
    const FSM_interfaces::FSM_if * const get_fsm(void)const;
    FSM_interfaces::FSM_UI_if* get_fsm_ui(void);

  private:
    FSM_interfaces::FSM_if * m_fsm;
    FSM_interfaces::FSM_UI_if *m_fsm_ui;
  }
  ;

  typedef framework_algorithm_if & (*FSM_framework_algorithm_creator_t)(void);
  
  void register_framework_algorithm(const std::string & p_algorithm_name,
				    FSM_framework_algorithm_creator_t,
				    std::map<std::string,FSM_framework_algorithm_creator_t> &p_factory);
}
#endif // FRAMEWORK_ALGORITHM_IF_H 
//EOF
