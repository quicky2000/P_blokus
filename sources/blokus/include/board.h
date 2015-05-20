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
#ifndef _BOARD_H_
#define _BOARD_H_

#include "blokus_types.h"
#include "shape.h"
#include <set>

namespace blokus
{
  class board
  {
  public:
    inline board(void);
    inline bool check_position(const uint32_t & p_x,
			       const uint32_t & p_y,
			       const shape & p_shape,
			       const blokus_types::t_blokus_color & p_color)const;

    inline const std::set<std::pair<uint32_t,uint32_t> > & get_starts(const blokus_types::t_blokus_color & p_color)const;

    inline void place_shape(const uint32_t & p_x,
			    const uint32_t & p_y,
			    const shape & p_shape,
			    const blokus_types::t_blokus_color & p_color);
    inline void to_string(std::string & )const;
    inline bool less(const board & p_board)const;
  private:
    inline bool is_free(const int32_t & p_x,
			const int32_t & p_y)const;
    inline bool is_blocked(const int32_t & p_x,
			   const int32_t & p_y,
			   const blokus_types::t_blokus_color & p_color)const;
    uint32_t m_grid[20][20];
    std::set<std::pair<uint32_t,uint32_t> > m_starts[5];
  };

  //----------------------------------------------------------------------------
  bool board::less(const board & p_board)const
  {
    for(uint32_t l_y = 0 ; l_y < 20 ; ++l_y)
      {
	for(uint32_t l_x = 0 ; l_x < 20 ; ++l_x)
	  {
	    if(m_grid[l_x][l_y] < p_board.m_grid[l_x][l_y] )
	      {
		return true;
	      }
	    else if(m_grid[l_x][l_y] > p_board.m_grid[l_x][l_y])
	      {
		return false;
	      }
	  }
      }    
    return false;
  }

  //----------------------------------------------------------------------------
  void board::to_string(std::string & p_string)const
  {
    char l_color2char[5] = {' ','B','J','R','V'};
    p_string = "";
    for(uint32_t l_y = 0 ; l_y < 20 ; ++l_y)
      {
	for(uint32_t l_x = 0 ; l_x < 20 ; ++l_x)
	  {
	    p_string += l_color2char[m_grid[l_x][l_y]];
	  }
	p_string += '\n';
      }
  }

  //----------------------------------------------------------------------------
  void board::place_shape(const uint32_t & p_x,
			  const uint32_t & p_y,
			  const shape & p_shape,
			  const blokus_types::t_blokus_color & p_color)
  {
    assert(check_position(p_x,p_y,p_shape,p_color));

    // place squares
    for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = p_shape.get_squares().begin();
	p_shape.get_squares().end() != l_iter;
	++l_iter)
      {
	uint32_t l_new_x = p_x + l_iter->first;
	uint32_t l_new_y = p_y + l_iter->second;
	m_grid[l_new_x][l_new_y] = p_color;
	// Check if it was a start
	for(int l_index = blokus_types::BLUE ; l_index <= blokus_types::GREEN ; ++l_index)
	  { 
	    std::set<std::pair<uint32_t,uint32_t> >::iterator l_iter_start = m_starts[l_index].find(std::pair<uint32_t,uint32_t>(l_new_x,l_new_y));
	    if(m_starts[l_index].end() != l_iter_start)
	      {
		m_starts[l_index].erase(l_iter_start);
	      }
	  }			      
      }
    // Check if new piece invalidate some starts of its own color
    for(std::set<std::pair<int32_t,int32_t> >::const_iterator l_blocked_iter = p_shape.get_blockeds().begin();
	p_shape.get_blockeds().end() != l_blocked_iter;
	++l_blocked_iter)
      {
	uint32_t l_new_x = p_x + l_blocked_iter->first;
	uint32_t l_new_y = p_y + l_blocked_iter->second;
	std::set<std::pair<uint32_t,uint32_t> >::iterator l_iter_start = m_starts[p_color].find(std::pair<uint32_t,uint32_t>(l_new_x,l_new_y));
	if(m_starts[p_color].end() != l_iter_start)
	  {
	    m_starts[p_color].erase(l_iter_start);
	  }
      }

