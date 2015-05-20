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
#include "situation_tree_node.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"

#include <assert.h>
using namespace std;

namespace FSM_framework
{
  //------------------------------------------------------------------------------
  situation_tree_node::situation_tree_node(FSM_interfaces::FSM_situation_if & p_situation):
    investigated_situation(p_situation)
  {
  }

  //------------------------------------------------------------------------------
  situation_tree_node::situation_tree_node(
                                           FSM_interfaces::FSM_situation_if & p_situation,
                                           FSM_interfaces::FSM_situation_if & p_predecessor_id,
                                           const FSM_interfaces::FSM_types::transition_index_t & p_predecessor_transition):
    investigated_situation(p_situation)
  {
    m_predecessor_situations.insert( map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &>::value_type(p_predecessor_transition,p_predecessor_id));
  }

  //------------------------------------------------------------------------------
  const map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> & situation_tree_node::get_predecessor_situations(void)const
  {
    return m_predecessor_situations;
  }

}
//EOF
