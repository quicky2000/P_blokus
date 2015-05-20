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
#ifndef INVESTIGATED_SITUATION_H
#define INVESTIGATED_SITUATION_H

#include "FSM_types.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include <set>

namespace FSM_framework
{
  class investigated_situation
  {
  public:

    /**
       Constructor without predecessor information 
       @param p_situation : situation of node
    */
    inline investigated_situation(FSM_interfaces::FSM_situation_if & p_situation);

    /**
       Method to access to situation contained in the node
    */
    inline FSM_interfaces::FSM_situation_if & get_situation(void)const;

    /**
       Method to get the list of unexplored transitions
       @return list of unexplored transitions
    */
    inline const std::set<FSM_interfaces::FSM_types::transition_index_t> & get_unexplored_transitions(void)const;

    /**
       Method to indicate that a transition is explored
       @param p_transition index of transition to mark explored
    */
    inline void set_transition_explored(const FSM_interfaces::FSM_types::transition_index_t & p_transition_id);

    /**
       Method to indicate that all transition are explored
    */
    inline void set_all_transition_explored(void);
  private:
    /**
       Method to initalize unexplored transition list
    */
    inline void initialize_unexplored_transition(void);

    FSM_interfaces::FSM_situation_if & m_situation;
    std::set<FSM_interfaces::FSM_types::transition_index_t> m_unexplored_transitions;
  };

  //------------------------------------------------------------------------------
  investigated_situation::investigated_situation(FSM_interfaces::FSM_situation_if & p_situation):
    m_situation(p_situation)
  {
    initialize_unexplored_transition();
  }

  //------------------------------------------------------------------------------
    const std::set<FSM_interfaces::FSM_types::transition_index_t> & investigated_situation::get_unexplored_transitions(void)const
  {
    return m_unexplored_transitions;
  }

  //------------------------------------------------------------------------------
  FSM_interfaces::FSM_situation_if & investigated_situation::get_situation(void)const
  {
    return m_situation;
  }

  //------------------------------------------------------------------------------
  void investigated_situation::set_all_transition_explored(void)
  {
    m_unexplored_transitions.clear();
  }

  //------------------------------------------------------------------------------
  void investigated_situation::set_transition_explored(const FSM_interfaces::FSM_types::transition_index_t & p_transition_id)
  {
    m_unexplored_transitions.erase(p_transition_id);
  }

  //------------------------------------------------------------------------------
  void investigated_situation::initialize_unexplored_transition(void)
  {
    // Set all transition as unexplored
    if( m_situation.get_current_context()->transitions_computed())
      {
        FSM_interfaces::FSM_types::transition_index_t l_nb_transition = m_situation.get_current_context()->get_nb_transitions();
        for(FSM_interfaces::FSM_types::transition_index_t l_transition_index = 0;
            l_transition_index < l_nb_transition ; 
            ++l_transition_index)
          {
            m_unexplored_transitions.insert(l_transition_index);
          }
      }
  
  }


}

#endif // INVESTIGATED_SITUATION_H 
//EOF
