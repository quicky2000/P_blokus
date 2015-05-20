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
#include "FSM_if.h"

using namespace std;

namespace FSM_interfaces
{
  //-----------------------------------------------------------------------------
  void register_fsm(const string & p_FSM_type,
                    FSM_creator_t p_creator,
                    map<string,FSM_creator_t>  & p_factory
                    )
  {
    p_factory.insert(map<string,FSM_creator_t>::value_type(p_FSM_type,p_creator));
  }
}
//EOF
