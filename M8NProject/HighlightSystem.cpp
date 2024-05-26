#pragma once

#include "HighlightSystem.hpp"
#include "Input.hpp"
#include "Rock.hpp"

void HighlightSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
    Input& input = Input::getInstance();
    Vector2D cameraPos = Camera::getInstance().getPosition();

    for (auto& entity : entities)
    {
        if (entity->hasComponent<ColliderComponent>() && entity->hasComponent<TransformComponent>() && entity->hasColliderComponent("highlightCollider"))
        {
            ColliderComponent& colliderComponent = entity->getColliderComponent("highlightCollider");

            Rock* rockEntity = dynamic_cast<Rock*>(entity.get());

            if (rockEntity)
            {
                int worldMouseX = input.mouseXPos + static_cast<int>(cameraPos.x);
                int worldMouseY = input.mouseYPos + static_cast<int>(cameraPos.y);

                if (worldMouseX >= colliderComponent.collider.x && worldMouseX <= colliderComponent.collider.x + colliderComponent.collider.w &&
                    worldMouseY >= colliderComponent.collider.y && worldMouseY <= colliderComponent.collider.y + colliderComponent.collider.h)
                {
                    rockEntity->sprite->setTextureId("rockHighlighted");
                }
                else
                {
                    rockEntity->sprite->setTextureId("rock");
                }
            }
        }
    }
}
