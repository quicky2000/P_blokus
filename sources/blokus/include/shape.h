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
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <inttypes.h>
#include <vector>
#include <set>
#include <cassert>

namespace blokus
{
  class shape
  {
  public:
    inline shape(const uint32_t & p_shape_id,
		 const std::set<std::pair<uint32_t,uint32_t> > & p_squares);
    inline const uint32_t & get_shape_id(void)const;
    inline const uint32_t & get_id(void)const;
    inline const uint32_t & get_rank(void)const;
    inline bool is_blocked(const int32_t & p_x,
			   const int32_t & p_y)const;
    inline bool is_corner(const int32_t & p_x,
			  const int32_t & p_y)const;
    inline bool is_square(const int32_t & p_x,
			  const int32_t & p_y)const;
    inline bool is_start(const int32_t & p_x,
			 const int32_t & p_y)const;
    inline uint32_t get_min_x(void)const;
    inline uint32_t get_max_x(void)const;
    inline uint32_t get_min_y(void)const;
    inline uint32_t get_max_y(void)const;

    inline const std::set<std::pair<uint32_t,uint32_t> > & get_squares(void)const;
    inline const std::set<std::pair<uint32_t,uint32_t> > & get_starts(void)const;
    inline const std::set<std::pair<int32_t,int32_t> > & get_blockeds(void)const;
    inline const std::set<std::pair<int32_t,int32_t> > & get_corners(void)const;
  private:
    inline void add_square(const uint32_t & p_x,
			   const uint32_t & p_y);
    inline void mark_blocked(const int32_t & p_x,
			     const int32_t & p_y);
    inline void mark_corner(const int32_t & p_x,
			    const int32_t & p_y);
    uint32_t m_shape_id;
    uint32_t m_rank;
    uint32_t m_min_x;
    uint32_t m_min_y;
    uint32_t m_max_x;
    uint32_t m_max_y;
    std::set<std::pair<uint32_t,uint32_t> > m_squares;
    std::set<std::pair<uint32_t,uint32_t> > m_starts;
    std::set<std::pair<int32_t,int32_t> > m_blockeds;
    std::set<std::pair<int32_t,int32_t> > m_corners;
    uint32_t m_id;
    static uint32_t m_unique_id;
  };

  //----------------------------------------------------------------------------
  const uint32_t & shape::get_rank(void)const
    {
      return m_rank;
    }

  //----------------------------------------------------------------------------
  const uint32_t & shape::get_shape_id(void)const
    {
      return m_shape_id;
    }

  //----------------------------------------------------------------------------
  const uint32_t & shape::get_id(void)const
  {
      return m_id;
  }

