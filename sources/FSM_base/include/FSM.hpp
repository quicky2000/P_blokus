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
#include "FSM_weighted_transition_index.h"

#include <cstdlib>
#include <iostream>

namespace FSM_base
{
  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  FSM<T_SITUATION,T_TRANSITION>::FSM(const std::string & p_name,
				     FSM_motor<T_SITUATION,T_TRANSITION> & p_motor,
				     FSM_situation_analyzer<T_SITUATION,T_TRANSITION> & p_analyzer
				     ):
    m_name(p_name),
    m_situation(NULL),
    m_motor(p_motor),
    m_analyzer(p_analyzer)
  {
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  FSM<T_SITUATION,T_TRANSITION>::~FSM(void)
  {
    delete & m_motor;
    delete & m_analyzer;
    if(m_situation)
      {
	// Dont delete the situation as it is managed externally
	m_situation = NULL;
      }
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  typename FSM<T_SITUATION,T_TRANSITION>::FSM_situation_if & FSM<T_SITUATION,T_TRANSITION>::get_current_situation(void)const
  {
    assert(m_situation);
    return *m_situation;
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  void FSM<T_SITUATION,T_TRANSITION>::set_current_situation
  (
   FSM_situation_if & p_situation
   )
  {
    m_situation = dynamic_cast<T_SITUATION*>(&p_situation);
    if(m_situation == NULL)
      {
	std::cout << "FSM<T_SITUATION,T_TRANSITION>::" << __FUNCTION__ << " ERROR : bad situation type" << std::endl ;
	exit(-1);
      }
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  void FSM<T_SITUATION,T_TRANSITION>::compute_transition_weights(std::vector<FSM_weighted_transition_index_if*> &p_vector)const
  {
    std::cout << "Default implementation of " << __FUNCTION__ << std::endl ;
    transition_index_t l_nb_transition = this->get_situation().get_context()->get_nb_transitions();
    for(transition_index_t l_index=0;l_index<l_nb_transition; ++l_index)
      {
	p_vector.push_back(new FSM_weighted_transition_index(l_index));
      }
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  void FSM<T_SITUATION,T_TRANSITION>::compute_transitions(void)
  {
    assert(m_situation);
    m_analyzer.compute_transitions(*m_situation);
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  void FSM<T_SITUATION,T_TRANSITION>::select_transition
  (
   const transition_index_t & p_transition_index
   )
  {
    const T_TRANSITION & l_selected_transition = this->get_situation().get_context()->get_specific_transition(p_transition_index);
#ifdef FSM_VERBOSE
    std::cout << l_selected_transition.to_string() << std::endl ;
#endif // FSM_VERBOSE
    this->set_situation(m_motor.run(this->get_situation(),l_selected_transition));
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  const std::string & FSM<T_SITUATION,T_TRANSITION>::get_fsm_name(void)const
  {
    return m_name;
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  void FSM<T_SITUATION,T_TRANSITION>::set_situation
  (
   T_SITUATION & p_situation
   )
  {
    m_situation = & p_situation;		
  }

  //-----------------------------------------------------------------------------
  template <class T_SITUATION,class T_TRANSITION>
  T_SITUATION & FSM<T_SITUATION,T_TRANSITION>::get_situation(void)const
  {
    assert(m_situation);
    return * m_situation;		
  }

}
//EOF
