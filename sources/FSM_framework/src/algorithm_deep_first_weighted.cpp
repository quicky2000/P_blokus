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
#include "algorithm_deep_first_weighted.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include "FSM_weighted_transition_index_if.h"
#include "FSM_weighted_transition_index_comparator.h"

#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

namespace FSM_framework
{

  //-----------------------------------------------------------------------------
  void algorithm_deep_first_weighted::run(void)
  {
    if(get_fsm() != NULL)
      {
	get_fsm()->configure();
	FSM_interfaces::FSM_situation_if *l_previous_situation = NULL;
	FSM_interfaces::FSM_types::transition_index_t l_previous_transition = 0;

	bool l_continu = true;
	do
	  {
	    FSM_interfaces::FSM_situation_if * l_current_situation = & get_fsm()->get_current_situation();
	      
	    // Check if situation was already encoutered
	    FSM_interfaces::FSM_situation_if * l_unique_situation = & m_situation_manager.get_unique_situation(*l_current_situation);
	    map<FSM_interfaces::FSM_situation_if*,situation_tree_node>::iterator l_node_iter = m_situation_tree.find(l_unique_situation);
	    map<FSM_interfaces::FSM_situation_if*,vector<FSM_interfaces::FSM_weighted_transition_index_if*> >::iterator l_weight_iter = m_situation_weighted_transition_index.find(l_unique_situation);
	    if(&l_current_situation == &l_unique_situation)
	      {
		cout << "Computing transitions" << endl ;
		cout << "Current situation : \"" << l_current_situation->get_string_id() << "\"" <<endl ; 
		get_fsm_ui()->display_situation(*l_current_situation) ;

		get_fsm()->compute_transitions();

		// Store current situation with its predecessor relation if it exists
		if(l_previous_situation != NULL)
		  {
		    l_node_iter = m_situation_tree.insert(map<FSM_interfaces::FSM_situation_if*,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(*l_current_situation,*l_previous_situation,l_previous_transition))).first;
		  }
		else
		  {
		    l_node_iter = m_situation_tree.insert(map<FSM_interfaces::FSM_situation_if*,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(*l_current_situation))).first;
		  }

		// Weighted code
		l_weight_iter = m_situation_weighted_transition_index.insert(map<FSM_interfaces::FSM_situation_if*,vector<FSM_interfaces::FSM_weighted_transition_index_if*> >::value_type(l_unique_situation,vector<FSM_interfaces::FSM_weighted_transition_index_if*>())).first;
		get_fsm()->compute_transition_weights(l_weight_iter->second);

		sort(l_weight_iter->second.begin(),l_weight_iter->second.end(),FSM_weighted_transition_index_comparator());

		vector<FSM_interfaces::FSM_weighted_transition_index_if*>::const_iterator l_iter = l_weight_iter->second.begin();
		vector<FSM_interfaces::FSM_weighted_transition_index_if*>::const_iterator l_iter_end = l_weight_iter->second.end();

		while(l_iter != l_iter_end)
		  {
		    cout << (*l_iter)->get_string() << "\t transition is " << l_current_situation->get_current_context()->get_transition((*l_iter)->get_transition_index()).to_string() << endl ;
		    ++l_iter;
		  }

		cout << "Total of situation = " <<  m_situation_tree.size() << endl;
	      }
	    else
	      {
		l_current_situation = l_unique_situation; 
		get_fsm()->set_current_situation(*l_current_situation);
	      }
	  
	    situation_tree_node & l_situation_tree_node = l_node_iter->second;
	    const set<FSM_interfaces::FSM_types::transition_index_t> &l_unexplored_transitions = l_situation_tree_node.get_unexplored_transitions();
	    vector<FSM_interfaces::FSM_weighted_transition_index_if*> &l_weighted_transitions = l_weight_iter->second;
		
	    cout << "Situation valid = " << l_current_situation->is_valid() << endl ;
	    cout << "Non explored transitions : " << l_unexplored_transitions.size() <<endl ;
	    set<FSM_interfaces::FSM_types::transition_index_t>::const_iterator l_iter = l_unexplored_transitions.begin();
	    set<FSM_interfaces::FSM_types::transition_index_t>::const_iterator l_iter_end = l_unexplored_transitions.end();
	    while(l_iter != l_iter_end)
	      {
		cout << *l_iter << " " ;
		l_iter++;
	      }
	    cout << endl ;
 
	    if(!l_current_situation->is_final())
	      {

		// Check if it can go deeply
		if( l_current_situation->is_valid() && l_unexplored_transitions.size()>0)
		  {
		    // Store current situation to record the relationship of future situation
		    l_previous_transition = (*l_weighted_transitions.begin())->get_transition_index();
		    l_previous_situation = l_current_situation;

		    cout << "Select transition number : " << l_previous_transition << endl ;

		    // Compute the next situation
		    get_fsm()->select_transition(l_previous_transition);

		    // Indicate that transition is explored
		    if((*l_weighted_transitions.begin())->get_weight())
		      {
			l_situation_tree_node.set_transition_explored(l_previous_transition);
			l_weighted_transitions.erase(l_weighted_transitions.begin());
		      }
		    else
		      {
			l_situation_tree_node.set_all_transition_explored();
			l_weighted_transitions.clear();
		      }
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
			map<FSM_interfaces::FSM_situation_if*,situation_tree_node>::const_iterator l_previous_node_iter =  m_situation_tree.find(&(l_predecessor_situations.begin()->second));

			// Predecessor situation should be in situation tree !!!!
			assert(l_previous_node_iter != m_situation_tree.end());

			// cout << "Restore previous situation " << l_previous_node_iter->second.get_situation() <<  endl ;
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
  const std::string & algorithm_deep_first_weighted::get_string(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  void algorithm_deep_first_weighted::register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
  {
    register_framework_algorithm("algorithm_deep_first_weighted",create_algorithm_deep_first_weighted,p_factory);
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if & create_algorithm_deep_first_weighted(void)
  {
    return *(new algorithm_deep_first_weighted());
  }

#ifdef EXTERNAL_ALGORITHM
  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
    {
      register_framework_algorithm("algorithm_deep_first_weighted",create_algorithm_deep_first,p_factory);
    }
  }
#endif
  const std::string algorithm_deep_first_weighted::m_class_name = "algorithm_deep_first_weighted";
}
//EOF
