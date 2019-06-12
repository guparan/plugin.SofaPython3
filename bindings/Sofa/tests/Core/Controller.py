# coding: utf8

import unittest
import gc
import Sofa

class MyController(Sofa.Controller):
        """This is my custom controller
           when init is called from Sofa this should call the python init function
        """        
        def __init__(self, *args, **kwargs):
                ## These are needed (and the normal way to override from a python class)
                Sofa.Controller.__init__(self, *args, **kwargs)
                print(" Python::__init__::"+str(self.name))
                self.inited = 0
                self.iterations = 0

        def __del__(self):
                print(" Python::__del__")
        
        def init(self):
                print(" Python::init() at "+str(self))
                self.inited += 1

        def onEvent(self, event):
                Sofa.Controller.handleEvent(self, event)
                print(" HandleEvent" )

        def onAnimateBeginEvent(self, other):
                print(" Python::onAnimationBeginEvent() at "+str(other))
                self.iterations+=1

class MyController2(Sofa.Controller):
    """This is another custom controller
       it can take arguments as parameters (or can it..?)
    """
    def __init__(self, *args, **kw):
        print ("Simple arguments list: " + str(args))
        print ("Keyword arguments list: " + str(kw))


class Test(unittest.TestCase):
         def test_constructor(self):
                 c = Sofa.Controller()
                 c.init()
                 c.reinit()

         def test_constructorOverriden(self):
                 root = Sofa.Node("rootNode")
                 root.addObject(MyController("controller"))
                 root.controller.init()
                 root.controller.reinit()

         def test_constructorOverriddenWithArgs(self):
             root = Sofa.Node("rootNode")
             root.addObject(MyController("controller", "value"))

         def test_constructorOverriddenWithKWArgs(self):
             root = Sofa.Node("rootNode")
             root.addObject(MyController("controller", an_argument="value2"))

         def test_methodOverriding(self):
                 """Test that a custom controller 'MyController' correctly adds attributes when overridden.
                 dynamically in its init and reinit function. And that after the
                 call the attributes are still available.
                 """
                 c = MyController("controller")

                 self.assertTrue( hasattr(c, "inited") )
                 c.init()

                 self.assertEqual( c.inited, 1 ) 
                 return c

         def test_events(self):
            """Test the event system."""
            node = Sofa.Node("root")
            node.addObject("DefaultAnimationLoop", name="loop")
            controller = node.addObject( MyController() )

            self.assertTrue( hasattr(controller, "iterations") )

            Sofa.Simulation.init(node)
            for i in range(10):
                Sofa.Simulation.animate(node, 0.01)

            self.assertTrue( hasattr(controller, "iterations") )
            self.assertEqual( controller.iterations, 10 )

         def test_bindingPersistance(self):
                 """Test that custom controllers correctly preserves attributes.
                    This can happens if the binding is not properly done and is loosing
                    the python part when go to/from sofa without having the sofa side
                    holding a reference to the python object.
                 """
                 node = Sofa.Node("root")
                 node.addObject( MyController("controller") )
                 node.init()

                 ## At this step we can validate that the python side is ok.
                 self.assertTrue( hasattr(node.controller, "inited") )
                 self.assertEqual( node.controller.inited, 1 )

                 gc.collect()

def getTestsName():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test)
    return [ test.id().split(".")[2] for test in suite]

def runTests():
        import sys
        suite = None
        if( len(sys.argv) == 1 ):
            suite = unittest.TestLoader().loadTestsFromTestCase(Test)
        else:
            suite = unittest.TestSuite()
            suite.addTest(Test(sys.argv[1]))
        return unittest.TextTestRunner(verbosity=1).run(suite).wasSuccessful()

def createScene(rootNode):
        runTests()

