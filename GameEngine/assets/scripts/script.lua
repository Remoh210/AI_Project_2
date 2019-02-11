--Create New group 
newCG("Main")
--Create New Command SubGroup
newSubCG("Main", "CameraMove")
--Create New commands and add it to existing command group to run them parallel
-- (Group Name, CommandName, objName, x, y, z, time, EaseIn from 0 to 1, EaseOut, Target Obj, ScriptName)
newCom("CameraMove", "MoveToEaseIO",  "camera", 0, 125, 0, 8, 0.14, 0.1, 0, "", "earth")
