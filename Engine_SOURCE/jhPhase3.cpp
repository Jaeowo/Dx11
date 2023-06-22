#include "jhPhase3.h"
#include "jhBee.h"
#include "jhTime.h"
#include "jhObject.h"

namespace jh
{
    Phase3::Phase3()
        : mOneCount(false)
        , mClear(false)
        , mTotalTime(0.0f)
        , mSpawnTime(0.0f)
        , mSpawnCount(0)
    {


    }
    Phase3::~Phase3()
    {
    }
    void Phase3::Initalize()
    {
        GameObject::Initalize();
    }
    void Phase3::Update()
    {
        GameObject::Update();

        if (!mClear)
        {
            mTotalTime += Time::DeltaTime();
            mSpawnTime += Time::DeltaTime();

            if (mSpawnTime >= 2.0f && mSpawnCount == 0)
            {
                Bee* beeobj = object::Instantiate<Bee>(eLayerType::Monster);
                beeobj->SetBeeState(eBeeState::LeftSpawn);
                mMonsters.push_back(beeobj);
                mSpawnTime = 0.0f;
                mSpawnCount++;
            }

            if (mSpawnTime >= 3.5f && mSpawnCount == 1)
            {
                Bee* beeobj2 = object::Instantiate<Bee>(eLayerType::Monster);
                beeobj2->SetBeeState(eBeeState::LeftSpawn);
                mMonsters.push_back(beeobj2);
                mSpawnTime = 0.0f;
                mSpawnCount++;
            }
            if (mSpawnTime >= 5.0f && mSpawnCount == 2)
            {
                Bee* beeobj3 = object::Instantiate<Bee>(eLayerType::Monster);
                beeobj3->SetBeeState(eBeeState::LeftSpawn);
                mMonsters.push_back(beeobj3);
                mSpawnTime = 0.0f;
                mSpawnCount++;
            }
            if (mSpawnTime >= 6.5f && mSpawnCount == 3)
            {
                Bee* beeobj4 = object::Instantiate<Bee>(eLayerType::Monster);
                beeobj4->SetBeeState(eBeeState::LeftSpawn);
                mMonsters.push_back(beeobj4);
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

        if (mTotalTime >= 8.0f)
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
    void Phase3::FixedUpdate()
    {
        GameObject::FixedUpdate();
    }
    void Phase3::Render()
    {
        GameObject::Render();
    }

}