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
#ifndef SITUATION_TREE_NODE_H
#define SITUATION_TREE_NODE_H

#include "investigated_situation.h"
#include <string>
#include <map>
#include <set>

namespace FSM_framework
{
  class situation_tree_node: public investigated_situation
  {
  public:

    /**
       Constructor without predecessor information 
       @param p_situation : situation of node
    */
    situation_tree_node(FSM_interfaces::FSM_situation_if & p_situation);

    /**
       Constructor with predecessor information 
       @param p_situation : situation of node
       @param p_predecessor_id : id of predecessor situation
       @param p_predecessor_transtion : index of transition used to come from predecessor
    */
    situation_tree_node(FSM_interfaces::FSM_situation_if  & p_situation,
                        FSM_interfaces::FSM_situation_if & p_predecessor_id,
                        const FSM_interfaces::FSM_types::transition_index_t & p_predecessor_transition);

    /**
       Method to get the list of predecessors
    */
    const std::map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> & get_predecessor_situations(void)const;

  private:
    std::map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> m_successor_situations;
    std::map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> m_predecessor_situations;

  };
}
#endif // SITUATION_TREE_NODE_H 
//EOF
