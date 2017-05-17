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
       // m_iScore = 0.5;//ÿ������ӵ���л��ӵ���ײʱ�������ӵ�������Ҽӷ֡�������ҷ���+1
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
       // cout<<"�ӵ�1��Ѫ�����˺���"<<GetHp()<<" ,"<<GetDamage()<<endl;
       // cout<<"�ӵ�2��Ѫ�����˺���"<<pOther->GetHp()<<" ,"<<pOther->GetDamage()<<endl;
        //cout<<"�ӵ�"<<m_iSize<<"ײ��";
        if(m_iSize== 2)
            return;

        pOther = dynamic_cast<CBullet*>( pOther );//cout<<"�ӵ�"<<pOther->GetSize()<<endl;
       // if(GetSize()==1)
        SetHp( GetHp() - pOther->GetDamage() );
       // if(pOther->GetSize()==1)
         //   g_GameMain.GetMyFighter()->SetScore( g_GameMain.GetMyFighter()->GetScore() + pOther->GetScore() );

       // cout<<"��ǰ������"<<g_GameMain.GetMyFighter()->GetScore() + pOther->GetScore()<<endl;
        //cout<<"�ӵ������ӵ�"<<"Ѫ����Ϊ��"<<GetHp()<<endl;
    }

	else if(IsMyBullet () )//�ҷ�����
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
       // cout<<"��ǰ������"<<g_GameMain.GetMyFighter()->GetScore()<<endl;
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
