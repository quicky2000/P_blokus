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
#ifndef _FSM_CONTEXT_IF_
#define _FSM_CONTEXT_IF_

#include "FSM_types.h"
#include <string>
#include <vector>

namespace FSM_interfaces
{
  class FSM_transition_if;

  class FSM_context_if
  {
  public:
    // Methods to implement
    virtual const std::string to_string(void)const=0;
    virtual void to_string(std::string &)const=0;
    virtual const FSM_types::transition_index_t get_nb_transitions(void)const=0;
    virtual const FSM_transition_if & get_transition(const FSM_types::transition_index_t &)const=0;
    virtual bool transitions_computed(void)const=0;

    // Virtual destructor
    inline ~FSM_context_if(void){};
  };
}
#endif
//EOF
