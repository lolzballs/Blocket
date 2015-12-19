#include "world.h"

World::World() : m_chunk(0, 0)
{
}

World::~World()
{
}

void World::Update(InputHandler& input)
{
    if (input.IsKeyDown(GLFW_KEY_P))
    {
        for (int i = 0; i < 16; i++)
        {
            m_chunk.AddBlock(1, glm::vec3(i, i, i));
        }
    }

    m_chunk.Update();
}

void World::Render(BasicShader& shader)
{
    m_chunk.Render(shader);
}

std::vector<AABB> World::GetIntersectingAABBs(AABB aabb)
{
    std::vector<AABB> intersecting;
    glm::vec3 min = glm::floor(aabb.GetAbsMin());
    glm::vec3 max = glm::ceil(aabb.GetAbsMax());

    for (int i = min.x; i <= max.x; i++)
    {
        for (int j = min.y; j <= max.y; j++)
        {
            for (int k = min.z; k <= max.z; k++)
            {
				glm::vec3 position{ i, j, k };
				if (m_chunk.GetBlockAtPosition(position) != 0)
				{
					AABB test(position, { -0.5, -0.5, -0.5 }, { 0.5, 0.5, 0.5 });
					if (test.Intersects(aabb))
					{
						intersecting.push_back(test);
					}
				}
            }
        }
    }
    return intersecting;
}

AABB World::Raytrace(glm::vec3 position, glm::vec2 rotation, float reach)
{
	glm::vec3 center;
	center.x = -cos(glm::radians(rotation.y + 90)) * reach * cos(glm::radians(rotation.x)) + position.x;
	center.y = -cos(glm::radians(rotation.x - 90)) * reach + position.y;
	center.z = -sin(glm::radians(rotation.y + 90)) * reach * cos(glm::radians(rotation.x)) + position.z;

	Geom::Line3 ray{ center, { position.x, position.y, position.z } };
	AABB checkArea = ray.ToAABB();
	std::vector<CollisionSide> sides;
	auto aabbs = GetIntersectingAABBs(checkArea);
	for (AABB aabb : aabbs)
	{
		if (!checkArea.Intersects(aabb))
		{
			continue;
		}

		glm::vec3 min = aabb.GetAbsMin();
		glm::vec3 max = aabb.GetAbsMax();

		sides.push_back(CollisionSide(Geom::Quad3
		{
			{min.x, min.y, min.z},
			{min.x, min.y, max.z},
			{max.x, min.y, max.z},
			{max.x, min.y, min.z}
		}, aabb, center, CSide::YP));
		sides.push_back(CollisionSide(Geom::Quad3
		{
			{ min.x, max.y, min.z },
			{ min.x, max.y, max.z },
			{ max.x, max.y, max.z },
			{ max.x, max.y, min.z }
		}, aabb, center, CSide::YN));
		sides.push_back(CollisionSide(Geom::Quad3
		{
			{ min.x, max.y, max.z },
			{ min.x, max.y, min.z },
			{ min.x, min.y, min.z },
			{ min.x, min.y, max.z }
		}, aabb, center, CSide::XP));
		sides.push_back(CollisionSide(Geom::Quad3
		{
			{ max.x, max.y, max.z },
			{ max.x, max.y, min.z },
			{ max.x, min.y, min.z },
			{ max.x, min.y, max.z }
		}, aabb, center, CSide::XN));
		sides.push_back(CollisionSide(Geom::Quad3
		{
			{ min.x, min.y, min.z },
			{ min.x, max.y, min.z },
			{ max.x, max.y, min.z },
			{ max.x, min.y, min.z }
		}, aabb, center, CSide::ZP));
		sides.push_back(CollisionSide(Geom::Quad3
		{
			{ min.x, min.y, max.z },
			{ min.x, max.y, max.z },
			{ max.x, max.y, max.z },
			{ max.x, min.y, max.z }
		}, aabb, center, CSide::ZN));
	}

	std::sort(sides.begin(), sides.end(), CSideCompare());

	bool collide = false;
	int size = sides.size();

	while (!sides.empty())
	{
		CollisionSide side = sides.front();
		sides.erase(sides.begin());

		if ((side.GetType() == CSide::XP || side.GetType() == CSide::XN) && !collide)
		{
			if (AABB::IntersectX(side.GetQStat(), ray))
			{
				collide = true;
				return side.GetAABB();
			}
		}
		else if ((side.GetType() == CSide::YP || side.GetType() == CSide::YN) && !collide)
		{
			if (AABB::IntersectY(side.GetQStat(), ray))
			{
				collide = true;
				return side.GetAABB();
			}
		}
		else if ((side.GetType() == CSide::ZP || side.GetType() == CSide::ZN) && !collide)
		{
			if (AABB::IntersectZ(side.GetQStat(), ray))
			{
				collide = true;
				return side.GetAABB();
			}
		}
	}

	return AABB(glm::vec3(), glm::vec3(), glm::vec3());
}
