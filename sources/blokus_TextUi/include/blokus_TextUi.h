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
#ifndef _BLOKUS_TEXT_UI_H_
#define _BLOKUS_TEXT_UI_H_

#include "FSM_UI.h"
#include "blokus_situation.h"

namespace blokus
{
  class blokus_TextUi:public FSM_base::FSM_UI<blokus_situation>
  {
  public:
    blokus_TextUi(void);
  
    //Methods inherited from interface
    void display_specific_situation(const blokus_situation & p_situation);
    const std::string & get_class_name(void)const;
    
  private:
    static const std::string m_class_name;
  };
}
#endif
//EOF
