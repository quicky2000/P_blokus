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
#include "algorithm_deep_first.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
#include <assert.h>
#include <inttypes.h>
using namespace std;

//#define ALGORITHM_VERBOSE

namespace FSM_framework
{

  //-----------------------------------------------------------------------------
  void algorithm_deep_first::run(void)
  {
    if(get_fsm() != NULL)
      {
	get_fsm()->configure();
	FSM_interfaces::FSM_situation_if *l_previous_situation = NULL;
	FSM_interfaces::FSM_types::transition_index_t l_previous_transition = 0;
        uint64_t l_nb_situation_explored = 0;
	bool l_continu = true;
	do
	  {
	    FSM_interfaces::FSM_situation_if * l_current_situation = & get_fsm()->get_current_situation();
	    get_fsm_ui()->display_situation(*l_current_situation) ;
#ifdef ALGORITHM_VERBOSE
		cout << "Current situation : \"" << l_current_situation->get_string_id() << "\"" <<endl ; 
#endif // ALGORITHM_VERBOSE	      
	      
	    // Check if situation was already encoutered
	    FSM_interfaces::FSM_situation_if * l_unique_situation = & m_situation_manager.get_unique_situation(*l_current_situation);
	    map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::iterator l_node_iter = m_situation_tree.find(l_unique_situation);
	    if(l_node_iter == m_situation_tree.end())
	      {
#ifdef ALGORITHM_VERBOSE
		std::cout << "New situation ! (never encountered)" << std::endl ;
		cout << "Computing transitions" << endl ;
#endif // ALGORITHM_VERBOSE	      
		get_fsm()->compute_transitions();
	      
		// Store current situation with its predecessor relation if it exists
		if(l_previous_situation != NULL)
		  {
		    l_node_iter = m_situation_tree.insert(map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(*l_current_situation,*l_previous_situation,l_previous_transition))).first;
		  }
		else
		  {
		    l_node_iter = m_situation_tree.insert(map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(*l_current_situation))).first;
		  }
#ifdef ALGORITHM_VERBOSE
		cout << "Total of situation = " <<  m_situation_tree.size() << endl;
#endif // ALGORITHM_VERBOSE	      
	      }
	    else if(l_current_situation != l_unique_situation)
	      {
		l_current_situation = l_unique_situation; 
		get_fsm()->set_current_situation(*l_unique_situation);
	      }
	  
	    situation_tree_node & l_situation_tree_node = l_node_iter->second;
	    const set<FSM_interfaces::FSM_types::transition_index_t> & l_unexplored_transitions = l_situation_tree_node.get_unexplored_transitions();
            ++l_nb_situation_explored;
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
 
	    if(!l_current_situation->is_final())
	      {
		// Check if it can go deeply
		if( l_current_situation->is_valid() && l_unexplored_transitions.size()>0)
		  {
		    // Store current situation to record the relationship of future situation
		    l_previous_transition = *(l_unexplored_transitions.begin());
		    l_previous_situation = l_current_situation;

#ifdef ALGORITHM_VERBOSE
		    cout << "Select transition number : " << l_previous_transition << endl ;
#endif // ALGORITHM_VERBOSE	      

		    // Compute the next situation
		    get_fsm()->select_transition(l_previous_transition);

		    // Indicate that transition is explored
		    l_situation_tree_node.set_transition_explored(l_previous_transition);
		  }
		// No more transition available so we go back for one step if possible
		else
		  {
	     
		    const map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> &l_predecessor_situations = l_situation_tree_node.get_predecessor_situations();
		    // Check if there is a predecessor
		    if(l_predecessor_situations.size())
		      {
			l_previous_situation = NULL;

			// Getting predecessor situation
			map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::const_iterator l_previous_node_iter = 
			  m_situation_tree.find(&(l_predecessor_situations.begin()->second));

			// Predecessor situation should be in situation tree !!!!
			assert(l_previous_node_iter != m_situation_tree.end());

#ifdef ALGORITHM_VERBOSE
			cout << "Restore previous situation" <<  endl ;
#endif // ALGORITHM_VERBOSE	      
			// Getting back to previous situation
			get_fsm()->set_current_situation(l_previous_node_iter->second.get_situation());
		      }
		    else
		      {		  
			// We are at the original situation
			l_continu = false ;
		      }
		  }
	      }
	    else
	      {
		cout << "Final situation found !!!" << endl ;
		cout << "Final situation : \"" << l_current_situation->get_string_id() << "\"" <<endl ; 
                std::cout << "Situations explored : "  << l_nb_situation_explored << std::endl ;
		l_continu = false;
	      }
	  } while(l_continu);
	cout << "End of algorithm" << endl ;
      }
    else
      {
	cout << "FSM ERROR : no FSM in algorithm" << endl ;
      }
  }

  //-----------------------------------------------------------------------------
  const string & algorithm_deep_first::get_string(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  void algorithm_deep_first::register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
  {
    register_framework_algorithm("algorithm_deep_first",create_algorithm_deep_first,p_factory);
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if & create_algorithm_deep_first(void)
  {
    return *(new algorithm_deep_first());
  }

#ifdef EXTERNAL_ALGORITHM
  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
    {
      register_framework_algorithm("algorithm_deep_first",create_algorithm_deep_first,p_factory);
    }
  }
#endif
  const std::string algorithm_deep_first::m_class_name = "algorithm_deep_first";
}
//EOF
