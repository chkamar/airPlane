#ifndef CGAMESPRITE_H
#define CGAMESPRITE_H

#include <CommonClass.h>


class CGameSprite : public CSprite
{
    public:
        int m_iHp;
        int m_iDamage;
        int m_iScore;

        CGameSprite(const char* szName);
        virtual ~CGameSprite();

        int	GetHp();
        int	GetDamage();
        virtual int	GetScore(){return m_iScore;}
        void SetHp( const int iHp );
        void SetDamage( const int iDamage );
        void SetScore( const int iScore );
        bool IsDead();
        virtual void	LoopTick( float fDeltaTime ){}
        virtual bool	IsMyFighter(){ return false;}
        virtual bool	IsMyBullet(){return false;}
        virtual void	OnColOtherSprite( CGameSprite *pOther ){}
        virtual bool    IsBullet(){return false;}

    protected:
    private:

};

#endif // CGAMESPRITE_H
