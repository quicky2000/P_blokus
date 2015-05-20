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
#ifndef FSM_UI_H
#define FSM_UI_H

#include "FSM_UI_if.h"
#include "assert.h"

namespace FSM_base
{
  template <class T_SITUATION> class FSM_UI:public FSM_interfaces::FSM_UI_if
  {
  private:
    typedef FSM_interfaces::FSM_situation_if FSM_situation_if;
  public:
    // Constructor and destructors
    virtual ~FSM_UI(void);
    
    // Methods inherited from interface
    virtual void display_situation(const FSM_situation_if & p_situation);
    
  private:
    virtual void display_specific_situation(const T_SITUATION & p_situation)=0;
  };
}
#include "FSM_UI.hpp"

#endif // FSM_UI
//EOF
