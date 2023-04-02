#pragma once
#include "Sprite.h"
class Tile :
    public Sprite
{
public:
    enum class groundTileType {
        none = -1,
        grass = 0,
        mood01 = 1,
        mood02 = 2,
        water01 = 3
    };
private:
    groundTileType tileType;
protected:

public:
    bool isTilable;
    bool needBackgroundTile;

    Tile() {
        tileType = groundTileType::none;
        isTilable = false;
        needBackgroundTile = false;
    };

    Tile(sf::Texture* m_texture, sf::IntRect m_area, bool m_isTilable, bool m_needBackgroundTile, DataMenager* m_dM) {
        p_dM = m_dM;
        sprite.setTexture(*m_texture);
        sprite.setTextureRect(m_area);
        shift = shifted::none;
        isTilable = m_isTilable;
        needBackgroundTile = m_needBackgroundTile;
        int i = ID / MAX_IDIES_FOR_TILES;
        tileType = static_cast<groundTileType>(i);
        std::cout << ID << " " << i << "constructor " << std::endl;
    };

    Tile(const Tile& p1) : Sprite(p1) {         //it make sure that the copy constructor of parent class is run
        p_dM = p1.p_dM;
        sprite.setTexture(*p1.sprite.getTexture());
        sprite.setTextureRect(p1.sprite.getTextureRect());
        shift = p1.shift;
        tileType = p1.tileType;
        isTilable = p1.isTilable;
        needBackgroundTile = p1.needBackgroundTile;
        //std::cout << "copy constructor" << std::endl;
    };

    void SetTileType(groundTileType a_type);
    Tile::groundTileType GetTileType();

    void Update(sf::Vector2i* a_mousePos);
};
