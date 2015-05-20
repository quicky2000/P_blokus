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
#ifndef _BLOKUS_SITUATION_ANALYZER_
#define _BLOKUS_SITUATION_ANALYZER_

#include "FSM_situation_analyzer.h"
#include "blokus_situation.h"
#include "blokus_transition.h"

namespace blokus
{
  class blokus_situation_analyzer: public FSM_base::FSM_situation_analyzer<blokus_situation,blokus_transition>
    {
    public:
      // Methods inherited from FSM_situation_analyzer
      const std::string & get_class_name(void)const;
      std::vector<const blokus_transition*> & get_transitions(blokus_situation & p_situation);
      
      // Specific methods
    private:
      static const std::string m_class_name;
    };

}
#endif /* _BLOKUS_SITUATION_ANALYZER_ */
//EOF
