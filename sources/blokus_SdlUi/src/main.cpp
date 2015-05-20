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
#include "shape_generator.h"
#include <map>
#include <set>
#include <iostream>
#include <cassert>

#include "gui.h"
#include "board.h"
#include <unistd.h>

void display(const blokus::shape & p_shape)
{
  int32_t l_pos_x = 1;
  int32_t l_pos_y = 1;
  std::cout << "Shape Id = " << p_shape.get_shape_id() << "\t" << p_shape.get_id() << std::endl ;
  for(uint32_t l_y = 0 ; l_y <= p_shape.get_max_y() + 2 ; ++l_y)
    {
      for(uint32_t l_x = 0 ; l_x <= p_shape.get_max_x() + 2 ; ++l_x)
	{
	  int32_t l_relative_pos_x = l_x - l_pos_x;
	  int32_t l_relative_pos_y = l_y - l_pos_y;
	  char l_representation = ' ';
	  if(p_shape.is_square(l_relative_pos_x,l_relative_pos_y))
	    {
	      l_representation = p_shape.is_start(l_relative_pos_x,l_relative_pos_y) ? 'S' :'*';
	    }
	  if(p_shape.is_blocked(l_relative_pos_x,l_relative_pos_y))
	    {
	      assert(' ' == l_representation);
	      l_representation = 'x';
	    }
	  if(p_shape.is_corner(l_relative_pos_x,l_relative_pos_y))
	    {
	      assert(' ' == l_representation);
	      l_representation = '.';
	    }
	  std::cout << l_representation;
	}
      std::cout << std::endl ;
    }
}

typedef struct {
  int a;
  std::set<uint32_t> b[2];
  int c;
} t_my_struct;

int main(void)
{
#if 0 
  t_my_struct l_struct;
  std::cout << "&a " << &(l_struct.a) << std::endl ;
  std::cout << "&b " << &(l_struct.b) << std::endl ;
  std::cout << "&c " << &(l_struct.c) << std::endl ;
  std::cout << "sizeof " << sizeof(t_my_struct) << std::endl ;
  std::cout << "max size " << l_struct.b[0].max_size() << std::endl ;

  const std::set<uint32_t> & l_ref_0 = l_struct.b[0];
  const std::set<uint32_t> & l_ref_1 = l_struct.b[1];
  

  for(int l_index = 0 ; l_index < 100000 ; ++l_index)
    {
      l_struct.b[0].insert(l_index);
      l_struct.b[1].insert(1000+l_index);
    }
  std::cout << "&a " << &(l_struct.a) << std::endl ;
  std::cout << "&b " << &(l_struct.b) << std::endl ;
  std::cout << "&c " << &(l_struct.c) << std::endl ;
  std::cout << "sizeof " << sizeof(t_my_struct) << std::endl ;
  std::cout << "max size " << l_struct.b[0].max_size() << std::endl ;
  for(std::set<uint32_t>::const_iterator l_iter = l_ref_0.begin();
      l_iter != l_ref_0.end();
      ++l_iter)
    {
      std::cout << *l_iter << std::endl ;
    }
  for(std::set<uint32_t>::const_iterator l_iter = l_ref_1.begin();
      l_iter != l_ref_1.end();
      ++l_iter)
    {
      std::cout << *l_iter << std::endl ;
    }
  exit(-1);
#endif
  blokus::board l_board;

  blokus_SdlUi::gui l_gui;

  sleep(2);

  blokus::shape_generator l_generator;
  std::multimap<uint32_t,blokus::shape> l_result;
  l_generator.generate(l_result);

  std::cout << "Generated shapes : " << l_result.size() << std::endl ;
  for(std::multimap<uint32_t,blokus::shape>::const_iterator l_iter = l_result.begin() ;
      l_result.end() != l_iter;
      ++l_iter)
    {
      display(l_iter->second);
      const std::set<std::pair<uint32_t,uint32_t> > & l_starts = l_board.get_starts(blokus::blokus_types::BLUE);
      bool l_found = false;
      std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter_start = l_starts.begin();
      while(!l_found && l_starts.end() != l_iter_start)
	{
	  uint32_t l_pos_x = l_iter_start->first;
	  uint32_t l_pos_y = l_iter_start->second;
	  std::cout << "Start at (" << l_pos_x << "," << l_pos_y  << ")" << std::endl ;
	  if(l_board.check_position(l_pos_x,l_pos_y,l_iter->second,blokus::blokus_types::BLUE))
	    {
	      std::cout << "Position valid at (" << l_pos_x << "," << l_pos_y << ")" << std::endl ;
	      l_found = true;
	      l_gui.lock();
	      l_board.place_shape(l_pos_x,l_pos_y,l_iter->second,blokus::blokus_types::BLUE);
	      l_gui.draw_shape(l_pos_x,l_pos_y,l_iter->second,blokus::blokus_types::BLUE);
	      l_gui.unlock();
	      l_gui.refresh();
	      sleep(1);
	    }
	  else
	    {
	      ++l_iter_start;
	    }
	}
#if 0 
      if(l_board.check_position(0,0,l_iter->second,blokus::blokus_types::BLUE))
	{
	  l_gui.lock();
	  l_board.place_shape(0,0,l_iter->second,blokus::blokus_types::BLUE);
	  l_gui.draw_shape(0,0,l_iter->second,blokus::blokus_types::BLUE);
	  l_gui.unlock();
	  l_gui.refresh();

	  sleep(1);
	  l_gui.lock();
	  l_gui.clear_shape(0,0,l_iter->second);
	  l_gui.unlock();
	  l_gui.refresh();
	}
#endif
    }
}
