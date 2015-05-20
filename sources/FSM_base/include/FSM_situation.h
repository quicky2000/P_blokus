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
#ifndef FSM_SITUATION
#define FSM_SITUATION

#include "FSM_situation_if.h"
#include "assert.h"

namespace FSM_base
{
  template <class T_CONTEXT> class FSM_situation:public FSM_interfaces::FSM_situation_if
  {
  private:
    typedef FSM_interfaces::FSM_context_if FSM_context_if;
  public:
    // Constructors and destructors
    FSM_situation(void);
    FSM_situation(const FSM_situation & p_situation);
    virtual ~FSM_situation(void);

    // Methods inherited from interface
    FSM_context_if * get_current_context(void)const;
    virtual const std::string to_string(void)const=0;
    virtual void to_string(std::string &)const=0;
    bool is_valid(void)const;
    void set_invalid(void);

    // Specific methods
    T_CONTEXT* get_context(void)const;
    void set_context(T_CONTEXT & p_context);

  private:
    T_CONTEXT * m_context;
    bool m_valid;
  };
}

#include "FSM_situation.hpp"

#endif // FSM_SITUATION 
//EOF
