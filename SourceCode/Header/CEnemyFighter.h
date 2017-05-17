#ifndef CENEMYFIGHTER_H
#define CENEMYFIGHTER_H

#include <CommonClass.h>
#include "CGameSprite.h"

class CEnemyFighter : public CGameSprite
{


    public:
        static float    m_fCreateTime;			// 创建敌机的时间间隔
        static int	m_iCreatedSpriteCount;//表示创建战机数量
        float m_fCanFireAfterCreated;
        float m_fBulletCreateTime;
        float m_fFloatTime;
        bool m_bFloatUp;
        int m_iSize;

        CEnemyFighter( const char* szName );
        void static ClassTick( float fDeltaTime );
        void LoopTick( float fDeltaTime );
        void OnColOtherSprite( CGameSprite *pOther );
        void SetSize(int iSize){m_iSize = iSize;}
        int GetSize(){return m_iSize;}
        void PlayEffect(int iSize,const float fPosX, const float fPosY, const float fRotation);

        virtual ~CEnemyFighter();
    protected:
    private:

};

#endif // CENEMYFIGHTER_H
