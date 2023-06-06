#include "jhWallScript.h"
#include "jhPlayer.h"
#include "jhCoin.h"

namespace jh
{
	WallScript::WallScript()
		:mCount(0)
	{
	}
	WallScript::~WallScript()
	{
	}
	void WallScript::Initalize()
	{
	}
	void WallScript::Update()
	{
	}
	void WallScript::Render()
	{
	}
	void WallScript::OnCollisionEnter(Collider2D* collider)
	{

        Player* playerObj = dynamic_cast<Player*>(collider->GetOwner());
        if (playerObj)
        {
            Vector3 playerPos = playerObj->GetPlayerPos();
            Vector3 previousPos = playerObj->GetPreviousPos();
            Transform* wallTransform = this->GetOwner()->GetComponent<Transform>();

            float deltaX = abs(playerPos.x - previousPos.x);
            float deltaY = abs(playerPos.y - previousPos.y);

            if (deltaX > deltaY)
            {
                // Handle x-axis collision first
                if (previousPos.x < playerPos.x)
                {
                    float wallLeft = wallTransform->GetPosition().x - (wallTransform->GetScale().x / 2);
                    playerPos.x = wallLeft;
                }
                else if (previousPos.x > playerPos.x)
                {
                    float wallRight = wallTransform->GetPosition().x + (wallTransform->GetScale().x / 2);
                    playerPos.x = wallRight;
                }
                playerObj->getTransform()->SetPosition(playerPos);
                playerObj->SetPlayerPos(playerPos);
                return;
            }
            else
            {
                // Handle y-axis collision first
                if (previousPos.y < playerPos.y)
                {
                    float wallBottom = wallTransform->GetPosition().y - (wallTransform->GetScale().y / 2);
                    playerPos.y = wallBottom;
                }
                else if (previousPos.y > playerPos.y)
                {
                    float wallTop = wallTransform->GetPosition().y + (wallTransform->GetScale().y / 2);
                    playerPos.y = wallTop;
                }
                playerObj->getTransform()->SetPosition(playerPos);
                playerObj->SetPlayerPos(playerPos);
                return;
            }
        }

	}
	void WallScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void WallScript::OnCollisionExit(Collider2D* collider)
	{

	}
}