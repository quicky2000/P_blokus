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
#include "situation_manager.h"
#include "FSM_situation_if.h"

#include <iostream>
using namespace std;

namespace FSM_framework
{
  //----------------------------------------------------------------------------
  situation_manager::situation_manager(void)
  {
  }

  //----------------------------------------------------------------------------
  situation_manager::~situation_manager(void)
  {
    for(set<FSM_interfaces::FSM_situation_if*,pointer_comparator>::const_iterator l_iter = m_set.begin();
        m_set.end() != l_iter;
        ++l_iter)
      {
        delete *l_iter;
      }
  }

  //----------------------------------------------------------------------------
  FSM_interfaces::FSM_situation_if & situation_manager::get_unique_situation(FSM_interfaces::FSM_situation_if & p_situation)
  {
    FSM_interfaces::FSM_situation_if * l_result = & p_situation;
    set<FSM_interfaces::FSM_situation_if*,pointer_comparator>::const_iterator l_iter = m_set.find(&p_situation);
    if(l_iter != m_set.end())
      {
        if(*l_iter != & p_situation)
          {
            l_result = *l_iter;
            delete & p_situation;
          }
      }
    else
      {
        m_set.insert(&p_situation);
      }
    return *l_result;
  }
}
//EOF
