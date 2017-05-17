#include "CGameSprite.h"

CGameSprite::CGameSprite(const char* szName):CSprite(szName)
{
    //ctor
    //m_iHp = 0;
   // m_iDamage = 0;
    //m_iScore = 0;
}

int	CGameSprite::GetHp()
{
    return m_iHp;
}
int	CGameSprite::GetDamage()
{
    return m_iDamage;
}
/*
int	CGameSprite::GetScore()
{
    return m_iScore;
}
*/
void CGameSprite::SetHp( const int iHp )
{
    m_iHp = iHp;
}
void CGameSprite::SetDamage( const int iDamage )
{
    m_iDamage = iDamage;
}
void CGameSprite::SetScore( const int iScore )
{
    m_iScore = iScore;
}

bool CGameSprite::IsDead()
{
    return ( GetHp() <= 0 );
}

CGameSprite::~CGameSprite()
{
    //dtor
}
