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
#ifndef FSM_IF_H
#define FSM_IF_H

#include "FSM_types.h"
#include <string>
#include <map>
#include <vector>

namespace FSM_interfaces
{
  class FSM_situation_if;
  class FSM_weighted_transition_index_if;

  /**
     Class defining FSM public interface
  **/
  class FSM_if
  {
  public:

    // Methods to implement
    virtual FSM_situation_if & get_current_situation(void)const=0;
    virtual void set_current_situation(FSM_situation_if & p_situation)=0;
    virtual void compute_transitions(void)=0;
    virtual void select_transition(const FSM_types::transition_index_t & p_transition_index)=0;
    virtual void configure(void)=0;
    virtual const std::string & get_class_name(void)const=0;
    virtual const std::string & get_fsm_name(void)const=0;
    virtual void compute_transition_weights(std::vector<FSM_weighted_transition_index_if*> &)const=0;

    //Virtual destructor
    inline virtual ~FSM_if(void){}
  };

  // Defining object type which allow to create FSMs instances
  typedef FSM_if & (*FSM_creator_t)();


  void register_fsm(const std::string & ,
		    FSM_creator_t,
		    std::map<std::string,FSM_creator_t> & );
}

#endif /* FSM_IF_H */
//EOF
