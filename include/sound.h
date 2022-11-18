/*
 * File: sound.h
 * -------------
 * This file defines a class that represents a sound.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef _sound_h
#define _sound_h

#include <string>

/*
 * Class: Sound
 * ------------
 * This class encapsulates a sound file.  The sound file is specified in the
 * constructor and must be a file in either the current directory or a
 * subdirectory named <code>sounds</code>.
 *
 * <p>The following code, for example, plays the sound file
 * <code>ringtone.wav</code>:
 *
 *<pre>
 *    Sound ringtone("ringtone.wav");
 *    ringtone.play();
 *</pre>
 */

class Sound {

  public:
    /*
 * Constructor: Sound
 * Usage: Sound sound;
 *        Sound sound(filename);
 * -----------------------------
 * Creates a <code>Sound</code> object.  The default constructor
 * creates an empty sound that cannot be played.  The second form
 * initializes the sound by reading in the contents of the specified
 * file.
 */

    Sound(std::string filename);

    /*
 * Destructor: ~Sound
 * ------------------
 * Frees the memory associated with the sound.
 */

    virtual ~Sound();

    /*
 * Method: play
 * Usage: sound.play();
 * --------------------
 * Starts playing the sound.  This call returns immediately without waiting
 * for the sound to finish.
 */

    void play();
};

#endif
