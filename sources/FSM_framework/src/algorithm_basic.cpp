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
#include "algorithm_basic.h"
#include "FSM_if.h"
#include "FSM_types.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
using namespace std;

namespace FSM_framework
{
  //-----------------------------------------------------------------------------
  void algorithm_basic::run(void)
  {
    if(get_fsm() != NULL)
      {
	get_fsm()->configure();
	FSM_interfaces::FSM_situation_if *l_previous_situation = NULL;
	bool l_continu = true;
	do
	  {

	    l_previous_situation = & get_fsm()->get_current_situation();
	    get_fsm_ui()->display_situation(*l_previous_situation) ;
	    if(!l_previous_situation->is_final())
	      {
		get_fsm()->compute_transitions();

		FSM_interfaces::FSM_context_if *l_context = l_previous_situation->get_current_context();
		unsigned int l_nb_transition = l_context->get_nb_transitions();
			
		if(l_nb_transition)
		  {
		    bool l_done = false;
		    do
		      {
			cout << "Available transitions : " << endl ;
			for(FSM_interfaces::FSM_types::transition_index_t l_transition_index = 0;l_transition_index < l_nb_transition ; l_transition_index++)
			  {
			    cout << l_transition_index << " : " <<  l_context->get_transition(l_transition_index).to_string() << endl ;
			  }
			FSM_interfaces::FSM_types::transition_index_t l_choosen_transition;
			cin >> l_choosen_transition;
			if(l_choosen_transition < l_nb_transition)
			  {
			    get_fsm()->select_transition(l_choosen_transition);
			    l_done = true ;
			  }
		      }while(!l_done);
		  }
		else
		  {
		    std::cout << "No more available transitions" << std::endl ;
		    l_continu = false;
		  }
	      }
	    else
	      {
		l_continu = false;
		cout << "Final situation reached !!!" << endl ;
	      }
	    delete l_previous_situation;
	  } while(l_continu);
      }
    else
      {
	cout << "FSM ERROR : no FSM in algorithm" << endl ;
      }
  }

  //-----------------------------------------------------------------------------
  const std::string & algorithm_basic::get_string(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  void algorithm_basic::register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
  {
    register_framework_algorithm("algorithm_basic",create_algorithm_basic,p_factory);
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if & create_algorithm_basic(void)
  {
    return * (new algorithm_basic());
  }

#ifdef EXTERNAL_ALGORITHM
  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_algorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
    {
      register_framework_algorithm("algorithm_basic",create_algorithm_basic,p_factory);
    }
  }
#endif
  const std::string algorithm_basic::m_class_name = "algorithm_basic";
}
//EOF
