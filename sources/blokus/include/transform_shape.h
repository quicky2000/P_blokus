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
#ifndef _TRANSFORM_SHAPE_H_
#define _TRANSFORM_SHAPE_H_

namespace blokus
{
  class transform_shape
  {
  public:
    typedef void(*t_transform)(const shape &,std::set<std::pair<uint32_t,uint32_t> > & ) ;
    inline static void rotate_90(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
    inline static void rotate_180(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
    inline static void rotate_270(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
    inline static void h_symetry(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
    inline static void v_symetry(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
    inline static void ul_swap(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
    inline static void br_swap(const shape & l_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result);
  };

  // ***   Original
  // *

  // ***   h_symetry
  //   *

  // *     v_symetry
  // ***

  //   *   rotate_180
  // ***

  // **    ul_swap
  // *
  // *

  // *     rotate_270
  // *
  // **

  //  *    br_swap
  //  *
  // **

  // ** rotate_90
  //  *
  //  *

  //----------------------------------------------------------------------------
  //  123    63
  //  456    52
  //         41
  void transform_shape::br_swap(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(p_shape.get_max_y() - l_iter->second,p_shape.get_max_x() - l_iter->first));
      }
  }
  //----------------------------------------------------------------------------
  //  123    14
  //  456    25
  //         36
  void transform_shape::ul_swap(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(l_iter->second,l_iter->first));
      }
  }
  //----------------------------------------------------------------------------
  //  123    41
  //  456    52
  //         63
  void transform_shape::rotate_90(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(p_shape.get_max_y() - l_iter->second ,l_iter->first));
      }
  }
  //----------------------------------------------------------------------------
  //  123  654
  //  456  321
  void transform_shape::rotate_180(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(p_shape.get_max_x() - l_iter->first , p_shape.get_max_y() - l_iter->second));
      }
  }
  //----------------------------------------------------------------------------
  //  123  321
  //  456  654
  void transform_shape::h_symetry(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(p_shape.get_max_x() - l_iter->first ,l_iter->second));
      }
  }
  //----------------------------------------------------------------------------
  //  123  456
  //  456  123
  void transform_shape::v_symetry(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(l_iter->first ,p_shape.get_max_y() - l_iter->second));
      }
  }
  //----------------------------------------------------------------------------
  //  123    36
  //  456    25
  //         14
  void transform_shape::rotate_270(const shape & p_shape,std::set<std::pair<uint32_t,uint32_t> > & l_result)
  {

    const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
    for( std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = l_squares.begin();
	 l_squares.end() != l_iter;
	 ++l_iter)
      {
	l_result.insert(std::pair<uint32_t,uint32_t>(l_iter->second ,p_shape.get_max_x() - l_iter->first));
      }
  }
}
#endif // _TRANSFORM_SHAPE_H_
//EOF
