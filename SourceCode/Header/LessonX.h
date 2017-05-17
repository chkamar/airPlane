/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CMyFighter.h"
#include "CommonClass.h"
#include "CSpriteList.h"
/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
    CMyFighter*     m_pMyFighter;
    CSprite*        g_BeginSprite;
    CTextSprite*    g_CurScoreText;
    CTextSprite*    g_MaxScoreText;
    int m_iCreatedSpriteCount;
    CSpriteList* m_SpriteList;
    int m_iMaxScore;
public:
	CGameMain();            //���캯��
	~CGameMain();           //��������

	// Get����
	int				GetGameState()				{ return m_iGameState; }
    CMyFighter*     GetMyFighter()              { return m_pMyFighter; }
    CSpriteList*    GetM_SpriteList()              {return m_SpriteList;}
	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();

	void	        OnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress );
	void            OnKeyUp( const int iKey );

    void            CreateBullet( int iType,int iEnemySize,const float fPosX, const float fPosY );
    void            AddSprite( CSprite *pSprite );
    void            DeleteSprite( CSprite *pSprite ,bool bDeleteImage);
    CGameSprite *   GetSprite( const int iIndex );
    CGameSprite *   GetSprite( const char *szName );
    bool            IsMyFighter( const char *szName );
    void            OnSpriteColSprite( const char *szSrcName, const char *szTarName );
    void            OnSpriteColWorldLimit( const char *szName, const int iColSide );
    bool            IsGameLost();
    void            SetCurScore(int score);
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
