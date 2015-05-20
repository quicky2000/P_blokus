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
#include "algorithm_wide_first.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
using namespace std;

namespace FSM_framework
{
  //-----------------------------------------------------------------------------
  void algorithm_wide_first::run(void)
  {
    if(get_fsm() != NULL)
      {
        get_fsm()->configure();
        FSM_interfaces::FSM_situation_if *l_previous_situation = NULL;
        bool l_continu = true;

        get_fsm()->compute_transitions();
        m_situation_manager.get_unique_situation(get_fsm()->get_current_situation());

        // Initialisinng situation vector
        m_situation_vector.push_back(&(get_fsm()->get_current_situation()));
        vector<FSM_interfaces::FSM_situation_if*>::const_iterator l_iter = m_situation_vector.begin();
 
        do
          {
            cout << "Vector size = " << m_situation_vector.size() << endl ;
            cout << "Map size = " << m_situation_tree.size() << endl ;
            l_previous_situation = *l_iter;
            cout << "Current situation : " <<endl ; 
            get_fsm_ui()->display_situation(*l_previous_situation) ;


            if(!l_previous_situation->is_final())
              {
                FSM_interfaces::FSM_context_if *l_context = l_previous_situation->get_current_context();
                FSM_interfaces::FSM_types::transition_index_t l_nb_transition = l_context->get_nb_transitions();
	      
                cout << "Available transitions : " << endl ;
                for(FSM_interfaces::FSM_types::transition_index_t l_transition_index = 0;l_transition_index < l_nb_transition ; ++l_transition_index)
                  {
                    cout << l_transition_index << " : " <<  l_context->get_transition(l_transition_index).to_string() << endl ;
                    get_fsm()->select_transition(l_transition_index);
		  
                    FSM_interfaces::FSM_situation_if & l_new_situation = get_fsm()->get_current_situation();
                    if(l_new_situation.is_valid())
                      {
                        if(&l_new_situation == &m_situation_manager.get_unique_situation(l_new_situation))
                          {
                            get_fsm()->compute_transitions();
			  
                            m_situation_vector.push_back(&l_new_situation);
                            m_situation_tree.insert( map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::value_type(&l_new_situation,situation_tree_node(l_new_situation,*l_previous_situation,l_transition_index)));
                          }
                      }
                    else
                      {
                        delete & l_new_situation;
                      }
                    get_fsm()->set_current_situation(*l_previous_situation);
                  }
                m_situation_vector.erase( m_situation_vector.begin());
                l_iter = m_situation_vector.begin();
                l_continu = (l_iter !=  m_situation_vector.end());
              }
            else
              {
                l_continu = false;
                cout << "Final situation reached !!!" << endl ;
              }
          } while(l_continu);
      }
    else
      {
        cout << "FSM ERROR : no FSM in algorithm" << endl ;
      }
  }

  //-----------------------------------------------------------------------------
  const std::string & algorithm_wide_first::get_string(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  void algorithm_wide_first::register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
  {
    register_framework_algorithm("algorithm_wide_first",create_algorithm_wide_first,p_factory);
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if & create_algorithm_wide_first(void)
  {
    return *(new algorithm_wide_first());
  }

#ifdef EXTERNAL_ALGORITHM
  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_algorithm(map<string,FSM_framework_algorithm_creator_t> & p_factory)
    {
      register_framework_algorithm("algorithm_wide_first",create_algorithm_wide,p_factory);
    }
  }
#endif

  const std::string algorithm_wide_first::m_class_name = "algorithm_wide_first";
}
//EOF
