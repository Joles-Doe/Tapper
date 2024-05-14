# Tapper C++
I wanted to try and create a game engine that uses SDL. I needed a game to make alongside it, so I decided on tapper. For this particular program, I was more focused on the programming side rather than the design side (definitely not because my design direction is a mess), so the assets used don't particularly match with one another.

The engine itself uses shared pointers in order to update objects. I took a page out of unity's book and had every GameObject have virtual Update and Draw functions - this allows the engine to call each added object and automatically removes them from the engine when the other holder of the pointer is gone. Granted, this probably isn't the best way in the world to handle objects, as I use a vector to store the pointers, but I think I did pretty well for a first attempt.

## Credits
### Assets
Floor and Wall assets - Indoor tileset by 2DPIXX - https://opengameart.org/content/indoor-tileset <br />
Bar counter asset - Home objects by Jannax - https://opengameart.org/content/home-objects <br />
Painting on bar wall - Oil painting landscapes by JAP - https://opengameart.org/content/oil-painting-landscapes <br />
Barman and Patron sprites - Classic hero and baddies pack by GrafxKid - https://opengameart.org/content/classic-hero-and-baddies-pack <br />
Beer sprite - Beer by Mapachana - https://opengameart.org/content/beer <br />

### Music
Main menu theme - Upbeat short Music Loop by AurynSky - https://opengameart.org/content/upbeat-short-music-loop-vorbis-oog <br />
Game theme - Chippey by Chasersgaming - https://opengameart.org/content/chippey <br />
Game over theme - Mandatory overtime by Joth - https://opengameart.org/content/mandatory-overtime <br />
