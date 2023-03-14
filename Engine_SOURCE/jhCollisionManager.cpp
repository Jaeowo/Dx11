#include "jhCollisionManager.h"
#include "jhScene.h"
#include "jhSceneManager.h"

namespace jh
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; column++)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
	}
	void CollisionManager::FixedUpdate()
	{
	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}

		mLayerCollisionMatrix[row][column] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (left->GetState() != GameObject::Active)
				continue;
			if (left->GetComponent<Collider2D>() == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				if (right->GetState() != GameObject::Active)
					continue;
				if (right->GetComponent<Collider2D>() == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<Collider2D>(), right->GetComponent<Collider2D>());
			}

			if ((UINT)left == (UINT)right)
				break;
		}
	}
	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		//두 충돌체 레이어로 구성된 ID확인
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		//이전 충돌 정보 검색후 충돌정보가 없는 상태라면 충돌정보를 생성해준다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}
		//충돌체크를 해준다
		if (Intersect(left, right)) //충돌을 한 상태
		{
			//최초 충돌중 Enter
			if (iter->second == false)
			{
				if (left->IsTrigger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTrigger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else //충돌 중이지 않은 상태 Enter
			{
				if (left->IsTrigger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTrigger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}

		}
		else // 충돌하지 않은상태
		{
			//충돌 중인상태 Exit
			if (iter->second == true)
			{
				if (left->IsTrigger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTrigger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionEnter(left);

				iter->second = false;
			}
		}

	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		//사각형 충돌


		Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, -0.5f, 0.0f}
			,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Matrix leftMat = leftTr->GetWorldMatrix();
		Matrix rightMat = rightTr->GetWorldMatrix();

		// 분리축 벡터
		Vector3 Axis[4] = {};
		Axis[0] = Vector3::Transform(arrLocalPos[1], leftMat);
		Axis[1] = Vector3::Transform(arrLocalPos[3], leftMat);
		Axis[2] = Vector3::Transform(arrLocalPos[1], rightMat);
		Axis[3] = Vector3::Transform(arrLocalPos[3], rightMat);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMat);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMat);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMat);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMat);

		Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
		Axis[0] = Axis[0] * leftScale;
		Axis[1] = Axis[1] * leftScale;

		Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
		Axis[2] = Axis[2] * rightScale;
		Axis[3] = Axis[3] * rightScale;

		for (size_t i = 0; i < 4; i++)
		{
			Axis[i].z = 0.0f;
		}

		Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];
			//vA.Normalize();

			float projDist = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDist += fabsf(Axis[i].Dot(vA) / 2.0f);
			}

			if (projDist < fabsf(centerDir.Dot(vA)))
			{
				return false;
			}
		}

		return true;

		/*if (left->GetType() == eColliderType::Rect && right->GetType() == eColliderType::Rect)
		{
		
		}*/

		////원충돌
		//if (left->GetType() == eColliderType::Circle && right->GetType() == eColliderType::Circle)
		//{
		//	Vector2 LeftSize = left->GetSize();
		//	Vector2 RightSize = right->GetSize();

		//	float LeftRadius = (LeftSize.x / 2.0f);
		//	float RightRadius = (RightSize.x / 2.0f);

		//	float TotalRadius = LeftRadius + RightRadius;

		//	Vector3 vc = left->GetPosition() - right->GetPosition();
		//	vc.z = 0.0f;

		//	Vector3 CenterDir = vc;

		//	if (CenterDir.x >= TotalRadius
		//		|| CenterDir.y >= TotalRadius)
		//	{
		//		return false;
		//	}
		//	else if (CenterDir.x < TotalRadius
		//		|| CenterDir.y < TotalRadius)
		//	{
		//		return true;
		//	}
		//	else
		//		return false;

		//}

	}
}