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
#ifndef FSM_WEIGHTED_TRANSITION_INDEX_IF_H
#define FSM_WEIGHTED_TRANSITION_INDEX_IF_H

#include "FSM_types.h"
#include <string>

namespace FSM_interfaces
{
  class FSM_weighted_transition_index_if
  {
  public:
    virtual const FSM_types::transition_index_t & get_transition_index(void)const=0;
    virtual const FSM_types::transition_weight_t & get_weight(void)const=0;
    virtual const std::string get_string(void)const=0;
    virtual void get_string(std::string &)const=0;
    virtual bool operator<(const FSM_weighted_transition_index_if & p_object2)const=0;
    
    inline virtual ~FSM_weighted_transition_index_if(void){}
    
  private:
    
  };
}
#endif /* FSM_WEIGHTED_TRANSITION_INDEX_IF_H */
//EOF
