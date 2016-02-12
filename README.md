# octo-wookie
Learning experiments with SDL2, resulting features are mostly (~95%) due to tutorials from [lazyfoo](www.lazyfoo.net) and [willusher](www.willusher.io). Thank you guys!

## Features
 * dt time stepping
 * lazyfoo's texture class
   * loading using SDL2_image
   * color modulation, alpha blending, selective rendering
 * rudimentary sprite sheet animation knowledge
   * result from selective rendering
 * ttf font display
 * cmake building for cross platform support

## TODO
### Text

 * implement text streaming class
   * stream input strings to a texture
   * features should allow different text display styles
     * e.g. immediate display and scrolling display
   * selective string rendering 
   * console-like text input and editing
   * perhaps rtf support...

### Audio

 * normal playback
 * fade in/out
 * learn more about audio in general...

### Management 

 * get some semblance of a game object class 

## Intended sample game
This is just my experimentation in making games/engines since the complexity is rather high but also keeps my interest. After running through the basics provided in the various tutorials I've found, I hope to make a very simple sample game:

 * The game will be 2D, top-down style like Pokemon
 * It should feature 1 building, and a small outside area. 
 * Have some trivial number of NPCs (1-2?) that can be spoken with.
 * Changing music based off location (house versus outside)
 * A menu system

Following this, I'd like to progress further to a new repository and attempt to assemble an engine that is more focused on useability. The inspiration would have to be a mixture of my own (in)experience and samplings from freely available engine source codes that I like. I am also considering attempting to take whatever I make in the first iteration and re-make it on a few other engines to gauge what I do and don't like about them (and, subsequently, backport features and improvements to my own iteration).
