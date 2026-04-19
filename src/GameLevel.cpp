#include "GameLevel.h"

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
	this->Bricks.clear();

	unsigned int tileCode;
	GameLevel level;

	std::string line;
	std::ifstream levelStream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (levelStream) {
		while (std::getline(levelStream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
            std::cout << line << std::endl;
			while (sstream >> tileCode)
                row.push_back(tileCode);
            if (!row.empty())
                tileData.push_back(row);
		};
		if (tileData.size() > 0) {
			this->Init(tileData, levelWidth, levelHeight);
		}
        std::cout << "Tiledata size: " << tileData.size() << std::endl;
	}

}

void GameLevel::Draw(SpriteRenderer & renderer)
{
    for (GameObject& tile : this->Bricks)
        if (!tile.destroyed)
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : this->Bricks)
        if (!tile.isSolid && !tile.destroyed)
            return false;
    return true;
}

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / height;

    std::shared_ptr<Texture> blockSolidTexture = std::make_shared<Texture>("res\\Textures\\breakout\\block_solid.png", "diffuse");
    std::shared_ptr<Texture> blockTexture = std::make_shared<Texture>("res\\Textures\\breakout\\block.png", "diffuse");

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            std::cout << "Row " << y << " size: " << tileData[y].size() << std::endl;
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);

                GameObject obj(pos, size,
                    blockSolidTexture,
                    glm::vec3(0.8f, 0.8f, 0.7f)
                );
                obj.isSolid = true;
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] > 1)
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->Bricks.push_back(
                    GameObject(pos, size, blockTexture, color)
                );
            }
        }
    }

}
