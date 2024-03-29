#pragma once
#include "Sprite.h"

const int MAX_TILE_TYPES = 5;       //taken from groundTileType last element val
const int DEFAULT_BASE_TILE = 34;   //taken from texture
const int BASE_TEXTURE_SIZE_X = 352;
class Tile :
    public Sprite
{
public:
    /// <summary>
    /// Adding new tileset:
    /// 1: adding new texture and tileset name in tileNames[] in Datamenager.h
    /// 2: adding new groundTileType into this file and rise MAX_TILE_TYPES constatn
    /// 3: adding Tile*[][] that size depends on texture and make prefabs in ObMg constructor (for strange size of texture you need to use **var and for loop;
    ///  
    /// </summary>
    enum class groundTileType {
        none = -1,
        grass = 0,
        muddyGrass = 1,
        mood01 = 2,
        mood02 = 3,
        water01 = 4,
        lastTilable = 4, 
        other = 5
    };
private:
    groundTileType tileType;
    sf::IntRect basicRect;
    bool isWalkable;
protected:

public:
    bool isTilable;
    bool needBackgroundTile;
    unsigned int nbOfVariants;
    unsigned int currentVariant;
    static int g_lastID;
    static int g_lastTileID;
    Tile() {
        tileType = groundTileType::none;
        isTilable = false;
        isWalkable = false;
        needBackgroundTile = false;
        nbOfVariants = 0;
        currentVariant = 0;
        hasHitbox = false;
    };

    Tile(sf::Texture* m_texture, sf::IntRect m_area, bool m_isTilable, bool m_isWalkable, bool m_needBackgroundTile, unsigned int m_nbOfVariants, DataMenager* m_dM) {
        p_dM = m_dM;
        sprite.setTexture(*m_texture);
        sprite.setTextureRect(m_area);
        basicRect = sprite.getTextureRect();
        nbOfVariants = m_nbOfVariants;
        currentVariant = 0;
        isTilable = m_isTilable;
        needBackgroundTile = m_needBackgroundTile;
        hasHitbox = false; 
        AnimMenager = new AnimationMenager(p_dM);
        isWalkable = m_isWalkable;
        int i = ID / MAX_IDIES_FOR_TILES;
        if (i > static_cast<int>(Tile::groundTileType::other))
            i = static_cast<int>(Tile::groundTileType::other);
        tileType = static_cast<groundTileType>(i);
        int a = ID - ((static_cast<int>(tileType) * MAX_IDIES_FOR_TILES));
        g_lastID = a;
        g_lastTileID++;
    };

    Tile(const Tile& p1) : Sprite(p1) {         //it make sure that the copy constructor of parent class is run
        p_dM = p1.p_dM;
        sprite.setTexture(*p1.sprite.getTexture());
        sprite.setTextureRect(p1.sprite.getTextureRect());
        basicRect = p1.basicRect;
        nbOfVariants = p1.nbOfVariants;
        currentVariant = p1.currentVariant;
        tileType = p1.tileType;
        isTilable = p1.isTilable;
        isWalkable = p1.isWalkable;
        needBackgroundTile = p1.needBackgroundTile;
    };

    bool isTileWalkable();
    Tile::groundTileType GetTileType();
    void changeVariant(bool a_up);
    void setVariant(unsigned int a_variant);
    void Update(sf::Vector2i* a_mousePos);
};
