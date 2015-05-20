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
#include "algorithm_deep_raw.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
#include <assert.h>
using namespace std;

//#define ALGORITHM_VERBOSE

namespace FSM_framework
{
  //----------------------------------------------------------------------------
  void algorithm_deep_raw::print_status(void)const
  {
    std::cout << "Current situation : \"" << get_fsm()->get_current_situation().get_string_id() << "\"" << std::endl ; 
    std::cout << "Total situations explored : "  << m_nb_situation_explored << std::endl ;
  }

  //-----------------------------------------------------------------------------
  void algorithm_deep_raw::run(void)
  {
    if(get_fsm() != NULL)
      {
	get_fsm()->configure();

        m_nb_situation_explored = 0;
	bool l_continu = true;
        get_fsm()->compute_transitions();
        m_situation_stack.push(get_fsm()->get_current_situation());
        get_fsm_ui()->display_situation(get_fsm()->get_current_situation());
	do
	  {
	    FSM_interfaces::FSM_situation_if & l_current_situation = m_situation_stack.top().get_situation();
            get_fsm()->set_current_situation(l_current_situation);
            //get_fsm_ui()->display_situation(l_current_situation) ;
#ifdef ALGORITHM_VERBOSE
            cout << "Current situation : \"" << l_current_situation->get_string_id() << "\"" <<endl ; 
#endif // ALGORITHM_VERBOSE	      
                
	    const set<FSM_interfaces::FSM_types::transition_index_t> & l_unexplored_transitions = m_situation_stack.top().get_unexplored_transitions();
#ifdef ALGORITHM_VERBOSE			
	    cout << "Situation valid = " << l_current_situation->is_valid() << endl ;
	    cout << "Non explored transitions : " << l_unexplored_transitions.size() <<endl ;
	    set<FSM_interfaces::FSM_types::transition_index_t>::const_iterator l_iter = l_unexplored_transitions.begin();
	    set<FSM_interfaces::FSM_types::transition_index_t>::const_iterator l_iter_end = l_unexplored_transitions.end();
	    while(l_iter != l_iter_end)
	      {
		cout << *l_iter << " " ;
		++l_iter;
	      }
	    cout << endl ;
#endif // ALGORITHM_VERBOSE	      

	    // Check if it can go deeply
	    if(l_unexplored_transitions.size() > 0)
	      {
		// Store current situation to record the relationship of future situation
                FSM_interfaces::FSM_types::transition_index_t l_previous_transition = *(l_unexplored_transitions.begin());

#ifdef ALGORITHM_VERBOSE
		cout << "Select transition number : " << l_previous_transition << endl ;
#endif // ALGORITHM_VERBOSE	      

		// Compute the next situation
		get_fsm()->select_transition(l_previous_transition);

		// Indicate that transition is explored
		m_situation_stack.top().set_transition_explored(l_previous_transition);

                FSM_interfaces::FSM_situation_if & l_new_situation = get_fsm()->get_current_situation();
                if(!m_situation_stack.contains(l_new_situation))
                  {
                    ++m_nb_situation_explored;
#ifdef ALGORITHM_VERBOSE
                    cout << "Total of situation = " <<  m_nb_situation_explored << endl;
#endif // ALGORITHM_VERBOSE	      
                    if(!l_new_situation.is_final())
                      {
#ifdef ALGORITHM_VERBOSE
                        cout << "Computing transitions" << endl ;
#endif // ALGORITHM_VERBOSE	      
                        get_fsm()->compute_transitions();
                      }
                    get_fsm_ui()->display_situation(l_new_situation) ;
                    if(l_new_situation.is_valid())
                      {
                        // Store in stack
                        m_situation_stack.push(get_fsm()->get_current_situation());
                      }
                    else
                      {
                        delete(&l_new_situation);
                      }

                  }	  
 

	      }
	    // No more transition available so we go back for one step if possible
	    else
	      {
                m_situation_stack.pop();
                delete &l_current_situation;
#ifdef ALGORITHM_VERBOSE
                std::cout << "Restore previous situation" << std::endl;
#endif // ALGORITHM_VERBOSE	      
                l_continu = m_situation_stack.size();
	      }
	  } while(l_continu && !m_stop);
	cout << "End of algorithm" << endl ;
        std::cout << "Total situations explored : "  << m_nb_situation_explored << std::endl ;
      }
    else
      {
	cout << "FSM ERROR : no FSM in algorithm" << endl ;
      }
  }

  //-----------------------------------------------------------------------------
  const std::string & algorithm_deep_raw::get_string(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  void algorithm_deep_raw::register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
  {
    register_framework_algorithm("algorithm_deep_raw",create_algorithm_deep_raw,p_factory);
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if & create_algorithm_deep_raw(void)
  {
    return *(new algorithm_deep_raw());
  }

#ifdef EXTERNAL_ALGORITHM
  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_algorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
    {
      register_framework_algorithm("algorithm_deep_raw",create_algorithm_deep_raw,p_factory);
    }
  }
#endif

  const std::string algorithm_deep_raw::m_class_name = "algorithm_deep_raw";
}
//EOF
