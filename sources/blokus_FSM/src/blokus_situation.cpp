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
#include "blokus_situation.h"
#include "blokus_game.h"

namespace blokus
{
  //-----------------------------------------------------------------------------
  blokus_situation::blokus_situation(void)
  {
    this->set_context(*(new blokus_context()));
    for(int_least8_t l_index = 0 ; l_index < blokus_game::get_nb_unique_shape() ; ++l_index)
      {
	const shape & l_shape = blokus_game::get_unique_shape(l_index);
	m_available_shape_ids.insert(std::multimap<uint32_t,uint32_t>::value_type(l_shape.get_shape_id(),l_index));
      }
  }
  //-----------------------------------------------------------------------------
  blokus_situation::blokus_situation(const blokus_situation & p_situation):
    m_board(p_situation.m_board),
    m_available_shape_ids(p_situation.m_available_shape_ids)
  {
    this->set_context(*(new blokus_context()));
  }

  //----------------------------------------------------------------------------
  blokus_situation::~blokus_situation(void)
  {
  }

  //----------------------------------------------------------------------------
  const std::string blokus_situation::to_string(void)const
  {
    std::string l_result;
    m_board.to_string(l_result);
    return l_result;
  }

  //----------------------------------------------------------------------------
  const std::string blokus_situation::get_string_id(void)const
  {
    std::string l_result;
    m_board.to_string(l_result);
    return l_result;
  }

  //----------------------------------------------------------------------------
  void blokus_situation::to_string(std::string & p_result)const
  {
    m_board.to_string(p_result);
  }

  //----------------------------------------------------------------------------
  void blokus_situation::get_string_id(std::string & p_result)const
  {
    m_board.to_string(p_result);
  }

  //----------------------------------------------------------------------------
  bool blokus_situation::less(const FSM_situation_if *p_situation)const
  {
    const blokus_situation * l_situation = dynamic_cast<const blokus_situation *>(p_situation);
    assert(l_situation);
    return m_board.less(l_situation->m_board);
  }

  //----------------------------------------------------------------------------
  void blokus_situation::place_shape(const shape & p_shape,
				     const std::pair<uint32_t,uint32_t> & p_pos)
  {
    std::multimap<uint32_t,uint32_t>::iterator l_iter = m_available_shape_ids.find(p_shape.get_shape_id());
    assert(m_available_shape_ids.end() != l_iter);
    m_available_shape_ids.erase(p_shape.get_shape_id());
    m_board.place_shape(p_pos.first,p_pos.second,p_shape,blokus_types::BLUE);
  } 

  //----------------------------------------------------------------------------
  bool blokus_situation::is_final(void)const
  {
    return !m_available_shape_ids.size();
  }

  //----------------------------------------------------------------------------
  const board & blokus_situation::get_board(void)const
    {
      return m_board;
    }

  //----------------------------------------------------------------------------
  const std::multimap<uint32_t,uint32_t> & blokus_situation::get_available_shape_ids(void)const
    {
      return m_available_shape_ids;
    }
}
//EOF
