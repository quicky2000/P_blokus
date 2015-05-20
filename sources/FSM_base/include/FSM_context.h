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
#ifndef FSM_CONTEXT
#define FSM_CONTEXT

#include "FSM_context_if.h"

#include <vector>
#include <assert.h>

namespace FSM_base
{
  template <class T_TRANSITION> class FSM_context:public FSM_interfaces::FSM_context_if
  {
  private:
    typedef FSM_interfaces::FSM_types::transition_index_t transition_index_t;
    typedef FSM_interfaces::FSM_transition_if FSM_transition_if;
  public:
    // Constructor and destructors
    FSM_context(void);
    virtual ~FSM_context(void);

    // Methods inherited from interface
    const transition_index_t get_nb_transitions(void)const;
    const FSM_transition_if & get_transition(const transition_index_t & p_index)const;
    bool transitions_computed(void)const;

    // Specific method
    const T_TRANSITION & get_specific_transition(const transition_index_t & p_index)const;
    void set_transitions(const std::vector<const T_TRANSITION *> & p_transitions);

  private:
    const std::vector<const T_TRANSITION *> * m_transitions;
  };

}

#include "FSM_context.hpp"

#endif // FSM_CONTEXT
//EOF
