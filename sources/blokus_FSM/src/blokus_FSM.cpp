/*    This file is part of blokus_FSM
      Copyright (C) 2014  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include "blokus_FSM.h"
#include "blokus_motor.h"
#include "blokus_situation_analyzer.h"

#include <iostream>

using namespace std;

namespace blokus
{
  //-----------------------------------------------------------------------------
  blokus_FSM::blokus_FSM(void):
    FSM<blokus_situation,blokus_transition>("blokus_FSM",*(new blokus_motor()), *(new blokus_situation_analyzer()))
  {
    set_situation(*(new blokus_situation()));
  }
  
  //-----------------------------------------------------------------------------
  void blokus_FSM::configure(void)
  {
  }
  
  //-----------------------------------------------------------------------------
  const std::string & blokus_FSM::get_class_name(void)const
  {
    return m_class_name;
  }
  
  //-----------------------------------------------------------------------------
  FSM_interfaces::FSM_if & create_blokus_FSM(void)
  {
    return *(new blokus_FSM());
  }

  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_fsm(map<std::string,FSM_interfaces::FSM_creator_t> & p_factory)
    {
      register_fsm("blokus_FSM",create_blokus_FSM,p_factory);
    }
  }
  const std::string blokus_FSM::m_class_name = "blokus";
}
