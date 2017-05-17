#include "CommonClass.h"
#ifndef CMYFIGHTER_H
#define CMYFIGHTER_H
#include "CGameSprite.h"


class CMyFighter : public CGameSprite
{
    public:
        CMyFighter(const char* szName);

        void OnMove(bool bKeyDown, int iKey);
        void LoopTick( float fDeltaTime );
        void SetCanFire( const bool bCan );
        bool IsMyFighter()	;
        void OnColOtherSprite( CGameSprite *pOther );
        int GetScore();
        void SetScore(int score);
        void PlayEffect(const float fPosX, const float fPosY, const float fRotation);

        virtual ~CMyFighter();
    protected:
    private:
        float			m_fVelocityLeft;			// 控制飞机的上下左右速度
        float			m_fVelocityRight;
        float			m_fVelocityUp;
        float			m_fVelocityDown;
        float           m_fBulletCreateTime;
        bool            m_bCanFire;
        //int             m_iScore;
};

#endif // CMYFIGHTER_H
