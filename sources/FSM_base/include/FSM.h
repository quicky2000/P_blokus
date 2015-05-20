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
#ifndef FSM_H
#define FSM_H

#include "FSM_if.h"
#include "FSM_motor.h"
#include "FSM_situation_analyzer.h"
#include <assert.h>

namespace FSM_base
{
  template <class T_SITUATION,class T_TRANSITION> class FSM: public FSM_interfaces::FSM_if
  {
  private:
    typedef FSM_interfaces::FSM_situation_if FSM_situation_if;
    typedef FSM_interfaces::FSM_types::transition_index_t transition_index_t;
    typedef FSM_interfaces::FSM_weighted_transition_index_if FSM_weighted_transition_index_if;
  public:
    // Constructors and destructors
    FSM(const std::string & p_FSM_name,
	FSM_motor<T_SITUATION,T_TRANSITION> & p_motor,
	FSM_situation_analyzer<T_SITUATION,T_TRANSITION> & p_analyzer);
    virtual ~FSM(void);

    // Methods inherited from interface class
    FSM_situation_if & get_current_situation(void)const;
    void set_current_situation(FSM_situation_if & p_situation);
    void select_transition(const transition_index_t & p_transition_index);
    void compute_transitions(void);
    virtual void configure(void)=0;
    //TO DELETE   virtual const std::string & get_class_name(void)const=0;
    const std::string & get_fsm_name(void)const;
    void compute_transition_weights(std::vector<FSM_weighted_transition_index_if*> &p_vector)const;

    // Specific methods
    void set_situation(T_SITUATION  & p_situation);
    T_SITUATION & get_situation(void)const;

  private:
    std::string m_name;
    T_SITUATION * m_situation;
    FSM_motor<T_SITUATION,T_TRANSITION> & m_motor;
    FSM_situation_analyzer<T_SITUATION,T_TRANSITION> & m_analyzer;
  };
}

#include "FSM.hpp"

#endif // FSM_H 
//EOF
