/*********************************************************************
Copyright 2019, CNRS, University of Lille, INRIA

This file is part of sofaPython3

sofaPython3 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

sofaPython3 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with sofaqtquick. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
/********************************************************************
 Contributors:
    - damien.marchal@univ-lille.fr
    - bruno.josue.marques@inria.fr
    - eve.le-guillou@centrale.centralelille.fr
    - jean-nicolas.brunet@inria.fr
    - thierry.gaugry@inria.fr
********************************************************************/

#include "Binding_PythonScriptEvent.h"

#include <SofaPython3/PythonFactory.h>
#include <sofa/core/objectmodel/Event.h>

namespace sofapython3 {
using namespace pybind11::literals;

SOFA_EVENT_CPP(PythonScriptEvent)

PythonScriptEvent::PythonScriptEvent(sofa::simulation::Node::SPtr sender, const char* eventName, py::object userData)
    : sofa::core::objectmodel::ScriptEvent(sender,eventName)
    , m_userData(userData){}

PythonScriptEvent::~PythonScriptEvent(){}

void moduleAddPythonScriptEvent()
{
    PythonFactory::registerType<PythonScriptEvent>(
                [] (sofa::core::objectmodel::Event* event) -> py::dict {
        auto evt = dynamic_cast<PythonScriptEvent*>(event);

        py::dict d("type"_a=evt->getClassName(),
                   "isHandled"_a=evt->isHandled(),
                   "sender"_a=(evt->getSender().get() ? py::cast(evt->getSender().get()) : py::none()),
                   "event_name"_a=py::cast(evt->getEventName()),
                   "userData"_a=evt->getUserData()
                   );
        return d;
    });
}

}  // namespace sofapython3

