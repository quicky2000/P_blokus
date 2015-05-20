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
#include "blokus_situation_analyzer.h"
#include "blokus_game.h"

namespace blokus
{
  //-----------------------------------------------------------------------------
  const std::string & blokus_situation_analyzer::get_class_name(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  std::vector<const blokus_transition*> & blokus_situation_analyzer::get_transitions(blokus_situation & p_situation)
    {
      std::vector<const blokus_transition*> & l_result = *(new std::vector<const blokus_transition*>());

      const std::multimap<uint32_t,uint32_t> & l_available_shape_ids = p_situation.get_available_shape_ids();
      for(std::multimap<uint32_t,uint32_t>::const_iterator l_shape_id_iter =  l_available_shape_ids.begin();
	  l_available_shape_ids.end() != l_shape_id_iter;
	  ++l_shape_id_iter)
	{
	  const shape & l_shape = blokus_game::get_unique_shape(l_shape_id_iter->second);
	  const std::set<std::pair<uint32_t,uint32_t> > & l_starts = p_situation.get_board().get_starts(blokus_types::BLUE);
	  for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_pos_iter = l_starts.begin();
	      l_starts.end() != l_pos_iter;
	      ++l_pos_iter)
	    {
	      if(p_situation.get_board().check_position(l_pos_iter->first,l_pos_iter->second,l_shape,blokus_types::BLUE))
		{
		  l_result.push_back(new blokus_transition(l_shape_id_iter->second,*l_pos_iter));
		}
	    }
	}

      return l_result;
    }
  const std::string blokus_situation_analyzer::m_class_name = "blokus_situation_analyzer";
}
//EOF
