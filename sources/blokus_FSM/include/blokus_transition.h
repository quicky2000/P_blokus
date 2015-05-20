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
#ifndef _BLOKUS_TRANSITION_H_
#define _BLOKUS_TRANSITION_H_

#include "FSM_transition_if.h"
#include "inttypes.h"

namespace blokus
{
  class blokus_transition: public FSM_interfaces::FSM_transition_if
  {
  public:
    blokus_transition(const uint32_t & shape_id,const std::pair<uint32_t,uint32_t> & p_position);

    // Methods inherited from interface
    const std::string to_string(void)const;
    void to_string(std::string & p_result)const;
  
    // Dedicated methods
    const uint32_t & get_shape_id(void)const;
    const std::pair<uint32_t,uint32_t> & get_position(void)const;
  private:
    const uint32_t m_shape_id;
    const std::pair<uint32_t,uint32_t> m_position;
  };

}
#endif
//EOF
