#pragma once
#include "Sprite.h"
class Tile :
    public Sprite
{
public:
    enum class groundTileType {
        none = -1,
        grass = 0,
        dirt = 1,
        sand = 2,
        gravel = 3,
        forrest = 4,
        water = 5
    };
private:
    groundTileType tileType;
protected:

public:

    Tile() {
        tileType = groundTileType::none;
    };

    Tile(sf::Texture* m_texture, sf::IntRect m_area, DataMenager* m_dM) {
        p_dM = m_dM;
        sprite.setTexture(*m_texture);
        sprite.setTextureRect(m_area);
        int i = ID / MAX_IDIES_FOR_TILES;
        tileType = static_cast<groundTileType>(i);
        std::cout << "constructor " << std::endl;
    };

    Tile(const Tile& p1) : Sprite(p1) {         //it make sure that the copy constructor of parent class is run
        p_dM = p1.p_dM;
        sprite.setTexture(*p1.sprite.getTexture());
        sprite.setTextureRect(p1.sprite.getTextureRect());
        tileType = p1.tileType;
        std::cout << "copy constructor" << std::endl;
    };

    void SetTileType(groundTileType a_type);
    Tile::groundTileType GetTileType();

    void Update(sf::Vector2i* a_mousePos);
};
