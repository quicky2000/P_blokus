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
#ifndef _FSM_SITUATION_IF_
#define _FSM_SITUATION_IF_

#include <string>

namespace FSM_interfaces
{
  class FSM_context_if;

  class FSM_situation_if
  {
  public:
    // Methods to implement
    virtual FSM_context_if* get_current_context(void)const=0;
    virtual const std::string to_string(void)const=0;
    virtual void to_string(std::string &)const=0;
    virtual const std::string get_string_id(void)const=0;
    virtual void get_string_id(std::string &)const=0;
    virtual bool is_valid(void)const=0;
    virtual void set_invalid(void)=0;
    virtual bool is_final(void)const=0;
    virtual bool less(const FSM_situation_if * p_object2)const=0;
    
    // Virtual destructor
    inline virtual ~FSM_situation_if(void){};
  };
}
#endif
//EOF
