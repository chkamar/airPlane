#include "CMyFighter.h"
#include "LessonX.h"
#include<iostream>
using namespace std;
CMyFighter:: CMyFighter (const char* szName):CGameSprite(szName) //�Թ��캯������ʵ��
{
	m_fVelocityLeft = 0.f;			// ���Ʒɻ������������ٶ�
	m_fVelocityRight = 0.f;
	m_fVelocityUp = 0.f;
	m_fVelocityDown = 0.f;
    m_fBulletCreateTime = 0.3f;
    m_bCanFire = false;
    m_iHp = 500;
    m_iScore = 0;
    m_iDamage = 100;//�κ������ҷ�ս����hp-100

	//bool WORLD_LIMIT_STICKY = true;//���ú�����༭����ײ����ΪWORLD_LIMIT_STICKY������������߽�ʱ��ս����ֹ������
}

void CMyFighter::OnMove(bool bKeyDown, int iKey)
{
	if(bKeyDown)
	{
	   // cout<<"press"<<endl;
		switch(iKey)
		{
		case KEY_A:  // ��
			m_fVelocityLeft	 =	30.f;
			break;
		case KEY_D:  // ��
			m_fVelocityRight =	30.f;
			break;
		case KEY_W:  // ��
			m_fVelocityUp	 =	15.f;
			break;
		case KEY_S:  // ��
			m_fVelocityDown	 =	15.f;
			break;
		}
    }
	else
	{
	   // cout<<"up"<<endl;
		switch(iKey)
		{
		case KEY_A:  // ��
			m_fVelocityLeft	 =	0.f;
			break;
		case KEY_D:  // ��
			m_fVelocityRight =	0.f;
			break;
		case KEY_W:  // ��
			m_fVelocityUp	 =	0.f;
			break;
		case KEY_S:  // ��
			m_fVelocityDown	 =	0.f;
			break;
		}
	}
	float fVelX	= m_fVelocityRight - m_fVelocityLeft;
	float fVelY = m_fVelocityDown - m_fVelocityUp;
	SetSpriteLinearVelocity( fVelX,fVelY );
}

// �����ӵ��ķ���
void CMyFighter::LoopTick( float fDeltaTime )
{
	m_fBulletCreateTime	-= fDeltaTime;
	if( m_fBulletCreateTime <= 0.f && m_bCanFire )
	{
		// �̶�����ʱ��
		m_fBulletCreateTime	=	0.3f;
		g_GameMain.CreateBullet(0,1,GetSpritePositionX(), GetSpritePositionY() );
	}
}

void CMyFighter::PlayEffect(const float fPosX, const float fPosY, const float fRotation)
{
    CEffect*    boom = new CEffect("playerExplode","",3.0);
    boom->PlayEffect(fPosX,fPosY,fRotation);
}

int CMyFighter::GetScore()
{
    return m_iScore;
}

void CMyFighter::SetScore(int score)
{
    m_iScore = score;
    g_GameMain.SetCurScore(m_iScore);
}

bool CMyFighter::IsMyFighter()
{
    return true;
}

void CMyFighter::SetCanFire( const bool bCan )
{
    m_bCanFire = bCan;
}

void CMyFighter::OnColOtherSprite( CGameSprite *pOther )
{
    if( NULL == pOther )
		return;
	if( pOther-> IsMyBullet () )
		return;
   // cout<<"i"<<endl;
	SetHp( GetHp() - pOther->GetDamage() );
	if( GetDamage() >= pOther->GetHp() )
	{
		SetScore( GetScore() + pOther->GetScore() );
	}
	if( GetHp() <= 200 )
	{
	    SetSpriteColorGreen( 0 );
		SetSpriteColorBlue( 0 );
	    if(GetHp()<=0)
	    {
	        float x = GetSpritePositionX();
	        float y = GetSpritePositionY();
            DeleteSprite();//cout<<"delete player     ";
	        PlayEffect(x,y,0.f);//cout<<"play effect"<<endl;
	    }

	}
	else if( GetHp() <= 500 )
	{
		SetSpriteColorGreen( 128 );
		SetSpriteColorBlue( 128 );
	}

//	else
//	{
//		SetSpriteColorGreen( 255 );
//		SetSpriteColorBlue( 255 );
//	}
	//���»�����ʾ
	if(pOther->GetHp()-GetDamage()<=0)
        g_GameMain.GetMyFighter()->SetScore( g_GameMain.GetMyFighter()->GetScore() + pOther->GetScore() );

}

CMyFighter::~CMyFighter()
{
    //dtor
}
