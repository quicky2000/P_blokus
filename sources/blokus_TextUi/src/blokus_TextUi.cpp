/*    This file is part of blokus_TextUi
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
#include "blokus_TextUi.h"
#include "blokus_situation.h"

using namespace std;

namespace blokus
{
  //----------------------------------------------------------------------------
  blokus_TextUi::blokus_TextUi(void):FSM_UI<blokus_situation>()
  {
  }

  //----------------------------------------------------------------------------
  void blokus_TextUi::display_specific_situation(const blokus_situation & p_situation)
  {
    cout << p_situation.to_string() << endl ;
  }

  //----------------------------------------------------------------------------
  const std::string & blokus_TextUi::get_class_name(void)const
  {
    return m_class_name;
  }

  //----------------------------------------------------------------------------
  FSM_interfaces::FSM_UI_if & create_blokus_text_ui(void)
  {
    return *(new blokus_TextUi());
  }

  extern "C"
  {
    void register_fsm_ui(std::map<std::string,FSM_interfaces::FSM_UI_creator_t> & p_factory)
    {
      register_fsm_ui("blokus",create_blokus_text_ui,p_factory);
    }
  }

  const std::string blokus_TextUi::m_class_name = "blokus_TextUi";
}
//EOF
