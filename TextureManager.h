#include <SFML/Graphics.hpp>
#include <map>
#include <string>
using namespace sf;
using namespace std;
using std::string;
using std::map;


class TextureManager {
    static map<string, Texture> textures;
public:
    static void LoadTexture(string textureName);
    static Texture& GetTexture(string textureName);
    static void Clear();   // call this once at end of main
};
