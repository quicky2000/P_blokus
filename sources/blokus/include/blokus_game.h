/*    This file is part of blokus
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
#ifndef _BLOKUS_GAME_H_
#define _BLOKUS_GAME_H_

#include "shape_generator.h"
#include <map>

namespace blokus
{
  class blokus_game
  {
  public:
    inline static const shape & get_unique_shape(const uint32_t & p_id);
    inline static const int_least8_t get_nb_unique_shape(void);
  private:
    static inline void fill_shapes(void);
    static std::map<uint32_t,shape> m_unique_shapes;
    static std::multimap<uint32_t,shape> m_all_shapes;

  };

  //----------------------------------------------------------------------------
  const int_least8_t blokus_game::get_nb_unique_shape(void)
    {
      if(!m_all_shapes.size())
	{
	  fill_shapes();
	}
      return  m_unique_shapes.size();
    }

  //----------------------------------------------------------------------------
  void blokus_game::fill_shapes(void)
  {
    shape_generator l_generator;
    l_generator.generate(m_all_shapes);
    
    for(std::multimap<uint32_t,shape>::const_iterator l_iter = m_all_shapes.begin() ;
	m_all_shapes.end() != l_iter;
	++l_iter)
      {
	m_unique_shapes.insert(std::map<uint32_t,shape>::value_type(l_iter->second.get_id(),l_iter->second));
      }
  }

  //----------------------------------------------------------------------------
  const shape & blokus_game::get_unique_shape(const uint32_t & p_id)
    {
      if(!m_all_shapes.size())
	{
	  fill_shapes();
	}
      std::map<uint32_t,shape>::const_iterator l_iter = m_unique_shapes.find(p_id);
      assert(m_unique_shapes.end() != l_iter);
      return l_iter->second;

    }

}
#endif
//EOF