    // Add new starts
    for(std::set<std::pair<int32_t,int32_t> >::const_iterator l_start_iter = p_shape.get_corners().begin();
	p_shape.get_corners().end() != l_start_iter;
	++l_start_iter)
      {
	uint32_t l_new_x = p_x + l_start_iter->first;
	uint32_t l_new_y = p_y + l_start_iter->second;
	if(!is_blocked(l_new_x,l_new_y,p_color) && is_free(l_new_x,l_new_y))
	  {
	    m_starts[p_color].insert(std::pair<uint32_t,uint32_t>(l_new_x,l_new_y));
	  }
      }
  }
  
  //----------------------------------------------------------------------------
  const std::set<std::pair<uint32_t,uint32_t> > & board::get_starts(const blokus_types::t_blokus_color & p_color)const
    {
      assert(p_color >= blokus_types::BLUE && p_color <= blokus_types::GREEN);
      return m_starts[p_color];
    }

  //----------------------------------------------------------------------------
  board::board(void)
    {
      for(int l_x = 0 ; l_x < 20 ; ++l_x)
	{
	  for(int l_y = 0 ; l_y < 20 ; ++l_y)
	    {
	      m_grid[l_x][l_y] = 0;
	    }
	}
      m_starts[blokus_types::BLUE].insert(std::pair<uint32_t,uint32_t>(0,0));
      m_starts[blokus_types::YELLOW].insert(std::pair<uint32_t,uint32_t>(19,0));
      m_starts[blokus_types::RED].insert(std::pair<uint32_t,uint32_t>(19,19));
      m_starts[blokus_types::GREEN].insert(std::pair<uint32_t,uint32_t>(0,19));

      //      m_grid[1][0]=blokus_types::RED;
    }

  //----------------------------------------------------------------------------
  bool board::is_free(const int32_t & p_x,
		      const int32_t & p_y)const
  {
    return p_x >= 0 && p_y >= 0 && p_x < 20 && p_y < 20 && !m_grid[p_x][p_y];
  }

  //----------------------------------------------------------------------------
  bool board::is_blocked(const int32_t & p_x,
		  const int32_t & p_y,
		  const blokus_types::t_blokus_color & p_color)const
  {
    return p_x >= 0 && p_y >= 0 && p_x < 20 && p_y < 20 && ((uint32_t)p_color) == m_grid[p_x][p_y];
  }

  //----------------------------------------------------------------------------
  bool board::check_position(const uint32_t & p_x,
			     const uint32_t & p_y,
			     const shape & p_shape,
			     const blokus_types::t_blokus_color & p_color)const
  {
    // Check if there is a valid start
    bool l_valid = false;
    for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = p_shape.get_squares().begin();
	!l_valid && p_shape.get_squares().end() != l_iter;
	++l_iter)
      {
	std::pair<uint32_t,uint32_t> l_real_start(p_x + l_iter->first,p_y + l_iter->second);
	l_valid = m_starts[p_color].end() != m_starts[p_color].find(l_real_start);	
      }
    if(!l_valid) return false;
    // Check if place is free
    for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = p_shape.get_squares().begin();
	l_valid && p_shape.get_squares().end() != l_iter;
	++l_iter)
      {
	l_valid = is_free(p_x + l_iter->first,p_y + l_iter->second);
      }
    if(!l_valid) return false;

    // Check if there is no blocking due to our other pieces
    for(std::set<std::pair<int32_t,int32_t> >::const_iterator l_iter = p_shape.get_blockeds().begin();
	l_valid && p_shape.get_blockeds().end() != l_iter;
	++l_iter)
      {
	l_valid = !is_blocked(p_x + l_iter->first,p_y + l_iter->second,p_color);	
      }
    return l_valid;
  }

}
#endif // _BOARD_H_
//#EOF
