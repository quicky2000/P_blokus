/*    This file is part of blokus_FSM
      Copyright (C) 2014  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include "blokus_transition.h"
#include <sstream>

namespace blokus
{
  blokus_transition::blokus_transition(const uint32_t & p_shape_id,const std::pair<uint32_t,uint32_t> & p_position):
    m_shape_id(p_shape_id),
    m_position(p_position)
  {
  }

  // Methods inherited from interface
  //----------------------------------------------------------------------------
  const std::string blokus_transition::to_string(void)const
  {
    std::stringstream l_stream;
    l_stream << "Shape " << m_shape_id << "@ (" << m_position.first << "," << m_position.second << ")" ;
    return l_stream.str();
  }
  
  //----------------------------------------------------------------------------
  void blokus_transition::to_string(std::string & p_result)const
  {
    std::stringstream l_stream;
    l_stream << "Shape " << m_shape_id << "@ (" << m_position.first << "," << m_position.second << ")" ;
    p_result = l_stream.str();
  }
  
  //----------------------------------------------------------------------------
  const uint32_t & blokus_transition::get_shape_id(void)const
    {
      return m_shape_id;
    }

  //----------------------------------------------------------------------------
  const std::pair<uint32_t,uint32_t> & blokus_transition::get_position(void)const
    {
      return m_position;
    }

}
//EOF
