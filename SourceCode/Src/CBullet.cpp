#include "CBullet.h"
#include "LessonX.h"
#include<iostream>
using namespace std;

CBullet::CBullet(const int iType,const int iSize, const char* szName):CGameSprite(szName)
{
    //ctor
    m_iType = iType;
    m_iSize = iSize;
    if(iSize==1)
        m_iDamage = 100;//
    else
        m_iDamage = 150;
        m_iHp = 100;
       // m_iScore = 0.5;//每次玩家子弹与敌机子弹碰撞时，两颗子弹都给玩家加分。所以玩家分数+1
        m_iScore = 0;
}

bool CBullet::IsMyBullet()
{
	if(m_iType==0)
        return true;
    else
        return false;
}

bool CBullet::IsBullet()
{
    return true;

}

int CBullet::GetSize()
{
    return m_iSize;
}

void CBullet::OnColOtherSprite( CGameSprite *pOther )
{
    //cout<<"bullet"<<m_iType<<endl;
    if( NULL == pOther )
		return;

    if(pOther->IsBullet())
    {
       // cout<<"子弹1：血量和伤害："<<GetHp()<<" ,"<<GetDamage()<<endl;
       // cout<<"子弹2：血量和伤害："<<pOther->GetHp()<<" ,"<<pOther->GetDamage()<<endl;
        //cout<<"子弹"<<m_iSize<<"撞上";
        if(m_iSize== 2)
            return;

        pOther = dynamic_cast<CBullet*>( pOther );//cout<<"子弹"<<pOther->GetSize()<<endl;
       // if(GetSize()==1)
        SetHp( GetHp() - pOther->GetDamage() );
       // if(pOther->GetSize()==1)
         //   g_GameMain.GetMyFighter()->SetScore( g_GameMain.GetMyFighter()->GetScore() + pOther->GetScore() );

       // cout<<"当前分数："<<g_GameMain.GetMyFighter()->GetScore() + pOther->GetScore()<<endl;
        //cout<<"子弹打中子弹"<<"血量变为："<<GetHp()<<endl;
    }

	else if(IsMyBullet () )//我方发射
	{
		if( pOther->IsMyFighter () )
			return;
		SetHp( GetHp() - pOther->GetDamage() );
//		if((pOther->GetHp()-GetDamage())<=0)
//            {
//
//                g_GameMain.GetMyFighter()->SetScore( g_GameMain.GetMyFighter()->GetScore() + pOther->GetScore() );
//            }
        //g_GameMain.SetCurScore(g_GameMain.GetMyFighter()->GetScore());
       // cout<<"当前分数："<<g_GameMain.GetMyFighter()->GetScore()<<endl;
	}

	else
	{
		if( pOther->IsMyFighter () || pOther->IsMyBullet () )
		{
			SetHp( GetHp() - pOther->GetDamage() );
		}
	}

	if(IsDead())
    {
        g_GameMain.GetM_SpriteList()->DeleteSprite(this,true);
    }
}


CBullet::~CBullet()
{
    //dtor
}
