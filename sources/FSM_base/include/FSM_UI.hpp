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

namespace FSM_base
{
  //-----------------------------------------------------------------------------
  template <class T_SITUATION>
  FSM_UI<T_SITUATION>::~FSM_UI(void)
  {
  }


  //-----------------------------------------------------------------------------
  template <class T_SITUATION>
  void FSM_UI<T_SITUATION>::display_situation
  (
   const FSM_situation_if & p_situation
   )
  {
    assert(dynamic_cast<const T_SITUATION*>(&p_situation) != NULL);
    const T_SITUATION *l_situation = static_cast<const T_SITUATION*>(&p_situation);
    this->display_specific_situation(*l_situation);

  }

}
//EOF
