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
#ifndef _BLOKUS_SITUATION_H_
#define _BLOKUS_SITUATION_H_

#include "FSM_situation.h"
#include "blokus_context.h"
#include "board.h"
#include <map>

namespace blokus
{
  class blokus_situation:public FSM_base::FSM_situation<blokus_context>
  {
  public:
    blokus_situation(void);
    blokus_situation(const blokus_situation & p_situation);
    ~blokus_situation(void);
    // Methods inherited from FSM_situation
    const std::string to_string(void)const;
    const std::string get_string_id(void)const;
    void to_string(std::string &)const;
    void get_string_id(std::string &)const;
    bool is_final(void)const;
    bool less(const FSM_situation_if *p_situation)const;

    const board & get_board(void)const;
    const std::multimap<uint32_t,uint32_t> & get_available_shape_ids(void)const;

    // Dedicated methods
    void place_shape(const shape & p_shape,
                     const std::pair<uint32_t,uint32_t> & p_pos); 
  private:
    board m_board;
    std::multimap<uint32_t,uint32_t> m_available_shape_ids;
  };

}
#endif
//EOF
