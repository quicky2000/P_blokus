/*    This file is part of blokus_SdlUi
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
#ifndef _GUI_H_
#define _GUI_H_

#include "simple_gui.h"
#include "shape.h"
#include "blokus_types.h"
#include <inttypes.h>

namespace blokus_SdlUi
{
  class gui: public simple_gui
  {
  public:
    inline gui(void);
    inline void draw_shape(const uint32_t & p_x,
			   const uint32_t & p_y,
			   const blokus::shape & p_shape,
			   const blokus::blokus_types::t_blokus_color & p_color);
    inline void clear_shape(const uint32_t & p_x,
			    const uint32_t & p_y,
			    const blokus::shape & p_shape);
  private:
    inline void draw_shape(const uint32_t & p_x,
			   const uint32_t & p_y,
			   const blokus::shape & p_shape,
			   const uint32_t & p_color);
    inline void fill_square(const uint32_t & p_x,
			    const uint32_t & p_y,
			    const uint32_t & p_color_code);
    const int m_block_size;
    const int m_grid_x_start;
    const int m_grid_y_start;
    int m_colors[5];
  };

  //----------------------------------------------------------------------------
  void gui::clear_shape(const uint32_t & p_x,
			const uint32_t & p_y,
			const blokus::shape & p_shape)
  {
    draw_shape(p_x,p_y,p_shape,m_colors[0]);
  }

  //----------------------------------------------------------------------------
  void gui::draw_shape(const uint32_t & p_x,
		       const uint32_t & p_y,
		       const blokus::shape & p_shape,
		       const uint32_t & p_color)
  {
    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	l_iter != l_squares.end();
	++l_iter)
      {
	fill_square(p_x + l_iter->first,p_y + l_iter->second,p_color);
      }
  }
  //----------------------------------------------------------------------------
  void gui::draw_shape(const uint32_t & p_x,
		       const uint32_t & p_y,
		       const blokus::shape & p_shape,
		       const blokus::blokus_types::t_blokus_color & p_color)
  {
    draw_shape(p_x,p_y,p_shape,m_colors[p_color]);
  }

  //----------------------------------------------------------------------------
  void gui::fill_square(const uint32_t & p_x,
			const uint32_t & p_y,
			const uint32_t & p_color_code)
  {
    for(uint32_t l_x = m_grid_x_start + p_x * m_block_size ;
	l_x < m_grid_x_start + (p_x + 1) *  m_block_size - 1;
	++l_x)
	{
	  for(uint32_t l_y = m_grid_y_start + p_y * m_block_size ;
	      l_y < m_grid_y_start + (p_y + 1) *  m_block_size - 1;
	      ++l_y)
	    {
	      set_pixel_without_lock(l_x,l_y,p_color_code);
	    }
	}
  }

  //----------------------------------------------------------------------------
  gui::gui(void):
    m_block_size(16),
    m_grid_x_start((640 - 20 * m_block_size) / 2),
    m_grid_y_start((480 - 20 *m_block_size) / 2)
    {
      createWindow(640,480);
      m_colors[0] = getColorCode(200,200,200);
      m_colors[blokus::blokus_types::RED] = getColorCode(255,0,0);
      m_colors[blokus::blokus_types::GREEN] = getColorCode(0,255,0);
      m_colors[blokus::blokus_types::BLUE] = getColorCode(0,0,255);
      m_colors[blokus::blokus_types::YELLOW] = getColorCode(255,255,0);
      lock();
      for(int l_x = 0 ; l_x < 20 ; ++l_x)
	{
	  for(int l_y = 0 ; l_y < 20 ; ++l_y)
	    {
	      fill_square(l_x,l_y,m_colors[0]);
	    }
	}
      unlock();
      refresh();
    }


  
}

#endif // _GUI_H_
//EOF
