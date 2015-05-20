/*    This file is part of FSM_framework
      The aim of this software is to provided generic facilities for FSM analyzis
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef _SITUATION_STACK_H_
#define _SITUATION_STACK_H_

#include <set>
#include <stack>
#include <cassert>

namespace FSM_interfaces
{
  class FSM_situation_if;
}

namespace FSM_framework
{
  class situation_stack
  {
  public:
    inline void push(FSM_interfaces::FSM_situation_if & p_situation);
    inline bool contains(FSM_interfaces::FSM_situation_if & p_situation)const;
    inline FSM_interfaces::FSM_situation_if & pop(void);
    inline unsigned int size(void)const;
  private:
    std::set< FSM_interfaces::FSM_situation_if * > m_sorted;
    std::stack< FSM_interfaces::FSM_situation_if * > m_in_order;
  };

  //----------------------------------------------------------------------------
  unsigned int situation_stack::size(void)const
  {
    return m_in_order.size();
  }
  //----------------------------------------------------------------------------
  void situation_stack::push(FSM_interfaces::FSM_situation_if & p_situation)
  {
    assert(m_sorted.end() == m_sorted.find(&p_situation));
    m_in_order.push(&p_situation);
    m_sorted.insert(&p_situation);
  }

  //----------------------------------------------------------------------------
  bool situation_stack::contains(FSM_interfaces::FSM_situation_if & p_situation)const
  {
    return m_sorted.end() != m_sorted.find(&p_situation);
  }

  //----------------------------------------------------------------------------
  FSM_interfaces::FSM_situation_if & situation_stack::pop(void)
  {
    assert(m_in_order.size());
    FSM_interfaces::FSM_situation_if & l_popped = *(m_in_order.top());
    std::set<FSM_interfaces::FSM_situation_if*>::iterator l_iter = m_sorted.find(&l_popped);
    assert(m_sorted.end() != l_iter);
    m_sorted.erase(l_iter);
    m_in_order.pop();
    return l_popped;
  }
}

#endif // _SITUATION_STACK_H_
//EOF
