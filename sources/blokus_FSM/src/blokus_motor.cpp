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
#include "blokus_motor.h"
#include "blokus_game.h"

namespace blokus
{
  //----------------------------------------------------------------------------
  const std::string & blokus_motor::get_class_name(void)const
    {
      return m_class_name;
    }
  //----------------------------------------------------------------------------
  blokus_situation & blokus_motor::run(const blokus_situation & p_situation,
				      const blokus_transition & p_transition)
    {
      blokus_situation & l_result = *(new blokus_situation(p_situation));
      l_result.place_shape(blokus_game::get_unique_shape(p_transition.get_shape_id()),p_transition.get_position());
      return l_result;
    }
  const std::string blokus_motor::m_class_name = "blokus_motor";
}
//EOF
