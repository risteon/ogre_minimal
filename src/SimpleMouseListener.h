/**
 * \author  risteon
 * \date    2016-03-25
 */

#ifndef OGRE_MINIMAL_SIMPLEMOUSELISTENER_H
#define OGRE_MINIMAL_SIMPLEMOUSELISTENER_H

#define OIS_DYNAMIC_LIB

// OGRE
#include <OGRE/OgreFrameListener.h>
#include <OIS/OIS.h>

/**
 * class SimpleMouseListener
 */
class SimpleMouseListener : public OIS::MouseListener
{
public:
    bool mouseMoved(const OIS::MouseEvent& e)                               { return true; }
    bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)      { return true; }
    bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)     { return true; }
};

#endif //OGRE_MINIMAL_SIMPLEMOUSELISTENER_H
