/*    This file is part of blokus_FSM
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
#ifndef _BLOKUS_MOTOR_H_
#define _BLOKUS_MOTOR_H_

#include "FSM_motor.h"
#include "blokus_situation.h"
#include "blokus_transition.h"

namespace blokus
{
  class blokus_motor:public FSM_base::FSM_motor<blokus_situation,blokus_transition>
    {
    public:
      // Methods inherited from FSM_motor
      const std::string & get_class_name(void)const;
      blokus_situation & run(const blokus_situation & p_situation,
                             const blokus_transition & p_transition);
    private:
      static const std::string m_class_name;
   };
}
#endif
//EOF
