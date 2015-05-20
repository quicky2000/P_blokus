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
#include <iostream>
#include <cstdlib>

namespace FSM_base
{
  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  FSM_context<T_TRANSITION>::~FSM_context(void)
  {
    if(m_transitions)
      {
	for(typename std::vector<const T_TRANSITION *>::const_iterator l_iter =  m_transitions->begin();
	    m_transitions->end() != l_iter;
	    ++l_iter)
	  {
	    delete *l_iter;
	  }
	delete m_transitions;
	m_transitions = NULL;
      }
  }

  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  FSM_context<T_TRANSITION>::FSM_context(void):
    m_transitions(NULL)
  {
  }

  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  const typename FSM_context<T_TRANSITION>::transition_index_t FSM_context<T_TRANSITION>::get_nb_transitions(void)const
  {
    assert(m_transitions);
    return m_transitions->size();
  }

  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  const typename FSM_context<T_TRANSITION>::FSM_transition_if & FSM_context<T_TRANSITION>::get_transition(const transition_index_t & p_index)const
  {
    assert(m_transitions);
    if(p_index > m_transitions->size())
      {
        std::cout << "FSM error : asked transition doesnt exist" << std::endl ;
        exit(-1);
      }
    return *((*m_transitions)[p_index]);
  }

  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  const T_TRANSITION & FSM_context<T_TRANSITION>::get_specific_transition(const transition_index_t & p_index)const
  {
    assert(m_transitions);
    if(p_index > m_transitions->size())
      {
        std::cout << "FSM error : asked transition doesnt exist" << std::endl ;
        exit(-1);
      }
    return *((*m_transitions)[p_index]);
  }

  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  void FSM_context<T_TRANSITION>::set_transitions(const std::vector<const T_TRANSITION *> &p_transitions)
  {
    m_transitions = & p_transitions;
  }

  //-----------------------------------------------------------------------------
  template <class T_TRANSITION>
  bool FSM_context<T_TRANSITION>::transitions_computed(void)const
  {
    return m_transitions;
  }
}
//EOF
