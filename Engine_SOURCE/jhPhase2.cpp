#include "jhPhase2.h"
#include "jhBee.h"
#include "jhTime.h"
#include "jhObject.h"

namespace jh
{
    Phase2::Phase2()
        : mOneCount(false)
        , mClear(false)
        , mTotalTime(0.0f)
        , mSpawnTime(0.0f)
        , mSpawnCount(0)
    {


    }
    Phase2::~Phase2()
    {
    }
    void Phase2::Initalize()
    {
        GameObject::Initalize();
    }
    void Phase2::Update()
    {
        GameObject::Update();

        if (!mClear)
        {
            mTotalTime += Time::DeltaTime();
            mSpawnTime += Time::DeltaTime();

            if (mSpawnTime >= 2.0f && mSpawnCount == 0)
            {
                Bee* beeobj = object::Instantiate<Bee>(eLayerType::Monster);
                beeobj->SetBeeState(eBeeState::RightSpawn);
                mMonsters.push_back(beeobj);
                mSpawnTime = 0.0f;
                mSpawnCount++;
            }

            if (mSpawnTime >= 4.0f && mSpawnCount == 1)
            {
                Bee* beeobj2 = object::Instantiate<Bee>(eLayerType::Monster);
                beeobj2->SetBeeState(eBeeState::RightSpawn);
                mMonsters.push_back(beeobj2);
                mSpawnTime = 0.0f;
                mSpawnCount++;
            }
        }

        for (auto it = mMonsters.begin(); it != mMonsters.end(); )
        {
            if ((*it)->IsDead())
            {
                it = mMonsters.erase(it);
            }
            else
            {
                ++it;
            }
        }

        if (mTotalTime >= 4.0f)
        {
            if (mMonsters.empty())
            {
                if (mOneCount == false)
                {
                    mClear = true;
                    mOneCount = true;
                }
            }
        }


    }
    void Phase2::FixedUpdate()
    {
        GameObject::FixedUpdate();
    }
    void Phase2::Render()
    {
        GameObject::Render();
    }

}