/**
 * \author  risteon
 * \date    2016-03-25
 */

#ifndef OGRE_MINIMAL_SIMPLEKEYLISTENER_H
#define OGRE_MINIMAL_SIMPLEKEYLISTENER_H

#define OIS_DYNAMIC_LIB

// OGRE
#include <OIS/OIS.h>

/**
 * class SimpleKeyListener
 */
class SimpleKeyListener : public OIS::KeyListener
{
public:

    bool keyPressed(const OIS::KeyEvent& e)     { return true; }
    bool keyReleased(const OIS::KeyEvent& e)    { return true; }
};

#endif //OGRE_MINIMAL_SIMPLEKEYLISTENER_H
