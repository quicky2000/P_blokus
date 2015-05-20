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

#include <sstream>
using namespace std;

namespace FSM_base
{
  //------------------------------------------------------------------------------
  FSM_weighted_transition_index::FSM_weighted_transition_index(const transition_index_t & p_transition_index,
                                                               const transition_weight_t & p_weight):
    m_transition_index(p_transition_index),
    m_weight(p_weight)
  {
  }

  //------------------------------------------------------------------------------
  const FSM_weighted_transition_index::transition_index_t & FSM_weighted_transition_index::get_transition_index(void)const
  {
    return m_transition_index;
  }

  //------------------------------------------------------------------------------
  const FSM_weighted_transition_index::transition_weight_t & FSM_weighted_transition_index::get_weight(void)const
  {
    return m_weight;
  }

  //------------------------------------------------------------------------------
  const string FSM_weighted_transition_index::get_string(void)const
  {
    stringstream l_stream;
    l_stream << "(Index,Weight)=(" << m_transition_index << "," << m_weight << ")" ;
    return l_stream.str();
  }

  //------------------------------------------------------------------------------
  void FSM_weighted_transition_index::get_string(string & p_result)const
  {
    stringstream l_stream;
    l_stream << "(Index,Weight)=(" << m_transition_index << "," << m_weight << ")" ;
    p_result = l_stream.str();
  }

  //------------------------------------------------------------------------------
  bool FSM_weighted_transition_index::operator<(const FSM_weighted_transition_index_if & p_object2)const
  {
    bool l_result = m_weight < p_object2.get_weight();
    if(m_weight == p_object2.get_weight())
      {
        l_result = m_transition_index < p_object2.get_transition_index();
      }
    return l_result;
  }

}
//EOF
