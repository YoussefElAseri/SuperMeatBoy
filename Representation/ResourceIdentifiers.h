#ifndef SUPERMEATBOY_RESOURCEIDENTIFIERS_H
#define SUPERMEATBOY_RESOURCEIDENTIFIERS_H

namespace sf {
    class Texture;
    class Font;
}

namespace Textures {

    enum ID {
        Meatboy,
        BandageGirl,
        Earth,
        Fire
    };
}

namespace Fonts {
    enum ID {
        TitleScreen
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

#endif //SUPERMEATBOY_RESOURCEIDENTIFIERS_H