  //----------------------------------------------------------------------------
  shape::shape(const uint32_t & p_shape_id,
               const std::set<std::pair<uint32_t,uint32_t> > & p_squares):
    m_shape_id(p_shape_id),
    m_rank(p_squares.size()),
    m_min_x(UINT32_MAX),
    m_min_y(UINT32_MAX),
    m_max_x(0),
    m_max_y(0),
    m_id(m_unique_id)
    {
      ++m_unique_id;
      for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = p_squares.begin();
	  p_squares.end() != l_iter;
	  ++l_iter)
	{
	  add_square(l_iter->first,l_iter->second);
	}
      for(std::set<std::pair<uint32_t,uint32_t> >::const_iterator l_iter = p_squares.begin();
	  p_squares.end() != l_iter;
	  ++l_iter)
	{
	  if(m_corners.end() != m_corners.find(std::pair<int32_t,int32_t>(((int32_t)l_iter->first) + 1,((int32_t)l_iter->second) + 1)) ||
	     m_corners.end() != m_corners.find(std::pair<int32_t,int32_t>(((int32_t)l_iter->first) - 1,((int32_t)l_iter->second) - 1)) ||
	     m_corners.end() != m_corners.find(std::pair<int32_t,int32_t>(((int32_t)l_iter->first) - 1,((int32_t)l_iter->second) + 1)) ||
	     m_corners.end() != m_corners.find(std::pair<int32_t,int32_t>(((int32_t)l_iter->first) + 1,((int32_t)l_iter->second) - 1)) 
	     )
	    {
	      m_starts.insert(*l_iter);
	    }
	}
      assert(0 == m_min_x && 0 == m_min_y);
    }

    //----------------------------------------------------------------------------
    void shape::add_square(const uint32_t & p_x,
			   const uint32_t & p_y)
    {
      // Compute min/max positions of squares
      if(p_x < m_min_x) m_min_x = p_x;
      if(p_y < m_min_y) m_min_y = p_y;
      if(p_x > m_max_x) m_max_x = p_x;
      if(p_y > m_max_y) m_max_y = p_y;

      // Store square position
      m_squares.insert(std::pair<int32_t,int32_t>(p_x,p_y));

      // check if it was a corner
      std::set<std::pair<int32_t,int32_t> >::iterator l_corner_iter = m_corners.find(std::pair<int32_t,int32_t>(p_x,p_y));
      if(m_corners.end() != l_corner_iter)
	{
	  m_corners.erase(l_corner_iter);
	}
      // check if it was blocked
      std::set<std::pair<int32_t,int32_t> >::iterator l_blocked_iter = m_blockeds.find(std::pair<int32_t,int32_t>(p_x,p_y));
      if(m_blockeds.end() != l_blocked_iter)
	{
	  m_blockeds.erase(l_blocked_iter);
	}
      // Block all adjacent squares
      mark_blocked(p_x + 1,p_y);
      mark_blocked(p_x - 1,p_y);
      mark_blocked(p_x,p_y + 1);
      mark_blocked(p_x,p_y - 1);

      // Mark corners
      mark_corner(p_x + 1,p_y + 1);
      mark_corner(p_x - 1,p_y - 1);
      mark_corner(p_x + 1,p_y - 1);
      mark_corner(p_x - 1,p_y + 1);
    }

    //----------------------------------------------------------------------------
    void shape::mark_blocked(const int32_t & p_x,
			     const int32_t & p_y)
    {
      // Check if this is not a square
      if(!is_square(p_x,p_y))
	{
	  m_blockeds.insert(std::pair<int32_t,int32_t>(p_x,p_y));
      
	  // check if it was a corner
	  std::set<std::pair<int32_t,int32_t> >::iterator l_corner_iter = m_corners.find(std::pair<int32_t,int32_t>(p_x,p_y));
	  if(m_corners.end() != l_corner_iter)
	    {
	      m_corners.erase(l_corner_iter);
	    }
	}
    }

    //----------------------------------------------------------------------------
    void shape::mark_corner(const int32_t & p_x,
			    const int32_t & p_y)
    {
      if(!is_square(p_x,p_y) && !is_blocked(p_x,p_y))
	{
	  m_corners.insert(std::pair<int32_t,int32_t>(p_x,p_y));
	}    
    }

    //----------------------------------------------------------------------------
    bool shape::is_blocked(const int32_t & p_x,
			   const int32_t & p_y)const
    {
      return m_blockeds.end() != m_blockeds.find(std::pair<int32_t,int32_t>(p_x,p_y));
    }

    //----------------------------------------------------------------------------
    bool shape::is_corner(const int32_t & p_x,
			  const int32_t & p_y)const
    {
      return m_corners.end() != m_corners.find(std::pair<int32_t,int32_t>(p_x,p_y));
    }

    //----------------------------------------------------------------------------
    bool shape::is_square(const int32_t & p_x,
			  const int32_t & p_y)const
    {
      return m_squares.end() != m_squares.find(std::pair<int32_t,int32_t>(p_x,p_y));
    }

    //----------------------------------------------------------------------------
    bool shape::is_start(const int32_t & p_x,
			  const int32_t & p_y)const
    {
      return m_starts.end() != m_starts.find(std::pair<int32_t,int32_t>(p_x,p_y));
    }

    //----------------------------------------------------------------------------
    uint32_t shape::get_min_x(void)const
    {
      return m_min_x;
    }

    //----------------------------------------------------------------------------
    uint32_t shape::get_max_x(void)const
    {
      return m_max_x;
    }

    //----------------------------------------------------------------------------
    uint32_t shape::get_min_y(void)const
    {
      return m_min_y;
    }

    //----------------------------------------------------------------------------
    uint32_t shape::get_max_y(void)const
    {
      return m_max_y;
    }

    //----------------------------------------------------------------------------
    const std::set<std::pair<uint32_t,uint32_t> > & shape::get_squares(void)const
      {
	return m_squares;
      }

    //----------------------------------------------------------------------------
    const std::set<std::pair<uint32_t,uint32_t> > & shape::get_starts(void)const
      {
	return m_starts;
      }

    //----------------------------------------------------------------------------
    const std::set<std::pair<int32_t,int32_t> > & shape::get_blockeds(void)const
      {
	return m_blockeds;
      }

    //----------------------------------------------------------------------------
    const std::set<std::pair<int32_t,int32_t> > & shape::get_corners(void)const
      {
	return m_corners;
      }

}

#endif //_SHAPE_H_
//EOF
