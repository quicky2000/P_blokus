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
#ifndef _SHAPE_GENERATOR_H_
#define _SHAPE_GENERATOR_H_

#include <map>
#include "shape.h"
#include "transform_shape.h"
#include <iostream>

namespace blokus
{
  class shape_generator
  {
  public:
    inline shape_generator(void);
    inline void generate(std::multimap<uint32_t,shape> & p_shapes);
  private:
    inline void managed_transformed(transform_shape::t_transform p_transform,
                                    const shape & p_shape,
                                    std::vector<shape> & p_results);
    inline bool contains(const std::set<std::pair<uint32_t,uint32_t> > & p_squares)const;
    inline void expand_shape(const shape & p_shape, std::vector<shape> & p_result);
    // Container to store shapes by rank
    std::multimap<uint32_t,shape> m_shapes;
    uint32_t m_shape_id;
  };

  //----------------------------------------------------------------------------
  shape_generator::shape_generator(void):
    m_shape_id(1)
    {
    }

    //----------------------------------------------------------------------------
    void shape_generator::generate(std::multimap<uint32_t,shape> & p_results)
    {
      // Create initial shape
      std::set<std::pair<uint32_t,uint32_t> > l_basic_squares;
      l_basic_squares.insert(std::pair<uint32_t,uint32_t>(0,0));
      shape l_basic_shape(0,l_basic_squares);

      // Store it in result lists
      std::vector<shape> l_shapes;
      l_shapes.push_back(l_basic_shape);
      p_results.insert(std::multimap<uint32_t,shape>::value_type(l_basic_shape.get_shape_id(),l_basic_shape));
      m_shapes.insert(std::multimap<uint32_t,shape>::value_type(l_basic_shape.get_rank(),l_basic_shape));


      std::vector<shape> l_empty_vector;
      std::vector<shape> & l_generated_shapes = l_empty_vector;
      std::vector<shape> & l_shapes_to_expand = l_shapes;

      while(l_shapes_to_expand.size())
        {
          // Generate expanded shapes
          for(std::vector<shape>::const_iterator l_iter = l_shapes_to_expand.begin();
              l_shapes_to_expand.end() != l_iter && l_iter->get_rank() < 5;
              ++l_iter)
            {
              expand_shape(*l_iter,l_generated_shapes);
            }
          // Store new shapes in results
          for(std::vector<shape>::const_iterator l_iter = l_generated_shapes.begin();
              l_generated_shapes.end() != l_iter;
              ++l_iter)
            {
              p_results.insert(std::multimap<uint32_t,shape>::value_type(l_iter->get_shape_id(),*l_iter));
            }
          // Clear shape to expand
          l_shapes_to_expand.clear();
          // Use generated chapes as shape to expand
          std::swap(l_shapes_to_expand,l_generated_shapes);
        }	
    }

    //----------------------------------------------------------------------------
    void shape_generator::managed_transformed(transform_shape::t_transform p_transform,
                                              const shape & p_shape,
                                              std::vector<shape> & p_results)
    {
      std::set<std::pair<uint32_t,uint32_t> > l_new_squares;
      p_transform(p_shape,l_new_squares);
      if(!contains(l_new_squares))
        {
          shape l_new_shape(p_shape.get_shape_id(),l_new_squares);
          m_shapes.insert(std::multimap<uint32_t,shape>::value_type(l_new_shape.get_rank(),l_new_shape));
          p_results.push_back(l_new_shape);
        }
    }

    //----------------------------------------------------------------------------
    void shape_generator::expand_shape(const shape & p_shape, std::vector<shape> & p_results)
    {
      const std::set<std::pair<int32_t,int32_t> > & l_blockeds = p_shape.get_blockeds();
      for(std::set<std::pair<int32_t,int32_t> >::const_iterator l_blocked_iter = l_blockeds.begin();
          l_blockeds.end() != l_blocked_iter ;
          ++l_blocked_iter)
        {
          uint32_t l_x_offset = ( l_blocked_iter->first < 0 ? - l_blocked_iter->first : 0);
          uint32_t l_y_offset = ( l_blocked_iter->second < 0 ? - l_blocked_iter->second : 0);
          std::set<std::pair<uint32_t,uint32_t> > l_new_squares;
          l_new_squares.insert(std::pair<uint32_t,uint32_t>(l_blocked_iter->first + l_x_offset,l_blocked_iter->second + l_y_offset));
          const std::set<std::pair<uint32_t,uint32_t> > & l_squares = p_shape.get_squares();
          for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_square_iter = l_squares.begin();
              l_squares.end() != l_square_iter ;
              ++l_square_iter)
            {
              l_new_squares.insert(std::pair<uint32_t,uint32_t>(l_square_iter->first + l_x_offset,l_square_iter->second + l_y_offset));          
            }
          bool l_found = contains(l_new_squares);
          if(!l_found)
            {
              // Store shape in list of generated shaoes
              shape l_new_shape(m_shape_id,l_new_squares);
              m_shapes.insert(std::multimap<uint32_t,shape>::value_type(l_new_shape.get_rank(),l_new_shape));

              // Store shape in result
              p_results.push_back(l_new_shape);

              // Store transformed shape
              managed_transformed(transform_shape::rotate_90,l_new_shape,p_results);
              managed_transformed(transform_shape::rotate_180,l_new_shape,p_results);
              managed_transformed(transform_shape::rotate_270,l_new_shape,p_results);
              managed_transformed(transform_shape::h_symetry,l_new_shape,p_results);
              managed_transformed(transform_shape::v_symetry,l_new_shape,p_results);
              managed_transformed(transform_shape::ul_swap,l_new_shape,p_results);
              managed_transformed(transform_shape::br_swap,l_new_shape,p_results);

              // Prepare id for next shape
              ++m_shape_id;
            }
        }  
    }

    //----------------------------------------------------------------------------
    bool shape_generator::contains(const std::set<std::pair<uint32_t,uint32_t> > & p_squares)const
    {
      bool l_result = false;
      for(std::multimap<uint32_t,shape>::const_iterator l_iter = m_shapes.lower_bound(p_squares.size());
          !l_result && m_shapes.upper_bound(p_squares.size()) != l_iter;
          ++l_iter)
        {
          l_result = l_iter->second.get_squares() == p_squares;
        }
      return l_result;
    }

}

#endif
