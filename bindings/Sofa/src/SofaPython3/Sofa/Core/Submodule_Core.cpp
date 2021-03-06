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


#include <sofa/core/objectmodel/BaseNode.h>
#include <sofa/core/objectmodel/BaseContext.h>
#include <sofa/core/behavior/BaseForceField.h>
#include <sofa/core/objectmodel/Context.h>

#include "Binding_Base.h"
#include "Binding_BaseObject.h"
#include "Binding_DataDict.h"
#include "Binding_BaseData.h"
#include "Binding_BaseCamera.h"
#include "Binding_ForceField.h"
#include "Binding_Controller.h"
#include "Binding_DataEngine.h"
#include "Binding_Node.h"
#include "Binding_NodeIterator.h"
#include "Binding_Prefab.h"
#include "Binding_Simulation.h"
#include "Binding_BaseLink.h"
#include "Binding_PythonScriptEvent.h"

#include "Data/Binding_DataString.h"
#include "Data/Binding_DataVectorString.h"
#include "Data/Binding_DataContainer.h"

#include "Submodule_Core.h"



namespace sofapython3
{

/// The first parameter must be named the same as the module file to load.
PYBIND11_MODULE(Core, core)
{
    core.doc() = R"doc(
           Scene components
           -----------------------

           Core components
           ^^^^^^^^^^^^^^^

           .. autosummary::
               :toctree: _autosummary/_autosummary

               Sofa.Core.Data
               Sofa.Core.Link
               Sofa.Core.Node
               Sofa.Core.RawPrefab
               Sofa.Core.Object
               Sofa.Core.Camera

           Overridable components
           ^^^^^^^^^^^^^^^^^^^^^^

           .. autosummary::
               :toctree: _autosummary/_autosummary

               Sofa.Core.Controller
               Sofa.Core.ForceField
               Sofa.Core.DataEngine


           Utilitary classes
           ^^^^^^^^^^^^^^^^^

           .. autosummary::
               :toctree: _autosummary/_autosummary

               Sofa.Core.DataDict
               Sofa.Core.DataDictIterator
               Sofa.Core.DataContainer
               Sofa.Core.DataString
               Sofa.Core.DataVectorString
               Sofa.Core.NodeIterator
               #Sofa.Core.WriteAccessor
       )doc";

    moduleAddPythonScriptEvent();
    moduleAddDataDict(core);
    moduleAddDataDictIterator(core);
    moduleAddBase(core);
    moduleAddBaseData(core);
    moduleAddDataContainerContext(core);
    moduleAddDataContainer(core);
    moduleAddDataString(core);
    moduleAddDataVectorString(core);
    moduleAddBaseObject(core);
    moduleAddBaseCamera(core);
    moduleAddController(core);
    moduleAddDataEngine(core);
    moduleAddForceField(core);

    moduleAddNode(core);
    moduleAddNodeIterator(core);
    moduleAddPrefab(core);
    moduleAddBaseLink(core);

}

} ///namespace sofapython3
