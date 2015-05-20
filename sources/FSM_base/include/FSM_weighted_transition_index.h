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
#ifndef FSM_WEIGHTED_TRANSITION_INDEX_H
#define FSM_WEIGHTED_TRANSITION_INDEX_H

#include "FSM_weighted_transition_index_if.h"

#include <string>

namespace FSM_base
{
  class FSM_weighted_transition_index:public FSM_interfaces::FSM_weighted_transition_index_if
  {
  private:
    typedef FSM_interfaces::FSM_types::transition_index_t transition_index_t;
    typedef FSM_interfaces::FSM_types::transition_weight_t transition_weight_t;
  public:
    // Constructor
    FSM_weighted_transition_index(const transition_index_t & p_transition_index,
                                  const transition_weight_t & p_weight=0);
    
    // Methods inhereited from interface
    const transition_index_t & get_transition_index(void)const;
    const transition_weight_t & get_weight(void)const;
    const std::string get_string(void)const;
    void get_string(std::string &)const;
    bool operator<(const FSM_weighted_transition_index_if & p_object2)const;
    
  private:
    const transition_index_t m_transition_index;
    const transition_weight_t m_weight;
  };
}

#endif /* FSM_WEIGHTED_TRANSITION_INDEX_H */
//EOF
